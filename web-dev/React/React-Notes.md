<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **REACT NOTES** [ **/>**](https://react.dev/learn) 🔥🐦‍🔥

<br>

## 🐦‍🔥 WHAT IS REACT?

React is a JavaScript library for building user interfaces, primarily for single-page applications (SPAs). It's component-based and uses a virtual DOM for efficient updates

<br>

## 🐦‍🔥 GETTING STARTED [ **/>**](https://create-react-app.dev/docs/getting-started/)

### 🔥 Prerequisites

- Node.js (v14.0.0 or later)
- npm or yarn
- Basic HTML, CSS and Javascript Knowledge

### 🔥 Vite

```bash
# Create Vite React project
npm create vite@latest
# or
yarn create vite my-app

cd my-app
npm install
npm run dev
```

> `npx` ( Node package execute ) is used to execute latest node packages without installing them to machine.

### 🔥 Project Structure

```text
my-app/
├── node_modules/
├── public/
│   ├── index.html
│   ├── favicon.ico
│   └── manifest.json
├── src/
│   ├── App.css
│   ├── App.jsx
│   ├── index.css
│   ├── main.jsx
│   └── (components, hooks, pages, etc.)
├── index.html
├── package-lock.json
├── package.json
├── README.md
└── vite.config.js
```

<br>

## 🐦‍🔥 JSX (Javascript XML)

- JSX is a syntax extension that allows writing HTML-like code in JavaScript.
- The JSX is then compiled to js using babel compiler.
- Instead of using plain `React.createElement()` calls, JSX lets you write code that looks similar to HTML.

⚡ JavaScript

```js
const element = React.createElement("h1", null, "Hello, World!");
const element = React.createElement("h1", null, "Hello, " + username + "!");
```

⚡ JSX

```js
// JSX Example
const element = <h1>Hello, React!</h1>;

// Embedding expressions
const name = "John";
const element = <h1>Hello, {name}!</h1>;

// JSX is an expression too
function greet(user) {
  if (user) {
    return <h1>Hello, {user}!</h1>;
  }
  return <h1>Hello, Stranger!</h1>;
}
```

### 🔥 JSX Rules

- Must return a single parent element (use fragments `<> </>`)
- class becomes `className`
- HTML attributes use `camelCase` (className, onClick, htmlFor)
- Must close all tags (`<img />`, `<br />`)
- JavaScript expressions inside `{ }`
- Inline styles are objects: `style={{color: 'red'}}`

<br>

## 🐦‍🔥 COMPONENTS

- Compenents are the `building blocks` of the React App
- React components are JavaScript functions that return markup. Their names always start with `Capital` letter.
- React components are written in `JSX` for convenient.

⚡ Functional Components (Modern)

```js
// Simple functional component
function Welcome(props) {
  return <h1>Hello, {props.name}</h1>;
}

// Arrow function syntax
const Welcome = (props) => {
  return <h1>Hello, {props.name}</h1>;
};

// Implicit return
const Welcome = ({ name }) => <h1>Hello, {name}</h1>;
```

⚡ Class Components (Used Earlier)

```js
import React, { Component } from "react";

class Welcome extends Component {
  render() {
    return <h1>Hello, {this.props.name}</h1>;
  }
}
```

## 🐦‍🔥 DEFAULT AND NAMED EXPORT

⚡ comp.mjs

```js
const a = "Aanshik";
const b = 2401037;
const c = "Male";

export default a; // default export only one
export { b }; // named export
export { c }; // can be many
```

⚡ Renderer file

```js
import data from "./comp.mjs";
import { b, c } from "./comp.mjs";

console.log(data); // 'Aanshik'
console.log(b); // 2401037
console.log(c); // Male
```

|    X    |     Export      |    Import     | Quantity |
| :-----: | :-------------: | :-----------: | :------: |
|  Named  |   Exact Name    | `{Same Name}` |   Many   |
| Default | Default keyword |   Any Alias   |   One    |

<br>

## 🐦‍🔥 PROPS (Properties)

- Props are used to send data from parent to child component.
- They are read-only, and the child element can't change them, jsut use them.

```js
// Parent Component
function App() {
  return (
    <div>
      <Welcome name="John" age={25} />
      <Welcome name="Jane" age={30} />
    </div>
  );
}

// Child Component
function Welcome(props) {
  return (
    <div>
      <h1>Hello, {props.name}</h1>
      <p>Age: {props.age}</p>
    </div>
  );
}

// Destructuring props
function Welcome({ name, age }) {
  return (
    <h1>
      Name: {name} Age: {age}
    </h1>
  );
}

// Default props
Welcome.defaultProps = {
  name: "Guest",
  age: 18,
};

// PropTypes (type checking)
import PropTypes from "prop-types";

Welcome.propTypes = {
  name: PropTypes.string.isRequired,
  age: PropTypes.number,
};
```

<br>

## 🐦‍🔥 STATE

State is a way to store data inside a component that can change over time.

- State is local to the component, unlike props which come from outside.
- When state changes, the component re-renders to reflect those changes.

### 🔥 useState Hook

```js
import { useState } from "react";

function Counter() {
  const [count, setCount] = useState(0); // creates count state, initial value 0
  function increase() {
    setCount(count + 1); // used to change the state
  }
  return (
    <div>
      <h1>Count: {count}</h1>
      <button onClick={increase}>Increase</button>
    </div>
  );
}
```

⚡ Important State Rules:

- Use setState() or setter functions
- State updates may be asynchronous
- State updates are merged (shallow merge)

<br>

## 🐦‍🔥 EVENT HANDLING

```js
function EventExample() {
  const handleClick = (event) => {
    console.log("Button clicked!", event);
  };

  const handleSubmit = (event) => {
    event.preventDefault();
    console.log("Form submitted");
  };

  return (
    <div>
      <button onClick={handleClick}>Click Me</button>

      <form onSubmit={handleSubmit}>
        <input type="text" />
        <button type="submit">Submit</button>
      </form>

      {/* Inline arrow function */}
      <button onClick={() => console.log("Inline handler")}>
        Inline Handler
      </button>
    </div>
  );
}
```

⚡ Commom Events
`onClick`, `onDoubleClick`
`onChange`, `onInput`
`onSubmit`, `onReset`
`onMouseEnter`, `onMouseLeave`
`onKeyDown`, `onKeyUp`, `onKeyPress`
`onFocus`, `onBlur`
`onLoad`, `onError`

<br>

## 🐦‍🔥 Conditional Rendering

```js
// If-else
function UserGreeting(props) {
  if (props.isLoggedIn) {
    return <h1>Welcome back!</h1>;
  }
  return <h1>Please Sign Up.</h1>;
}

// Ternary operator
function Greeting({ isLoggedIn }) {
  return (
    <div>{isLoggedIn ? <h1>Welcome back!</h1> : <h1>Please Sign Up.</h1>}</div>
  );
}

// Logical && operator
function Mailbox({ isLoggedIn }) {
  return (
    <div>
      {isLoggedIn && <h2>Welcome Back!</h2>}
      {!isLoggedIn && <h2>Please Sign Up.</h2>}
    </div>
  );
}
```

<br>

## 🐦‍🔥 LIST AND KEYS

⚡ Keys should be:

- Unique among siblings
- Stable (don't change on re-renders)
- Predictable

```js
function NumberList({ numbers }) {
  // Always use keys for list items
  const listItems = numbers.map((number, index) => (
    <li key={number.id || index}>{number.value}</li>
  ));
  return <ul>{listItems}</ul>;
}

// Better with unique IDs
const todoItems = todos.map((todo) => <li key={todo.id}>{todo.text}</li>);
```

<br>

## 🐦‍🔥 STYLING IN REACT

⚡ Inline Styles

```js
function InlineStyle() {
  const styles = {
    container: {
      padding: "20px",
      backgroundColor: "#f0f0f0",
      borderRadius: "8px",
    },
  };

  return <div style={styles.container}>I am the container</div>;
}
```

⚡ CSS Modules

```css
/* Button.module.css  */
.button {
  background-color: blue;
  color: white;
  padding: 10px 20px;
}
```

```js
// Button.js
import styles from "./Button.module.css";

function Button() {
  return <button className={styles.button}>Click Me</button>;
}
```

⚡ CSS-in-JS Libraries (Styled Components)

```js
import styled from "styled-components";

const StyledButton = styled.button`
  background-color: ${(props) => (props.primary ? "blue" : "gray")};
  color: white;
`;

function App() {
  return <StyledButton primary>Click Me</StyledButton>;
}
```

⚡ Tailwind CSS

```bash
# Installation
npm install tailwindcss @tailwindcss/vite
```

```js
import tailwindcss from "@tailwindcss/vite";
// Configuration in the tailwind.config.js
export default defineConfig({
  plugins: [tailwindcss()],
});
```

```css
@import "tailwindcss";
```

```bash
npx tailwindcss init
```

```js
function TailwindComponent() {
  return (
    <div className="p-6 max-w-sm mx-auto bg-white rounded-xl shadow-lg">
      <h2 className="text-2xl font-bold text-gray-800">Tailwind CSS</h2>
    </div>
  );
}
```

<br>

## 🐦‍🔥 REACT HOOKS

Hooks let you use state and other React features in functional components.

- Hooks are used only at the `top level` of functional component.
- Hooks are not used inside `if, loop, function` etc.
- Hooks start with the `use` word

### 🔥 useState Hook

Used to store and update data(state) inside component locally.

```js
import { useState } from "react";

function Example() {
  const [count, setCount] = useState(0);
  const [user, setUser] = useState({ name: "", age: 0 });
  const [todos, setTodos] = useState([]);

  // Functional updates (when new state depends on previous)
  const increment = () => {
    setCount((prevCount) => prevCount + 1);
  };

  // Updating object (name)
  const updateName = (name) => {
    setUser((prevUser) => ({
      ...prevUser, // Spread operator copies previous state
      name: name,
    }));
  };

  // Updating arrays
  const addTodo = (todo) => {
    setTodos((prevTodos) => [...prevTodos, todo]);
  };

  const removeTodo = (id) => {
    setTodos((prevTodos) => prevTodos.filter((todo) => todo.id !== id));
  };
}
```

### 🔥 UseEffect Hook

Handles side effects (data fetching, Event listner, Component load/update/unmount)

⚡ Syntax

```js
import { useState, useEffect } from "react";

useEffect(() => {
  // side effect code
}, [dependency Array]);
```

⚡ Runs on every render
(componentDidMount + componentDidUpdate)

```js
useEffect(() => {
  console.log("Runs on every render");
}); // rarely used, performance issues
```

⚡ Runs once on mount
(componentDidMount)

- The return inside useEffect is NOT a normal return, It is a registration of a cleanup function, not execution.
- function returns cleanup function, which is stored internally, called on unmount

```js
const [width, setWidth] = useState(window.innerWidth);
// Window Width Resize
useEffect(() => {
  const handleResize = () => {
    setWidth(window.innerWidth);
  };
  window.addEventListener("resize", handleResize);
  // Cleanup Function
  return () => {
    window.removeEventListener("resize", handleResize);
  };
}, []); // Empty dependency array
```

⚡ Runs when State Changes

```js
const [count, setCount] = useState(0);

useEffect(() => {
  console.log(`Count changed to: ${count}`);
}, [count]); // Dependency array
```

### 🔥 useContext Hook

It is helpfull when data is transferred form parent to nested child components. Instead of passing to every level(prop drilling) we share context to child directly.

⚡ Creating and Providing Context

```js
import { createContext, useState } from "react";

// 1. Create Context
export const ThemeContext = createContext();

// 2. Create Provider Component
function AppTheme({ children }) {
  const data = "Theme Data";
  const [theme, setTheme] = useState("light");
  return (
    <ThemeContext.Provider value={{ theme, setTheme, data }}>
      {children}
    </ThemeContext.Provider>
  );
}
export default AppTheme;
```

- In context provider the `{children}` is a special prop, used to render child components

- Wrap the parent componet `(<App />)` with `<AppTheme />` to use the context in children of `<App />`

⚡ Consuming the Context

```js
import AppTheme from "./AppTheme";
import { useContext } from "react";
import { ThemeContext } from "./AppTheme";

function App() {
  return (
    // Wrapping the parent with context
    <AppTheme>
      <div>
        <h1>Toolbar and Other components</h1>
        <ThemedButton />
      </div>
    </AppTheme>
  );
}

function ThemedButton() {
  const { theme, setTheme, data } = useContext(ThemeContext);

  const toggleTheme = () => {
    setTheme(theme === "light" ? "dark" : "light");
  };

  return (
    <button
      onClick={toggleTheme}
      style={{
        backgroundColor: theme === "light" ? "#fff" : "#333",
      }}
    >
      {data}: Toggle Theme
    </button>
  );
}

export default App;
```

### 🔥 useRef Hook

- It is used to access DOM elements directly
- It Stores values that survive re-renders
- Stores mutable things(timers, previous values, etc)
- It return a mutable ref object called `current`

```js
import { useRef, useEffect, useState } from "react";

function RefExample() {
  // 1. Accessing DOM elements
  const inputRef = useRef(null);

  // 2. Storing mutable values that don't trigger re-renders
  const renderCount = useRef(0);
  const intervalRef = useRef(null);
  const [value, setValue] = useState("");

  // Focus input on mount
  useEffect(() => {
    inputRef.current.focus();
    renderCount.current++;
  }, []);

  // Start/stop timer
  const startTimer = () => {
    intervalRef.current = setInterval(() => {
      console.log("Timer tick");
    }, 1000);
  };
  const stopTimer = () => {
    clearInterval(intervalRef.current);
  };

  return (
    <div>
      <input
        ref={inputRef}
        value={value}
        onChange={(e) => setValue(e.target.value)}
      />
    </div>
  );
}
```

### 🔥 useMemo Hook

- It is used to memoize expensive calculations

```js
import { useMemo } from "react";

function ExpensiveComponent({ list, filter }) {
  // This runs on every render
  const filteredList = list.filter((item) => item.includes(filter));

  // This only recalculates when list or filter changes
  const memoizedList = useMemo(() => {
    console.log("Recalculating filtered list...");
    return list.filter((item) => item.includes(filter));
  }, [list, filter]); // Dependency array

  // Complex calculation example
  const expensiveCal = useMemo(() => {
    console.log("Performing expensive calculation...");
    let sum = 0;
    for (let i = 0; i < 10000; i++) {
      sum += i;
    }
    return sum;
  }, []); // Empty array = runs once on mount

  return (
    <div>
      <p>Items: {memoizedList.length}</p>
      <p>Calculation result: {expensiveCal}</p>
    </div>
  );
}
```

### 🔥 useCallback Hook

```js
import { useState, useCallback, memo } from "react";

// Child component
const ChildComponent = memo(({ onClick, data }) => {
  console.log("Child rendered");
  return <button onClick={onClick}>{data}</button>;
});

function ParentComponent() {
  const [count, setCount] = useState(0);
  const [text, setText] = useState("");

  // ❌ Creates new function on every render (causes Child to re-render)
  const badHandleClick = () => {
    console.log("Button clicked", count);
  };

  // ✅ Memoized function (Child doesn't re-render unnecessarily)
  const goodHandleClick = useCallback(() => {
    console.log("Button clicked", count);
  }, [count]); // Only recreates when count changes

  return (
    <div>
      <input
        value={text}
        onChange={(e) => setText(e.target.value)}
        placeholder="Type to trigger re-renders..."
      />
      <ChildComponent onClick={goodHandleClick} data={`Count: ${count}`} />
      <button onClick={() => setCount(count + 1)}>Increment: {count}</button>
    </div>
  );
}
```

<br>

## 🐦‍🔥 CUSTOM HOOK

```js
// useLocalStorage.js
import { useState, useEffect } from "react";

function useLocalStorage(key, initialValue) {
  // Get from localStorage or use initial value
  const [storedValue, setStoredValue] = useState(() => {
    try {
      const item = window.localStorage.getItem(key);
      return item ? JSON.parse(item) : initialValue;
    } catch (error) {
      console.error(error);
      return initialValue;
    }
  });

  // Update localStorage when value changes
  useEffect(() => {
    try {
      window.localStorage.setItem(key, JSON.stringify(storedValue));
    } catch (error) {
      console.error(error);
    }
  }, [key, storedValue]);

  return [storedValue, setStoredValue];
}

// useFetch.js
import { useState, useEffect, useCallback } from "react";

function useFetch(url, options = {}) {
  const [data, setData] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  const fetchData = useCallback(async () => {
    try {
      setLoading(true);
      setError(null);

      const response = await fetch(url, options);
      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
      }

      const result = await response.json();
      setData(result);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  }, [url, options]);

  useEffect(() => {
    fetchData();
  }, [fetchData]);

  const refetch = () => {
    fetchData();
  };

  return { data, loading, error, refetch };
}

// Using custom hooks
function App() {
  const [name, setName] = useLocalStorage("username", "Guest");
  const {
    data: users,
    loading,
    error,
  } = useFetch("https://api.example.com/users");

  return (
    <div>
      <h1>Hello, {name}!</h1>
      <input
        value={name}
        onChange={(e) => setName(e.target.value)}
        placeholder="Enter your name"
      />

      {loading && <p>Loading users...</p>}
      {error && <p>Error: {error}</p>}
      {users && (
        <ul>
          {users.map((user) => (
            <li key={user.id}>{user.name}</li>
          ))}
        </ul>
      )}
    </div>
  );
}
```

<br>

## 🐦‍🔥 Component Lifecycle

```js
import { useState, useEffect, useMemo, useCallback } from "react";

function FunctionalLifecycle() {
  const [count, setCount] = useState(0);

  // componentDidMount + componentWillUnmount
  useEffect(() => {
    console.log("Component mounted");

    return () => {
      console.log("Component will unmount");
    };
  }, []);

  // componentDidUpdate (for specific state/props)
  useEffect(() => {
    console.log("Count updated:", count);
  }, [count]);

  // shouldComponentUpdate equivalent (useMemo, useCallback)
  const memoizedValue = useMemo(() => {
    console.log("Recalculating memoized value");
    return count * 2;
  }, [count]);

  const handleClick = useCallback(() => {
    setCount((prev) => prev + 1);
  }, []);

  // render
  console.log("Render");
  return (
    <div>
      <p>Count: {count}</p>
      <p>Doubled: {memoizedValue}</p>
      <button onClick={handleClick}>Increment</button>
    </div>
  );
}
```

<br>

## 🐦‍🔥 REACT ROUTER

React Router is a client-side routing library for React that helps in navigating between different components without reloading the page.

It enables Single Page Application (SPA) behavior.

⚡ Installation

```bash
npm install react-router-dom
```

⚡ basic Setup (Main.jsx)

- Wrap the `<App />` component with `<BrowserRouter>`

```js
import React from "react";
import ReactDOM from "react-dom/client";
import { BrowserRouter } from "react-router-dom";
import App from "./App";

ReactDOM.createRoot(document.getElementById("root")).render(
  <BrowserRouter>
    <App />
  </BrowserRouter>,
);
```

### 🔥 Routes & route

```js
import { Routes, Route } from "react-router-dom";
import Home from "./pages/Home";
import About from "./pages/About";
import Contact from "./pages/Contact";

function App() {
  return (
    <Routes>
      <Route path="/" element={<Home />} />
      <Route path="/about" element={<About />} />
      <Route path="/contact" element={<Contact />} />
    </Routes>
  );
}

export default App;
```

- `<Routes>` is a container for multiple `<Route>` components.
- `<Route>` has replaced the old `Switch`
- `path` property specifies the URL path for the route.
- `element` property specifies the component to render when the route is matched.
- `exact` property specifies that the route should match the exact URL path, without any trailing slashes, Routes are `exact by default`.

### 🔥 Link Vs NavLink

⚡ Link

```js
import { Link } from "react-router-dom";

<Link to="/about">About</Link>;
```

- It prevents page reload
- It replaced the old `<a>` tag

⚡ NavLink

```js
import { NavLink } from "react-router-dom";

<NavLink to="/about" className={({ isActive }) => (isActive ? "active" : "")}>
  About
</NavLink>;
```

- It adds the `active` class to the link when it's active

### 🔥 useNavigate Hook

It is used for programmatic navigation

```js
import { useNavigate } from "react-router-dom";

function Login() {
  const navigate = useNavigate();

  const handleLogin = () => {
    navigate("/dashboard");
  };

  return <button onClick={handleLogin}>Login</button>;
}
```

⚡ Navigate Options

```js
navigate(-1); // back
navigate(1); // forward
navigate("/", { replace: true }); // replace current history entry
```

### 🔥 Dynamic Routes (useParams)

⚡ Route Definion

```js
<Route path="/user/:id" element={<User />} />
```

⚡ Access Parameter

```js
import { useParams } from "react-router-dom";

function User() {
  const { id } = useParams();
  return <h1>User ID: {id}</h1>;
}
// Example: /user/101
```

### 🔥 Query Parameters (useSearchParams)

```js
import { useSearchParams } from "react-router-dom";

function Products() {
  const [searchParams, setSearchParams] = useSearchParams();
  const category = searchParams.get("category");

  return <h1>Category: {category}</h1>;
}
// Example: /products?category=mobile
```

### 🔥 Nested Routes

⚡ Route Structure

```js
<Route path="/dashboard" element={<Dashboard />}>
  <Route path="profile" element={<Profile />} />
  <Route path="settings" element={<Settings />} />
</Route>
```

⚡ Parent Component

```js
import { Outlet } from "react-router-dom";

function Dashboard() {
  return (
    <div>
      <h1>Dashboard</h1>
      <Outlet />
    </div>
  );
}
```

### 🔥 404 - Not Fount Route

```js
<Route path="*" element={<NotFound />} />
```

### 🔥 Protected Routes (Auth)

```js
import { Navigate } from "react-router-dom";

function PrivateRoute({ children }) {
  const isAuthenticated = false;

  return isAuthenticated ? children : <Navigate to="/login" />;
}
```

⚡ Usage

```js
<Route
  path="/dashboard"
  element={
    <PrivateRoute>
      <Dashboard />
    </PrivateRoute>
  }
/>
```

### 🔥 useLocation Hook

```js
import { useLocation } from "react-router-dom";

function Page() {
  const location = useLocation();

  console.log(location.pathname);
  console.log(location.search);

  return <h1>Current Page</h1>;
}
```

### 🔥 Lazy Loading Routes

```js
import { lazy, Suspense } from "react";

const About = lazy(() => import("./pages/About"));

<Route
  path="/about"
  element={
    <Suspense fallback={<h2>Loading...</h2>}>
      <About />
    </Suspense>
  }
/>;
```

</div>
</div>
