# Domain 03: Authentication, Authorization (RBAC) & Web Security

This guide covers **JWT mechanisms, Token Refresh architectures with Axios interceptors, Role-Based Access Control (RBAC)**, and the **OWASP Top 10** web security standards.

---

## 1. JSON Web Tokens (JWT) Architecture

### 1.1 JWT Anatomy
A JWT is a compact, URL-safe, cryptographically signed string comprising three Base64URL-encoded components separated by dots (`.`):
$$\text{Header} . \text{Payload} . \text{Signature}$$

1. **Header:** Algorithm and token type (`{"alg": "HS256", "typ": "JWT"}`).
2. **Payload (Claims):** Non-sensitive identification data:
   - Registered claims: `sub` (subject/user ID), `exp` (expiration time), `iat` (issued at).
   - Custom claims: `role: "farmer"`, `collectiveId: "col_123"`.
   - *Never put passwords, raw API secrets, or credit card info here—it is easily decoded!*
3. **Signature:** Calculated using the specified algorithm:
   $$\text{HMACSHA256}(\text{base64UrlEncode}(\text{header}) + "." + \text{base64UrlEncode}(\text{payload}), \text{secret})$$

### 1.2 Access Token vs. Refresh Token Strategy
A critical tradeoff in stateless authentication is **security vs. database lookup latency**:
- **Access Token:**
  - Short-lived (e.g., 10 to 15 minutes).
  - Sent in the `Authorization: Bearer <token>` header or Secure cookie with each API request.
  - Verified statelessly in memory by the backend without querying MongoDB or Redis.
- **Refresh Token:**
  - Long-lived (e.g., 7 to 30 days).
  - Stored in an **`HttpOnly`, `Secure`, `SameSite=Strict` cookie** (prevents XSS theft) or a dedicated database table for revocation.
  - Used exclusively at `POST /api/v1/auth/refresh` to issue a new Access Token.
- **Refresh Token Rotation (RTR):**
  - Every time a refresh token is used, it is invalidated and replaced with a new pair.
  - If a revoked/stolen refresh token is reused, the auth service assumes a compromise, invalidates the entire token family, and forces re-login.

---

## 2. Automated Axios Token-Refresh Interceptors

On your resume, *FarmFresh* highlights an **automated Axios token-refresh interceptor**. Here is the canonical production-grade implementation that avoids multiple refresh requests when concurrent API calls fail with 401:

```javascript
import axios from 'axios';

const api = axios.create({
  baseURL: import.meta.env.VITE_API_BASE_URL || 'https://api.farmfresh.com/api/v1',
  withCredentials: true, // Send HttpOnly refresh cookies automatically
});

let isRefreshing = false;
let failedQueue = [];

// Helper to drain the queue once refresh completes or fails
const processQueue = (error, token = null) => {
  failedQueue.forEach((prom) => {
    if (error) {
      prom.reject(error);
    } else {
      prom.resolve(token);
    }
  });
  failedQueue = [];
};

// 1. Request Interceptor: Attach in-memory Access Token
api.interceptors.request.use(
  (config) => {
    const accessToken = window.__ACCESS_TOKEN__; // Or from a secure memory store
    if (accessToken && !config.headers['Authorization']) {
      config.headers['Authorization'] = `Bearer ${accessToken}`;
    }
    return config;
  },
  (error) => Promise.reject(error)
);

// 2. Response Interceptor: Catch 401s and Refresh
api.interceptors.response.use(
  (response) => response,
  async (error) => {
    const originalRequest = error.config;

    // Skip retry for login or refresh endpoints to avoid infinite loops
    if (
      error.response?.status === 401 &&
      !originalRequest._retry &&
      !originalRequest.url.includes('/auth/refresh') &&
      !originalRequest.url.includes('/auth/login')
    ) {
      if (isRefreshing) {
        // Queue concurrent failing requests until refresh finishes
        return new Promise((resolve, reject) => {
          failedQueue.push({ resolve, reject });
        })
          .then((newToken) => {
            originalRequest.headers['Authorization'] = `Bearer ${newToken}`;
            return api(originalRequest);
          })
          .catch((err) => Promise.reject(err));
      }

      originalRequest._retry = true;
      isRefreshing = true;

      try {
        // Request new access token using HttpOnly cookie credentials
        const { data } = await api.post('/auth/refresh');
        const newAccessToken = data.accessToken;
        window.__ACCESS_TOKEN__ = newAccessToken;

        // Drain pending queue
        processQueue(null, newAccessToken);

        // Retry original failed request
        originalRequest.headers['Authorization'] = `Bearer ${newAccessToken}`;
        return api(originalRequest);
      } catch (refreshError) {
        processQueue(refreshError, null);
        // Force logout on failed refresh
        window.__ACCESS_TOKEN__ = null;
        window.location.href = '/login?expired=true';
        return Promise.reject(refreshError);
      } finally {
        isRefreshing = false;
      }
    }

    return Promise.reject(error);
  }
);

export default api;
```

---

## 3. Role-Based Access Control (RBAC)

In your internship and *FarmFresh*, you implemented RBAC for distinct roles: **Farmer**, **Collective**, and **Admin**.

### 3.1 Backend Middleware Implementation (Node.js & Express)

```javascript
// Middleware: Verify JWT and inject user into req
export const authenticate = (req, res, next) => {
  const authHeader = req.headers.authorization;
  if (!authHeader || !authHeader.startsWith('Bearer ')) {
    return res.status(401).json({ message: 'Authentication required. No token provided.' });
  }

  const token = authHeader.split(' ')[1];
  try {
    const decoded = jwt.verify(token, process.env.JWT_SECRET);
    req.user = decoded; // { id: "...", role: "farmer", collectiveId: "..." }
    next();
  } catch (err) {
    if (err.name === 'TokenExpiredError') {
      return res.status(401).json({ message: 'Token expired. Refresh required.' });
    }
    return res.status(403).json({ message: 'Invalid or malformed token.' });
  }
};

// Middleware: Restrict to specific roles
export const authorizeRoles = (...allowedRoles) => {
  return (req, res, next) => {
    if (!req.user || !allowedRoles.includes(req.user.role)) {
      return res.status(403).json({
        message: `Forbidden: Role '${req.user?.role}' does not have permission to access this resource.`
      });
    }
    next();
  };
};

// Route protection in Express:
router.post(
  '/api/v1/pickups/assign-driver',
  authenticate,
  authorizeRoles('collective', 'admin'), // Only Collective and Admin can assign drivers
  pickupController.assignDriver
);
```

### 3.2 Frontend Route Protection in React

```jsx
import { Navigate, Outlet } from 'react-router-dom';
import { useAuth } from '../context/AuthContext';

export const ProtectedRoute = ({ allowedRoles }) => {
  const { user, isLoading } = useAuth();

  if (isLoading) return <div>Loading...</div>;
  if (!user) return <Navigate to="/login" replace />;
  if (allowedRoles && !allowedRoles.includes(user.role)) {
    return <Navigate to="/unauthorized" replace />;
  }

  return <Outlet />;
};

// In AppRouter.jsx:
<Route element={<ProtectedRoute allowedRoles={['admin', 'collective']} />}>
  <Route path="/admin/fleet-dispatch" element={<FleetDispatchDashboard />} />
</Route>
```

---

## 4. Web Application Security & OWASP Top 10

### 4.1 Cross-Site Scripting (XSS)
- **Stored XSS:** Malicious script is saved in DB (e.g., in a crop listing description) and served to other users.
- **Reflected XSS:** Script injected via URL query parameters.
- **Mitigation:**
  - Never use `dangerouslySetInnerHTML` in React unless sanitizing with `DOMPurify`. React automatically escapes strings rendered in JSX (`{userInput}`).
  - Store sensitive auth tokens in `HttpOnly` cookies, preventing JavaScript access (`document.cookie`).
  - Set Content Security Policy (CSP) headers using `helmet`.

### 4.2 Cross-Site Request Forgery (CSRF)
- An attacker tricks an authenticated browser into submitting unauthorized requests to a site where the user is logged in.
- **Mitigation:**
  - Use `SameSite=Strict` or `SameSite=Lax` on authentication cookies.
  - Implement CSRF tokens (Double-Submit Cookie Pattern) for state-changing HTTP methods (`POST`, `PUT`, `DELETE`).

### 4.3 SQL & NoSQL Injection
- **SQL Injection (in *Insight Forge*):** If user-generated or LLM-generated SQL queries are executed directly without controls.
  - *Defense:* Run queries strictly through a read-only database user/connection (`GRANT SELECT ONLY`), use parameter binding, and implement an SQL parser whitelist (disallow `DROP`, `DELETE`, `UPDATE`, `ALTER`, `ATTACH`).
- **NoSQL Injection (in MongoDB):**
  - Example vulnerability: passing `{ username: req.body.username, password: req.body.password }` where an attacker sends `{"$gt": ""}` for password.
  - *Defense:* Sanitize inputs with `express-mongo-sanitize`, use schema validators, and avoid passing raw objects to queries.

### 4.4 CORS (Cross-Origin Resource Sharing)
- Browser-enforced security mechanism preventing websites from making unauthorized requests to a different domain/port.
- **Preflight Request (`OPTIONS`):** Sent automatically by the browser when custom headers (like `Authorization`) or non-simple methods (`PUT`, `DELETE`, `PATCH`) are used.
- **Node.js Express CORS setup:**
  ```javascript
  import cors from 'cors';

  app.use(cors({
    origin: ['https://farmfresh.vercel.app', 'http://localhost:5173'],
    credentials: true, // Allow cookies over CORS
    methods: ['GET', 'POST', 'PUT', 'PATCH', 'DELETE'],
    allowedHeaders: ['Content-Type', 'Authorization']
  }));
  ```
