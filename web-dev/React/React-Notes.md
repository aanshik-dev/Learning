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

## 🐦‍🔥 JSX (Javascript XML)

JSX is a syntax extension that allows writing HTML-like code in JavaScript.

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

Compenents are the building blocks of the React App

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

<br>

## 🐦‍🔥 PROPS

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
    <div>
      <h1>Hello, {name}</h1>
      <p>Age: {age}</p>
    </div>
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

State is the data changes over time within a component.

### 🔥 useState Hook

```js
import { useState } from "react";

function Counter() {
  // Declare state variable or state object
  const [count, setCount] = useState(0);
  const [user, setUser] = useState({ name: "John", age: 25 });

  return (
    <div>
      <p>Count: {count}</p>
      <button onClick={() => setCount(count + 1)}>Increment</button>
      <button onClick={() => setCount(0)}>Reset</button>
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
function UserGreeting(props) {
  if (props.isLoggedIn) {
    // If-else
    return <h1>Welcome back!</h1>;
  }
  return <h1>Please sign up.</h1>;
}

// Ternary operator
function Greeting({ isLoggedIn }) {
  return (
    <div>
      {isLoggedIn ? <h1>Welcome back!</h1> : <h1>Please sign up.</h1>}
      The user is <b>{isLoggedIn ? "currently" : "not"}</b> logged in.
    </div>
  );
}

// Logical && operator
function Mailbox({ unreadMessages }) {
  return (
    <div>
      <h1>Hello!</h1>
      {unreadMessages.length > 0 && (
        <h2>You have {unreadMessages.length} unread messages.</h2>
      )}
    </div>
  );
}

// Immediately Invoked Function Expression (IIFE)
function NumberList({ numbers }) {
  return (
    <div>
      {(() => {
        if (numbers.length === 0) return <p>No numbers</p>;
        if (numbers.length === 1) return <p>Only one number</p>;
        return <p>Multiple numbers</p>;
      })()}
    </div>
  );
}
```

<br>

> 🔸 Install node.js and run the following command:
>
> ```
> npx create-react-app@latest my-app
> ```

> 🔸 To install in the same folder use this command:
>
> ```
> npx create-react-app@latest .
> ```

> 🔸 To run the react app run:
>
> ```
> npm run start
> ```

 <br>

> 📝 NOTE : Make sure create-react-app is not already installed, uninstall it by cmd `uninstall -g create-react-app`
> 🔸 `npx` ( Node package execute ) is used to execute latest node packages without installing them to machine.

This creates a basic react app with required dependencies in **`node_modules`** folder, a public folder for final production and an **`src`** folder in which we are going to create owr react app.

## 🔥 File System

♦️ `node_modules` // Nothing to do, it contain packages
♦️ `public` // it contain a index.html, the entry point of app
♦️ `src` // these are the files used to develop app
&nbsp; &nbsp; &nbsp; 🔸 `App.js`
&nbsp; &nbsp; &nbsp; 🔸 `App.css`
&nbsp; &nbsp; &nbsp; 🔸 `index.js`
&nbsp; &nbsp; &nbsp; 🔸 `index.css`
♦️ package.json // contains data about app and packages

`Index.html` file contain a `div` with ID `root`, in which the `App.js` is rendered by `index.js`

<br>

## 🐦‍🔥 COMPONENTS BASED PROGRAMMING

React apps are made out of components. A component is a piece of the UI (user interface) that has its own logic and appearance. A component can be as small as a button, or as large as an entire page.

```js
function MyButton() {
  return <button>I'm a button</button>;
}
```

> 📝 NOTE : 🔸 React components are JavaScript functions that return markup. Their names always start with Capital letter.
> 🔸 React components are written in JSX for convenient.

<br>

## 🐦‍🔥 JSX - JAVASCRIPT XML

🔸 JSX allows you to write HTML-like code inside JavaScript, and using `{}` inside JSX let us use js inside it.
🔸 The JSX is then compiled to js using babel compiler.

Instead of using plain `React.createElement()` calls, JSX lets you write code that looks similar to HTML.

> Javascript:
>
> ```js
> const element = React.createElement("h1", null, "Hello, World!");
> const element = React.createElement("h1", null, "Hello, " + username + "!");
> ```

> JSX:
>
> ```jsx
> const element = <h1>Hello, World!</h1>;
> const element = <h1>Hello, {username}!</h1>;
> ```

<br>

## 🐦‍🔥 DEFAULT AND NAMED EXPORT

```js
// comp1.mjs
const a = "Aanshik";
const b = 2401037;
const c = "Male";

export default a;
export { b };
export { c };
```

```js
// Renderer file
import data, {b,c} form './comp1.mjs'

console.log(data);    // 'Aanshik'
console.log(b);   //named export
console.log(c);   //name should be the same

```

> 📝 NOTE : We do not write our code in `App.js` rather we create components which can be used at different places using import

<br>

## 🐦‍🔥 PROPS AND STATE

## 🔥 Props - Properties

➡️ Props are used to send data from parent to child component.
➡️ They are read-only, and the child element can't change them, jsut use them.

```js
function Greeting(props) {
  return <h1>Hello, {props.name}!</h1>;
}

export default function App() {
  return <Greeting name="Anshik" />;
}
```

## 🔥 State

State is a way to store data inside a component that can change over time.

➡️ State is local to the component, unlike props which come from outside.
➡️ When state changes, the component re-renders to reflect those changes.

To use them we have to import `{useState}` hook.

```js
import { useState } from "react";

export default function Counter() {
  const [count, setCount] = useState(0); // creates a state named count with initial value 0

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

> 📝 NOTE : Afters every state change the component is rendered/refreshed again

</div>
</div>
