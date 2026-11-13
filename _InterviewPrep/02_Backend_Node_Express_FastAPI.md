# Domain 02: Backend Engineering (Node.js, Express & FastAPI)

This guide covers core server-side architectures, concurrency models, asynchronous execution, and API design standards relevant to your tech stack (**Node.js, Express.js, FastAPI, Python, REST APIs**).

---

## 1. Node.js Architecture & Concurrency Model

### 1.1 Single-Threaded Event Loop & `libuv`
Node.js executes JavaScript on a single thread (V8 engine), but delegates heavy I/O operations (file system, DNS, crypto, network requests) to the OS kernel or the **libuv thread pool** (default 4 worker threads, configurable via `UV_THREADPOOL_SIZE`).

```
 +-------------------------------------------------------+
 |                    V8 Engine (Call Stack)             |
 +-------------------------------------------------------+
                            |
                            v
 +-------------------------------------------------------+
 |                 libuv Event Loop                     |
 |                                                       |
 |  1. Timers (setTimeout, setInterval)                  |
 |  2. Pending Callbacks (I/O callbacks)                 |
 |  3. Idle, Prepare                                     |
 |  4. Poll Phase (Retrieves new I/O events)             |
 |  5. Check Phase (setImmediate callbacks)             |
 |  6. Close Callbacks (socket.on('close'))              |
 +-------------------------------------------------------+
          |                                  |
          v                                  v
 [Kernel Async I/O (epoll/kqueue)]   [Worker Thread Pool]
 (Sockets, HTTP, TCP connections)    (FS, Crypto, zlib, DNS)
```

#### Microtasks in Node.js:
- `process.nextTick()`: Higher priority than promises. Fires immediately after the current operation finishes, before the event loop advances to the next phase.
- `Promise.then()` / `queueMicrotask()`: Runs right after `process.nextTick()` queue is drained.

**Interview Trap:** *What happens if you run a heavy CPU computation (e.g., recursive JSON parsing or image compression) in Express?*
- **Accepted Answer:** It monopolizes the single main thread, blocking the event loop. Incoming HTTP requests cannot be accepted or processed, causing request timeouts and high latency. Solutions:
  1. Offload CPU-bound tasks to `Worker Threads` (`worker_threads` module).
  2. Use a distributed job queue (BullMQ + Redis) with separate background worker processes.
  3. Spin up child processes (`child_process.fork()`).

---

### 1.2 Streams and Buffers
Handling large files (like CSV uploads in *Insight Forge* or crop images before uploading to Cloudinary) using standard memory buffers (`fs.readFile`) loads the entire file into RAM, risking `Out Of Memory (OOM)` errors.

- **Buffer:** Fixed-size chunk of memory allocated outside the V8 heap for binary data.
- **Streams:** Data handling abstraction where chunks are processed piece by piece:
  1. `Readable` (e.g., incoming HTTP request, `fs.createReadStream`)
  2. `Writable` (e.g., HTTP response `res`, `fs.createWriteStream`)
  3. `Transform` (e.g., `zlib.createGzip()`, CSV parser)
  4. `Duplex` (e.g., TCP socket)

```javascript
// Efficient stream piping with backpressure handling:
import { pipeline } from 'stream/promises';
import fs from 'fs';
import zlib from 'zlib';

async function compressFile(sourcePath, destinationPath) {
  await pipeline(
    fs.createReadStream(sourcePath),
    zlib.createGzip(),
    fs.createWriteStream(destinationPath)
  );
  console.log('Compression complete without high RAM consumption');
}
```

---

## 2. Express.js Deep Dive & Production Best Practices

### 2.1 Middleware Pipeline
Express is fundamentally a series of middleware function calls executed sequentially in an onion/pipeline architecture.

```javascript
// Signature: (req, res, next)
const loggingMiddleware = (req, res, next) => {
  const start = Date.now();
  res.on('finish', () => {
    const duration = Date.now() - start;
    console.log(`${req.method} ${req.originalUrl} - ${res.statusCode} (${duration}ms)`);
  });
  next(); // Pass control to the next middleware
};
```

### 2.2 Centralized Error Handling Middleware
In Express, error handling middleware **must accept 4 arguments** (`(err, req, res, next)`). Omitting `next` causes Express to treat it as a standard middleware.

```javascript
// AppError custom class
export class AppError extends Error {
  constructor(message, statusCode) {
    super(message);
    this.statusCode = statusCode;
    this.status = `${statusCode}`.startsWith('4') ? 'fail' : 'error';
    this.isOperational = true; // Operational (trusted) vs programming error
    Error.captureStackTrace(this, this.constructor);
  }
}

// Global Error Handler
export const globalErrorHandler = (err, req, res, next) => {
  err.statusCode = err.statusCode || 500;
  err.status = err.status || 'error';

  if (process.env.NODE_ENV === 'development') {
    res.status(err.statusCode).json({
      status: err.status,
      message: err.message,
      stack: err.stack,
      error: err
    });
  } else {
    // Production: Do not leak stack traces or internal secrets
    if (err.isOperational) {
      res.status(err.statusCode).json({
        status: err.status,
        message: err.message
      });
    } else {
      console.error('CRITICAL UNHANDLED ERROR:', err);
      res.status(500).json({
        status: 'error',
        message: 'Internal server error. Please try again later.'
      });
    }
  }
};
```

---

## 3. Python FastAPI & Asynchronous Architecture

On your resume, you used **FastAPI** for *Insight Forge* to orchestrate multi-agent LLM pipelines, schema inference, and SQL execution.

### 3.1 ASGI vs WSGI
| Metric | WSGI (Flask, Django) | ASGI (FastAPI, Starlette) |
| :--- | :--- | :--- |
| **Model** | Synchronous, 1 request per thread/worker | Asynchronous, event-loop driven (`asyncio`) |
| **Concurrency** | Threads block on I/O (DB queries, LLM calls) | Single worker handles thousands of concurrent pending I/O requests |
| **WebSockets/SSE** | Difficult, requires separate servers (Gunicorn + Gevent) | Native first-class support |
| **Server** | Gunicorn / uWSGI | Uvicorn / Hypercorn |

### 3.2 Async/Await and Thread Pool Offloading in FastAPI
- An endpoint declared as `async def endpoint():` runs directly on the main `asyncio` event loop.
- **Critical Caveat:** If you run synchronous blocking code (e.g., `time.sleep()`, synchronous SQLite query, or CPU-heavy calculations) inside an `async def` route, you **freeze the entire event loop** for all users!
- **FastAPI's Smart Thread Pool:** If an endpoint is declared as a plain synchronous function (`def endpoint():`), FastAPI automatically offloads it to an external thread pool (`anyio.to_thread.run_sync`), keeping the main event loop responsive!

```python
from fastapi import FastAPI, HTTPException, Depends
from pydantic import BaseModel, Field
import httpx
import asyncio

app = FastAPI(title="Insight Forge Analytics Engine")

class QueryRequest(BaseModel):
    natural_query: str = Field(..., min_length=3, max_length=500)
    session_id: str

# Async I/O for external LLM API calls (non-blocking)
@app.post("/api/v1/generate-sql")
async def generate_sql(payload: QueryRequest):
    async with httpx.AsyncClient(timeout=30.0) as client:
        # Non-blocking async call to Groq API
        response = await client.post(
            "https://api.groq.com/openai/v1/chat/completions",
            headers={"Authorization": f"Bearer {GROQ_API_KEY}"},
            json={
                "model": "llama-3.1-70b-versatile",
                "messages": [{"role": "user", "content": payload.natural_query}]
            }
        )
        if response.status_code != 200:
            raise HTTPException(status_code=502, detail="LLM Provider Error")
        
        return response.json()
```

### 3.3 Pydantic Data Validation & Serialization
FastAPI utilizes Pydantic v2 (implemented in Rust core) for:
- Automatic request body parsing and type coercion.
- Automatic generation of OpenAPI (Swagger UI) specs at `/docs`.
- Response model filtering (stripping internal attributes like hashed passwords).

---

## 4. RESTful API Design Standards & Best Practices

1. **Noun-Based Resource Endpoints:**
   - Good: `GET /api/v1/crops`, `POST /api/v1/crops`, `GET /api/v1/crops/:id`, `PATCH /api/v1/crops/:id`, `DELETE /api/v1/crops/:id`.
   - Bad: `POST /api/v1/getAllCrops`, `POST /api/v1/deleteCropById`.
2. **HTTP Status Codes:**
   - `200 OK`: Successful read/update.
   - `201 Created`: Successful creation with resource returned.
   - `204 No Content`: Successful deletion, no body returned.
   - `400 Bad Request`: Malformed payload or validation error.
   - `401 Unauthorized`: Authentication missing or invalid token.
   - `403 Forbidden`: Authenticated, but lacking sufficient role/permission.
   - `404 Not Found`: Resource does not exist.
   - `409 Conflict`: Duplicate key error, concurrent conflict.
   - `429 Too Many Requests`: Rate limit reached.
   - `500 Internal Server Error`: Unhandled server exception.
3. **Idempotency:**
   - `GET`, `PUT`, `DELETE`, `HEAD`, `OPTIONS` must be idempotent (multiple identical requests result in the same server state).
   - `POST` is non-idempotent. To make financial or pickup operations safe against network retries (e.g., UTR payment recording in *FarmFresh*), accept an `Idempotency-Key` header in the request.
