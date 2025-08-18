<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **REACT NOTES** [ **/>**](https://react.dev/learn) 🔥🐦‍🔥

<br>

## 🐦‍🔥 GETTING STARTED [ **/>**](https://create-react-app.dev/docs/getting-started/)

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
