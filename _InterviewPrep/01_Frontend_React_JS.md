# Domain 01: Frontend Engineering, Modern JavaScript & React

This study guide is tailored specifically to your tech stack (**JavaScript, React, Vite, Tailwind CSS, HTML5/CSS3**) and the architectural patterns on your resume (e.g., custom hooks, Axios interceptors, responsive dashboards, data visualizer with Recharts).

---

## 1. Advanced JavaScript (Core Engine & Runtime)

### 1.1 The Event Loop, Call Stack, and Task Queues
JavaScript is single-threaded with a non-blocking, asynchronous concurrency model powered by the runtime engine (V8 in Chrome/Node.js) and the platform environment (browser APIs or libuv in Node.js).

```
   [ Call Stack ]  <--- Synchronous Execution
         |
         v (Web APIs / C++ background threads handle timers, fetch, I/O)
         |
   [ Microtask Queue ]  (Promises, queueMicrotask, MutationObserver)
         |              --> HIGHER PRIORITY (drained completely before next macrotask)
   [ Macrotask Queue ]  (setTimeout, setInterval, setImmediate, I/O, UI rendering)
```

#### Execution Order Example:
```javascript
console.log('1'); // Synchronous -> Stack

setTimeout(() => {
  console.log('2'); // Macrotask Queue
}, 0);

Promise.resolve().then(() => {
  console.log('3'); // Microtask Queue
}).then(() => {
  console.log('4'); // Microtask Queue (chained)
});

console.log('5'); // Synchronous -> Stack

// Output: 1, 5, 3, 4, 2
```

**Key Interview Question:** *Why does a microtask starve macrotasks?*
- **Accepted Answer:** At the end of each task (or turn of the event loop), the engine drains the *entire* microtask queue until empty before picking the next task from the macrotask queue or performing a UI repaint. If microtasks recursively schedule other microtasks, the event loop blocks macrotasks and UI updates, causing browser freezing.

---

### 1.2 Closures, Scope, and Execution Context
- **Lexical Scope:** Inner functions have access to variables declared in their outer lexical environments, even after the outer function has returned.
- **Memory & Garbage Collection:** Closures retain references in memory. If large objects are captured in closures attached to long-lived objects (e.g., global event listeners or intervals), memory leaks occur.

```javascript
// Practical use case: Factory function / Private state
function createRateLimiter(limit, intervalMs) {
  let callCount = 0;
  let resetTime = Date.now() + intervalMs;

  return function execute(fn) {
    const now = Date.now();
    if (now > resetTime) {
      callCount = 0;
      resetTime = now + intervalMs;
    }
    if (callCount < limit) {
      callCount++;
      return fn();
    }
    throw new Error('Rate limit exceeded');
  };
}
```

---

### 1.3 `this` Binding, Prototypal Inheritance & Prototypes
- `this` is evaluated dynamically at invocation time depending on the call site:
  1. **Default Binding:** Global object (`window` in browser, `global` in Node, `undefined` in strict mode).
  2. **Implicit Binding:** Calling `obj.method()` binds `this` to `obj`.
  3. **Explicit Binding:** `.call(thisArg, ...args)`, `.apply(thisArg, [args])`, `.bind(thisArg)`.
  4. **`new` Binding:** Creates a new empty object linked to the constructor's prototype; `this` points to the new instance.
  5. **Arrow Functions:** **Lexical `this`**—arrow functions do not have their own `this`, `arguments`, or `super`. They inherit `this` directly from the enclosing lexical scope at creation time.

- **Prototype Chain:** Every JS object has an internal `[[Prototype]]` link (`__proto__`). When accessing a property:
  1. Checks own properties.
  2. Traverses `[[Prototype]]` chain up to `Object.prototype`.
  3. If still not found, returns `undefined`.

---

### 1.4 Promises, `async/await`, and Error Handling
- A `Promise` represents an eventual completion or failure of an asynchronous operation (States: *pending*, *fulfilled*, *rejected*).
- `async/await` is syntactic sugar over generator functions and promises (`co`-routine pattern).
- **Concurrency control:**
  - `Promise.all([p1, p2])`: Fails fast if *any* promise rejects.
  - `Promise.allSettled([p1, p2])`: Waits for all to resolve or reject; returns array of `{status, value/reason}`.
  - `Promise.race([p1, p2])`: Resolves/rejects as soon as the *first* promise settles.
  - `Promise.any([p1, p2])`: Resolves as soon as the *first* promise fulfills (ignores rejections until all reject with `AggregateError`).

---

## 2. React Internals & Architecture

### 2.1 React 18+ Fiber Architecture & Reconciliation
- **Virtual DOM (VDOM):** Lightweight in-memory representation of real DOM nodes.
- **Diffing Algorithm ($O(n)$ heuristic):**
  1. Two elements of different types will produce different trees (replaces old tree entirely).
  2. The developer can hint with `key` props which child elements are stable across renders.
- **React Fiber:**
  - Reconciliation engine introduced to allow **incremental rendering**.
  - A Fiber node is a JavaScript object representing a unit of work with links (`child`, `sibling`, `return`).
  - Work is split into two phases:
    1. **Render/Reconciliation Phase (Interruptible, Concurrent):** Traverses the fiber tree, computes diffs, creates side-effect list. React can pause/abort this phase when higher-priority events occur (like typing or clicks).
    2. **Commit Phase (Synchronous, Uninterruptible):** Flushes DOM mutations, runs `useLayoutEffect`, then mounts `useEffect` asynchronously.

---

### 2.2 Deep Dive into React Hooks

#### `useState` & `useReducer`
- State updater triggers a re-render. State batching in React 18 is automatic across promises, timeouts, and native event handlers.
- Functional updates: `setCount(prev => prev + 1)` prevents stale closures when updates depend on previous state.

#### `useEffect` vs `useLayoutEffect`
| Feature | `useEffect` | `useLayoutEffect` |
| :--- | :--- | :--- |
| **Execution** | Asynchronous, after browser paint | Synchronous, after DOM mutation, before paint |
| **Use Case** | Data fetching, subscriptions, logging | Measuring DOM (bounding rect), preventing visual flicker |
| **Performance Impact** | Non-blocking | Blocks browser painting if heavy computation is run |

#### `useMemo` & `useCallback`
- `useMemo(() => computeExpensiveValue(a, b), [a, b])`: Caches the result of a calculation between renders.
- `useCallback(fn, deps)`: Equivalent to `useMemo(() => fn, deps)`. Caches the function definition itself to preserve reference equality across renders, avoiding child re-renders wrapped in `React.memo`.

```jsx
// Avoiding unnecessary re-renders in complex dashboards:
const MemoizedChart = React.memo(({ data, onPointSelect }) => {
  return <RechartsLine data={data} onClick={onPointSelect} />;
});

function Dashboard({ records }) {
  const [selectedId, setSelectedId] = useState(null);

  // Reference identity preserved across re-renders
  const handleSelect = useCallback((id) => {
    setSelectedId(id);
  }, []);

  const filteredData = useMemo(() => {
    return records.filter(r => r.status === 'VERIFIED');
  }, [records]);

  return <MemoizedChart data={filteredData} onPointSelect={handleSelect} />;
}
```

#### Custom Hooks
Encapsulate reusable stateful logic without component tree nesting.

```javascript
// Custom Hook for Debounced Search (used in FarmFresh or Insight Forge queries)
import { useState, useEffect } from 'react';

export function useDebounce(value, delayMs = 300) {
  const [debouncedValue, setDebouncedValue] = useState(value);

  useEffect(() => {
    const handler = setTimeout(() => {
      setDebouncedValue(value);
    }, delayMs);

    return () => clearTimeout(handler); // Cleanup on rapid typing
  }, [value, delayMs]);

  return debouncedValue;
}
```

---

### 2.3 State Management & Prop Drilling Solutions
1. **Local State:** `useState`, `useReducer` for form inputs, toggle states, modals.
2. **Context API:** Best for low-frequency global updates (Auth state, Theme, Locale).
   - *Gotcha:* Any change to `Context.Provider` value forces all consumer components to re-render unless memoized or split into separate contexts (`AuthUserContext` vs `AuthDispatchContext`).
3. **Server State vs Client State:**
   - Server state (API cache, pagination) is best handled by libraries like React Query (TanStack Query) or SWR to manage caching, deduplication, and background invalidation.
   - Client state (UI filters, active tabs) handled via Zustand, Redux Toolkit, or Context.

---

### 2.4 React Performance Optimization Techniques
1. **Code Splitting & Lazy Loading:**
   ```jsx
   const FarmAssistChat = React.lazy(() => import('./components/FarmAssistChat'));

   <Suspense fallback={<ChatSkeletonLoader />}>
     <FarmAssistChat />
   </Suspense>
   ```
2. **List Virtualization:** Using `react-window` or `@tanstack/react-virtual` when rendering thousands of items (e.g., crop ledgers or CSV data rows in Insight Forge).
3. **Throttling & Debouncing:** Essential for scroll events, resize handlers, and search input triggers.
4. **Avoiding Anonymous Functions in JSX:** `<button onClick={() => doSomething()} />` creates a new function reference every render, defeating `React.memo` on children.

---

## 3. Tailwind CSS, Vite & Modern Web Tooling

### 3.1 Vite vs Webpack
- **Webpack:** Bundles the entire dependency graph into memory before serving in development. Slow startup times on large codebases.
- **Vite:** Leverages native browser **ES Modules (ESM)** in development. Uses **esbuild** (written in Go) for pre-bundling dependencies ($10\text{-}100\times$ faster than JS-based bundlers). Files are served on-demand over HTTP.
- **Production:** Uses **Rollup** for optimized tree-shaking, chunking, and CSS code splitting.

### 3.2 Tailwind CSS Principles
- **Utility-First:** Atomic CSS classes minimize CSS bundle growth because utility classes are heavily reused.
- **Just-in-Time (JIT) Engine:** Scans template files (`.jsx`, `.html`) and generates only the CSS rules actually utilized.
- **Responsive & Dynamic Design:** Breakpoint prefixes (`sm:`, `md:`, `lg:`, `xl:`), dark mode variant (`dark:`), pseudo-class states (`hover:`, `focus:`, `active:`).
