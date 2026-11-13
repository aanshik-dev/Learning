# Domain 05: System Design & Application Architecture

This guide covers **System Design Fundamentals** (Scalability, Caching, Concurrency, Messaging) and detailed **Architectural Case Studies** directly derived from your projects (**FarmFresh** and **Insight Forge**).

---

## 1. High-Level Architecture Fundamentals

### 1.1 Horizontal vs. Vertical Scaling & Statelessness
- **Vertical Scaling (Scale Up):** Adding more CPU, RAM, or faster NVMe storage to a single machine. Limited by hardware ceilings and introduces a single point of failure (SPOF).
- **Horizontal Scaling (Scale Out):** Adding more application server instances behind a Load Balancer (e.g., NGINX, AWS ALB).
- **Stateless Application Tier:** To scale horizontally, servers must not store session state in local memory. Session authentication should be **stateless (signed JWTs)** or stored in a shared distributed store like **Redis**. Any incoming request can then be served by any available server instance.

---

### 1.2 Caching Strategies & Redis
- **Cache-Aside (Lazy Loading):**
  1. Application checks Redis cache first.
  2. Cache hit: Return data immediately.
  3. Cache miss: Read from MongoDB/SQL, write to Redis with a TTL (Time-To-Live), and return.
- **Write-Through:** Data is written simultaneously to cache and database. Higher write latency, but cache is always warm and consistent.
- **Eviction Policies:**
  - **LRU (Least Recently Used):** Discards the least recently accessed items first.
  - **LFU (Least Frequently Used):** Discards items accessed the fewest times.
- **Common Cache Pitfalls:**
  - **Cache Stampede (Thundering Herd):** High-traffic key expires, causing thousands of concurrent requests to hit the database at once. *Solution:* Mutex/distributed locking or background probabilistic re-caching.
  - **Cache Penetration:** Requests for non-existent keys bypass cache and hit DB. *Solution:* Cache `null` values with a short TTL or use a **Bloom Filter**.

---

### 1.3 Communication Protocols: REST vs. WebSockets vs. SSE
| Feature | REST (HTTP/1.1 or HTTP/2) | WebSockets (RFC 6455) | Server-Sent Events (SSE) |
| :--- | :--- | :--- | :--- |
| **Direction** | Unidirectional (Client $\to$ Server) | Full-Duplex Bi-directional | Unidirectional (Server $\to$ Client) |
| **Protocol** | Standard HTTP | Upgraded TCP socket | Standard HTTP (streaming `text/event-stream`) |
| **Reconnection** | Per-request | Manual implementation needed | Automatic client reconnection built-in |
| **Best Use Case** | CRUD operations, Auth, File uploads | Multi-player games, live chat, real-time vehicle GPS tracking | Real-time AI token streaming (Groq LLaMA in FarmFresh / Insight Forge) |

---

### 1.4 Rate Limiting Algorithms
1. **Token Bucket:** Tokens added to a bucket at a constant rate up to capacity. Each request consumes a token. Allows bursts of traffic while maintaining a steady rate.
2. **Leaky Bucket:** Requests enter a queue and leak out at a constant rate. Smooths out traffic spikes.
3. **Sliding Window Counter:** Divides time into rolling windows to eliminate edge-burst vulnerabilities of Fixed Window. Implemented in Redis using sorted sets (`ZADD`, `ZREMRANGEBYSCORE`).

---

## 2. Project Architecture Deep-Dive: FarmFresh

### 2.1 The Problem & Business Flow
- **Ecosystem:** Rural farmer collectives in Himalayan regions, bulk organic buyers, fleet drivers, and platform administrators.
- **Core Operations:**
  1. Farmers aggregate crop listings.
  2. Buyers negotiate bulk quantities and place deal requests.
  3. Platform schedules batch pickups based on vehicle capacity and geographical zones.
  4. Payment reconciliation via immutable UTR records.

```
 [ Farmer Collective ]          [ Bulk Buyer ]
         |                             |
         v                             v
  +-------------------------------------------+
  |         Vercel Edge / React Client        |
  +-------------------------------------------+
                        | (HTTPS + JWT Bearer)
                        v
  +-------------------------------------------+
  |        Express.js API Gateway (Node)      |
  |  - RBAC Middleware (Farmer/Collective/Admin)
  |  - Automated Axios Interceptor handling   |
  +-------------------------------------------+
       |                  |                |
       v                  v                v
 [ MongoDB Cluster ] [ Cloudinary ]  [ Groq LLaMA 3.1 ]
 - Normalized Schemas  (Media CDN)   (FarmAssist Advisor via SSE)
 - Pickup Scheduler
 - Immutable UTR Ledger
```

### 2.2 Zone-Based Pickup Scheduler with Vehicle Capacity Constraints
**Design Challenge:** Prevent vehicle overloading and driver over-assignment when multiple collectives schedule batch pickups on the same day.

```
Zone A (Himalayan Valley 1)
  ├── Pickup Req 1: Apples (400 kg)
  ├── Pickup Req 2: Walnuts (300 kg)
  └── Total Demand: 700 kg

Vehicle Fleet Assignment:
  ├── Van 1: Max Payload 1000 kg -> Assigned (Remaining: 300 kg)
  └── Van 2: Idle
```

**Implementation Strategy:**
1. **Spatial Grouping:** Group active pickup requests by geographical `zoneId` and target date.
2. **Knapsack / Bin-Packing Algorithm:** Greedily fit pending batches into available fleet vehicles sorted by payload capacity (`maxWeightKg`).
3. **Optimistic Locking & Concurrency Guard:**
   ```javascript
   // Ensure vehicle capacity is not exceeded during concurrent assignments:
   const vehicle = await Vehicle.findOneAndUpdate(
     {
       _id: vehicleId,
       assignedDate: targetDate,
       currentLoadKg: { $lte: vehicleMaxCapacity - batchWeightKg }
     },
     {
       $inc: { currentLoadKg: batchWeightKg },
       $push: { assignedPickups: pickupId }
     },
     { new: true }
   );
   if (!vehicle) {
     throw new Error("Vehicle capacity exceeded or vehicle unavailable for this date.");
   }
   ```

### 2.3 Immutable UTR Payment Ledger
- Once a payment is made via bank transfer (NEFT/RTGS/IMPS), a **UTR (Unique Transaction Reference)** is generated.
- To prevent double-spending or invoice tampering:
  1. The `UTR` column has a **unique compound index** in MongoDB (`{ utrNumber: 1 }, { unique: true }`).
  2. Status state-machine transitions are strictly one-way:
     $$\text{PENDING} \longrightarrow \text{VERIFIED} \longrightarrow \text{SETTLED}$$
  3. No `UPDATE` or `DELETE` is permitted on settled financial ledger documents. Corrections require issuing offsetting credit/debit adjustment records.

---

## 3. Project Architecture Deep-Dive: Insight Forge

### 3.1 The 4-Agent LLM Pipeline
Insight Forge converts natural language queries into executable SQL queries, validates them, runs them against datasets, and visualizes the results.

```
  [ User Query: "Show top 5 revenue crops in 2025" ]
                           |
                           v
   +-----------------------------------------------+
   | 1. Table & Column Selector Agent              |
   | - Analyzes schema metadata                    |
   | - Prunes irrelevant tables to fit context     |
   +-----------------------------------------------+
                           |
                           v
   +-----------------------------------------------+
   | 2. SQL Generator Agent (Groq LLaMA 3.1)       |
   | - Generates deterministic SQL (SELECT only)   |
   | - Enforces dialect (SQLite / ANSI SQL)        |
   +-----------------------------------------------+
                           |
                           v
   +-----------------------------------------------+
   | 3. Execution & Auto-Fix Retry Engine          |
   | - Checks query via AST Parser (AST whitelist) |
   | - Executes on read-only SQLite sandbox        |
   | - IF error: feeds traceback back to Agent 2   |
   |   for auto-correction (max 3 retries)         |
   +-----------------------------------------------+
                           |
                           v
   +-----------------------------------------------+
   | 4. Insight & Chart Recommendation Agent       |
   | - Analyzes result dimensions and datatypes    |
   | - Selects chart type: Bar / Line / Pie / KPI  |
   | - Streams summary insights to React Recharts  |
   +-----------------------------------------------+
```

### 3.2 SQL Sandboxing & Execution Safety
**Critical Security Concern:** LLM hallucinating or injecting destructive commands (`DROP TABLE`, `UPDATE`, `ATTACH DATABASE`, or prompt injection attacks).

**Multi-Layer Security Architecture:**
1. **Static AST Analysis:** Use an SQL parser (e.g., `sqlglot` or `sqlparse` in Python) to inspect query statement types. Reject any statement that is not an explicit `Select`.
2. **SQLite Connection Flags:**
   ```python
   import sqlite3

   # Open connection in strict URI read-only mode:
   conn = sqlite3.connect("file:analytics_dataset.db?mode=ro", uri=True)
   cursor = conn.cursor()
   ```
3. **Execution Timeout / Resource Quota:** Execute queries with a strict execution deadline (e.g., 3 seconds) using `asyncio.wait_for` to mitigate denial-of-service queries like Cartesian joins (`SELECT * FROM table1, table2, table3`).

### 3.3 Dynamic Schema Inference for CSV Uploads
- Upon file upload, infer datatypes using chunked streaming:
  - Check sample rows: Cast to `INT`, `FLOAT`, `DATETIME`, or fall back to `TEXT`.
  - Automatically create corresponding SQLite schema and insert rows using bulk transactions (`executemany`).
