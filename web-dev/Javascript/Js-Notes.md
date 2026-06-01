<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **JavaScript Notes** 🔥🐦‍🔥

<br>

## 🐦‍🔥 VARIABLES

JavaScript is a dynamically typed language, meaning variables can hold values of any type without explicit declaration.

- **`var`** // Not used widely, because scope is global
- **`const`** // Used to hold constant values cannot be changed later
- **`let`** // Work similar as var but with block scope

> 📝 NOTE : A variable name may contain `a-z, 0-9, _, $` and should not start with a number.

<br>

## 🐦‍🔥 DATA TYPES

### 🔥 Primitive Datatypes (immutable)

- `null` - no value, type object due to historical bug and backward compatibiity
- `string` - text data
- `Number` -integer or floating point
- `boolean` - true or false
- `undefined` - no value
- `BigInt` - large integers
- `Symbol` - unique identifiers

### 🔥 Reference Datatypes (mutable)

- `Object` - Key value pair
- `Array` - ordered Lists
- `Function` - callable Objects
- `Date`, `RegExp`, `Error` etc

### 🔥 Type conversion

```js
// Implicit (coercion)
let result = "5" + 2; // "52" (string concatenation)
let sum = "5" - 2; // 3 (numeric subtraction)

// Explicit
let num = Number("123"); // 123
let str = String(123); // "123"
let bool = Boolean(1); // true
```

<br>

## 🐦‍🔥 COMMENTS

🔸 `//` Singe Line Commments
🔸 `\* Comments *\` Multi line Comments
<br>

## 🐦‍🔥 PRINT STATEMENTS

```js
console.log("Hello World");
console.error("Hello Error");
console.warn("Hello Warn");
console.info("Hello Info");
console.debug("Hello Debug");
console.trace("Hello Trace");
```

<br>

## 🐦‍🔥 OPERATORS

### 🔥 Arithematic Operators

`+`, `-`, `*`, `/`, `%`, `**`

### 🔥 Relational Operators

`===` checks the value as well as type
`==`, `!=`, `!==`, `<`, `>`, `<=`, `>=`

### 🔥 Logical Operators

`&&`, `||`, `!`, `??` null coalescing

> "If not null use this" `??` "else use this"

### 🔥 Unary Operators

`i++` ,`++i` ,`i--` ,`--i`

### 🔥 Bitwise Operators

- `&` // And
- `|` // Or
- `<<` // Left Shift
- `>>` // Right shift
- `^` // Bitwise Or
- `~` // Bitwise Not
- `>>>` // Right shift with zero

### 🔥 Assignment Operators

`=`, `+=`, `-=`, `*=`, `/=`, `%=`, `**=`

### 🔥 Ternary Operator

`condition ? True : False`

<br>

## 🐦‍🔥 FUNCTIONS

```js
// Function Declaration (hoisted)
function greet(name) {
  return `Hello, ${name}!`;
}

// Function Expression (not hoisted)
const greet = function (name) {
  return `Hello, ${name}!`;
};

// Arrow Function (ES6+)
const greet = (name) => {
  return `Hello, ${name}!`;
};

// Arrow Function (implicit return)
const greet = (name) => `Hello, ${name}!`;
```

### 🔥 Parameters and Default Values

```js
function sum(a, b = 0) {
  return a + b;
}

// Rest parameters
function sumAll(a, b, ...numbers) {
  console.log(a, b);
  return numbers.reduce((acc, num) => acc + num, 0);
}
// reduce((accumulator, currentValue) => accumulator + currentValue, initialValue);
```

### 🔥 Higher order Functions

```js
// Functions that take other functions as arguments
function operate(a, b, operation) {
  return operation(a, b);
}

const result = operate(5, 3, (x, y) => x * y);
```

<br>

## 🐦‍🔥 Control Flow

⚡ If else-if else ladder

```js
if (condition) {
  // code
} else if (condition2) {
  // code
} else {
  // code
}
```

⚡Switch Case

```js
switch (expression) {
  case value1:
    // code
    break;
  case value2:
    // code
    break;
  default:
  // code
}
```

<br>

## 🐦‍🔥 LOOP CONSTRUCT

### 🔥 for loop

```js
for (let i = 0; i < num; i++) {
  console.log(i);
  // do something
}
```

### 🔥 for...in loop

```js
for (const key in obj) {
  console.log(key, ":", obj[key]);
  // do something
}
```

### 🔥 for...of loop

```js
for (const iterator of "iterable Object") {
  console.log(i);
  // do something
}
```

### 🔥 while loop

```js
while (condition) {
  console.log(i);
  // do something
}
```

### 🔥 do while loop

```js
do {
  console.log(i);
  // do something
} while (condition);
```

> 📝 NOTE :
> `forEach()` is not a loop but a method of array, forEach() takes a callback function and executes it once for every element in the array.

### 🔥 forEach()

```js
// used for array or any iterable elements
let num = [1, 5, 3, 79, 15, 45];
num.forEach((element, idx, arr) => {
  console.log(element, idx, arr);
});
```

- `break` - breaks the loop
- `continue` - skips the current iteration

<br>

## 🐦‍🔥 STRING FUNCTION

```js
let str1 = "Single quotes";
let str2 = "Double quotes";
let str3 = `Template literal`;
let str4 = String(123); // "123"
```

## 🔥 String Methods

```js
let str = "Hello Aanshik !! ";
```

⚡ Basic methods

- `str.length` - used without ()
- `str[0]` // 'H'
- `str.charAt(0)` // 'H'
- `str.concat(strings,..)` concats strings

⚡ Case Methods

- `str.toUpperCase()`
- `str.toLowerCase()`

⚡ Search Methods

- `str.indexOf("Aanshik")` // -1 if not found
- `str.lastIndexOf("o")`
- `str.includes("Aanshik")` // bool
- `str.startWith("He")` // bool
- `str.endsWith("World")` // bool

⚡ Extract Methods

- `str.slice(start, end)`
- `str.substring(start, end)`
- `str.substr(start, length)`

⚡ Modify Methods

- `str.replace(old, new)`
- `str.repeat(2)` // repeats string 2 times
- `str.trim()` // removes whitespace
- `str.trimStart()`
- `str.trimEnd()`

⚡ Split & Join Methods

- `str.split(",")` // returns an array
- ["Hello", "World"]`.join(" ")` // Hello World

### 🔥 Template Leterals

- They are used when there are many varibles to concatenate, this is called string interpolation
- Format is ``(`I like \${fruit1} \${fruit2} \${fruit3}`)``
- we can use `'` & `"` inside it

```js
const name = "John";
const age = 30;

// String interpolation
const greeting = `Hello, ${name}! You are ${age} years old.`;

// Multi-line strings
const multiLine = `
    Line 1
    Line 2
    Line 3
`;
```

### 🔥 Escape Sequence Characters

> \n , \t , \" , \r are some escape sequence characters which appear to be two char but bahave as one

<br>

## 🐦‍🔥 ARRAYS

- The arrays in js can contain elements with different data types

```js
let arr1 = [1, 2, 3];
let arr2 = new Array(1, 2, 3);
let arr3 = Array.of(1, 2, 3);
let arr4 = Array.from("hello"); // ['h', 'e', 'l', 'l', 'o']
```

### 🔥 Array Methods

```js
let arr = [1, 2, 3];
```

⚡ Mutating Methods

- `arr.push(4)` // [1, 2, 3, 4]
- `arr.pop()` // [1, 2, 3]
- `arr.unshift(0)` // [0, 1, 2, 3]
- `arr.shift()` // [1, 2, 3]
- `arr.splice(start=1, deleteCount=1,'a','b',..)` // [1,'a', 'b', 3]
- `arr.reverse()` // [3, 2, 1]
- `arr.sort()` // [1, 2, 3]

> 📝 NOTE : JavaScript evaluates the Splice method before printing

⚡ Non Mutating Methods

- `arr.concat([4,5])` // [1, 2, 3, 4, 5]
- `arr.slice(1,3)` // [2, 3]
- `arr.join('-')` // '1-2-3'

⚡ Search Methods

- `arr.indexOf(3)` // 2
- `arr.lastIndexOf(3)` // 2
- `arr.includes(3)` // true
- `arr.find(x => x > 1)` // 2, return first element matching condition
- `arr.findIndex(x=> x > 1)` // 1

⚡ Iterator Methods

- `arr.forEach((item, index, arr) => {})`
- `arr.map((item, index, arr) => {})`
- `arr.filter((item, index, arr) => {})`
- `arr.some((item, index, arr) => {})`
- `arr.every((item, index, arr) => {})`
- `arr.reduce((acc, item, index, arr) => {})`
- we can use spice method to create a copy of the array without modifying it as `newArr = arr.splice()`

### 🔥 Destructuring Arrays

```js
const [first, second, ...rest] = [1, 2, 3, 4, 5];
// first = 1, second = 2, rest = [3, 4, 5]

// Swapping variables
let a = 1,
  b = 2;
[a, b] = [b, a]; // a = 2, b = 1
```

<br>

## 🐦‍🔥 OBJECTS

### 🔥 Object Creation

```js
// Oject Literal
const obj1 = {
  name: "John",
  greet() {
    return `Hello, ${this.name}`;
  },
};

// Constructor
const obj2 = new Object();
obj2.name = "Jane";

// Object.create()
const obj3 = Object.create(obj1);
```

### 🔥 Object Methods

```js
const person = {
  name: "John",
  age: 30,
  city: "New York",
};
```

```js
// Access
person.name; // "John"
person["age"]; // 30

// Modification
person.name = "Jane";
person["age"] = 31;
person.country = "USA"; // Add new property
delete person.city; // Remove property

// Check
"name" in person; // true
person.hasOwnProperty("name"); // true

// Keys, values, entries
Object.keys(person); // ["name", "age", "country"]
Object.values(person); // ["Jane", 31, "USA"]
Object.entries(person); // [["name", "Jane"], ["age", 31], ["country", "USA"]]

// Merge objects
Object.assign({}, person, { city: "LA" });
// or with spread operator
const merged = { ...person, ...{ city: "LA" } };

// Freeze/seal
Object.freeze(person); // Cannot add, delete, or modify
Object.seal(person); // Can modify, cannot add/delete
```

### 🔥 Destructuring Objects

```js
const person = { name: "John", age: 30, city: "NYC" };

const { name, age, city = "Default" } = person;
// name = "John", age = 30, city = "NYC"

// Renaming
const { name: firstName, age: yearsOld } = person;
// firstName = "John", yearsOld = 30

// Nested
const {
  address: { street },
} = { address: { street: "123 Main" } };
// street = "123 Main"
```

### 🔥 Getter And Setter

```js
const person = {
  firstName: "John",
  lastName: "Doe",
  get fullName() {
    return `${this.firstName} ${this.lastName}`;
  },
  set fullName(value) {
    [this.firstName, this.lastName] = value.split(" ");
  },
};
```

<br>

## 🐦‍🔥 CLASSES (ES6+)

```js
class Person {
  // Constructor
  constructor(name, age) {
    this.name = name;
    this.age = age;
    this.id = Person.generateId();
  }

  // Static method
  static generateId() {
    return Math.floor(Math.random() * 1000);
  }

  // Instance method
  greet() {
    return `Hello, I'm ${this.name}`;
  }

  // Getter
  get isAdult() {
    return this.age >= 18;
  }

  // Setter
  set newName(value) {
    if (value.length > 0) {
      this.name = value;
    }
  }
}

// Inheritance
class Student extends Person {
  constructor(name, age, grade) {
    super(name, age); // Call parent constructor
    this.grade = grade;
  }

  // Method overriding
  greet() {
    return `${super.greet()} and I'm in grade ${this.grade}`;
  }
}
```

<br>

## 🐦‍🔥 SCOPE AND HOISTING

### 🔥 Variable Scope

```js
// Global scope
var globalVar = "I'm global";

function testScope() {
  // Function scope
  var functionVar = "I'm in function";
  let blockVar = "I'm block scoped";

  if (true) {
    // Block scope (let/const only)
    let innerBlock = "I'm in block";
    var hoistedVar = "I'm hoisted to function";
  }

  console.log(hoistedVar); // Works
  // console.log(innerBlock); // Error
}
```

### 🔥 Hoisting

Hoisting is a JavaScript mechanism where variables and function declarations are moved to the top of their scope before code execution.

```js
// Variable hoisting (var only)
console.log(x); // undefined (not error)
var x = 5;

// Function hoisting
sayHello(); // Works
function sayHello() {
  console.log("Hello!");
}

// let/const are not hoisted in same way
// console.log(y); // Error
let y = 10;
```

<br>

## 🐦‍🔥 CLOSURES

```js
function createCounter() {
  let count = 0; // Private variable

  return {
    increment() {
      count++;
      return count;
    },
    decrement() {
      count--;
      return count;
    },
  };
}

const counter = createCounter();
console.log(counter.increment()); // 1
console.log(counter.decrement()); // 0
// count is not accessible directly
```

<br>

## 🐦‍🔥 THIS KEYWORD

```js
// Global context
console.log(this); // Window (browser) or global (Node.js)

// Function context
function regularFunc() {
  console.log(this); // Depends on how called
}

// Method context
const obj = {
  name: "John",
  greet() {
    console.log(this.name); // "John"
  },
};

// Arrow functions (lexical this)
const arrowObj = {
  name: "Jane",
  greet: () => {
    console.log(this.name); // undefined (inherits from parent)
  },
};

// Explicit binding
function greet() {
  console.log(this.name);
}
const person = { name: "Bob" };
greet.call(person); // "Bob"
greet.apply(person); // "Bob"
const boundGreet = greet.bind(person);
boundGreet(); // "Bob"
```

<br>

## 🐦‍🔥 CALLBACK AND PROMISES

### 🔥 Callback

It is a function that is passed as an argument to another function, which is executed after the completion of called function.

```js
function doTask(callme) {
  console.log("Task Initiated..");

  setTimeout(() => {
    console.log("Task Acomplished..");
    callback(); // callback happening
  }, 2000);
}

function callme() {
  console.log("Task completed");
}

doTask(callme);
```

### 🔥 Callback Hell

Callback hell is a situation where multiple callbacks are nested inside each other, making it difficult to manage and maintain code.

To prevent this we use the promises

### 🔥 Promises

Promises represent the eventual completion or failure of an asynchronous operation, and its resulting value.

```js
const promise = new Promise((resolve, reject) => {
  // Async operation
  setTimeout(() => {
    const success = true;
    if (success) {
      resolve("Data received");
    } else {
      reject("Error occurred");
    }
  }, 1000);
});

// Using promises
promise
  .then((data) => {
    console.log(data);
    return data.toUpperCase();
  })
  .then((processedData) => {
    console.log(processedData);
  })
  .catch((error) => {
    console.error(error);
  })
  .finally(() => {
    console.log("Cleanup");
  });
```

⚡ Promise methods

- `Promise.all([promise1, promise2]);` // Wait for all to resolve and return the array of results
- `Promise.allSettled([promise1, promise2]);` // All settled (resolve/reject)
- `Promise.race([promise1, promise2]);` // First to settle and its relult returned
- `Promise.any([promise1, promise2]);` // First to resolve/fulfilled

<br>

## 🐦‍🔥 ASYNC / AWAIT

Async/await is used when you want to pause the execution of a function until a promise is resolved, this happen majorly when the execution of function depends on some data delivered by promise.

- `async` function always return a promise
- `await` keyword waits for a promise to resolve
- `await` can only be used inside an `async` function

```js
function getData() {
  return new Promise((resolve) => {
    console.log("Bundling data...");
    if (error) {
      reject("Error Sending Data");
    } else {
      setTimeout(() => {
        resolve("Data Sent");
      }, 2000);
    }
  });
}

async function fetchData() {
  console.log("Fetching data...");
  console.log("Performing Other operations");
  let data = await getData(); // Waits here, promise returned
  console.log("Processing Data");
  console.log("End");
}

fetchData()
  .then((data) => console.log(data))
  .catch((error) => console.error(error));
```

> 📝 NOTE : We can use the Try catch block for error handling and remove the `.then` and `.catch`

⚡ Real API example

```js
async function fetchData() {
  try {
    const response = await fetch("https://api.example.com");
    const data = await response.json();
    return data;
  } catch (error) {
    console.error("Error:", error);
    throw error; // Rethrow the error, Should be catched
  }
}
// Using async function
fetchData()
  .then((data) => console.log(data))
  .catch((error) => console.log(error));
```

- `fetch("...")` returns promise
- `await fetch("...")` returns resolved promise(data/error)
- If error occur then catch block triggered
- If no `try - catch` blocks then `.then`, `.catch` are used

<br>

## 🐦‍🔥 MODULES (ES6+)

### 🔥 Export

```js
// Named exports
export const pi = 3.14159;
export function square(x) {
  return x * x;
}
export class Circle {
  /* ... */
}

// Default export
export default class Rectangle {
  /* ... */
}

// Export list
const a = 1,
  b = 2;
export { a, b };
export { a as alpha, b as beta };
```

### 🔥 Import

```js
// Import named exports
import { pi, square } from "./math.js";
import { pi as PI, square as sq } from "./math.js";
import * as Math from "./math.js";

// Import default export
import Rectangle from "./shapes.js";

// Dynamic import
const module = await import("./module.js");
```

<br>

## 🐦‍🔥 ERROR HANDLING

```js
try {
  // Code that might throw an error
  throw new Error("Something went wrong");

  // Custom error types
  throw new TypeError("Invalid type");
  throw new RangeError("Out of range");
  throw new SyntaxError("Syntax error");
} catch (error) {
  console.error("Error:", error.message);
  console.error("Stack:", error.stack);

  // Rethrow if can't handle
  if (error instanceof TypeError) {
    // Handle TypeError
  } else {
    throw error;
  }
} finally {
  // Cleanup code (always runs)
  console.log("Cleanup");
}

// Custom error class
class ValidationError extends Error {
  constructor(message) {
    super(message);
    this.name = "ValidationError";
  }
}
```

<br>

## 🐦‍🔥 REGULAR EXPRESSIONS

```js
// Creation
const regex1 = /pattern/flags;
const regex2 = new RegExp("pattern", "flags");

// Flags
// g - global, i - case-insensitive, m - multiline, u - unicode, y - sticky, s - dotall

// Methods
const str = "Hello World";
regex.test(str);        // true/false
regex.exec(str);        // Match object
str.match(regex);       // Array of matches
str.matchAll(regex);    // Iterator of matches
str.search(regex);      // Index of first match
str.replace(regex, replacement);
str.replaceAll(regex, replacement);
str.split(regex);       // Split by pattern

// Common patterns
/^abc/      // Starts with abc
/abc$/      // Ends with abc
/a.b/       // a, any char, b
/a*b/       // 0 or more a's then b
/a+b/       // 1 or more a's then b
/a?b/       // 0 or 1 a then b
/a{3}/      // Exactly 3 a's
/a{3,}/     // 3 or more a's
/a{2,4}/    // 2 to 4 a's
/[abc]/     // a, b, or c
/[^abc]/    // Not a, b, or c
/[a-z]/     // a to z
/\d/        // Digit
/\D/        // Not digit
/\w/        // Word char
/\W/        // Not word char
/\s/        // Whitespace
/\S/        // Not whitespace
/(abc)/     // Capturing group
/(?:abc)/   // Non-capturing group
/a(?=b)/    // a followed by b
/a(?!b)/    // a not followed by b
```

<br>

## 🐦‍🔥 DOCUMENT OBJECT MODEL (DOM)

The Document Object Model (DOM) is a programming interface for web documents. It represents the page as a tree of objects that can be manipulated with JavaScript.

```text
Window
└── Document
    └── html
        ├── head
        │   ├── title
        │   └── meta
        └── body
            ├── header
            │   └── h1
            ├── main
            │   ├── p
            │   ├── span
            │   └── img
            └── Footer
```

- window is a global object , which act as the root, hence `window.document.body = document.body`

### 🔥 Selecting Elements

⚡ Single Element

```js
// By ID (fastest)
document.getElementById("myId");

// By CSS selector (returns first match)
document.querySelector(".myClass");
document.querySelector("#myId");
document.querySelector("div.active");

// By tag name (returns first)
document.querySelector("div");

// Special selectors
document.documentElement; // <html>
document.head; // <head>
document.body; // <body>
document.forms[0]; // First form
document.images[0]; // First image
document.links[0]; // First link
```

⚡ Multiple Element

```js
// HTMLCollection (live)
document.getElementsByClassName("myClass");
document.getElementsByTagName("div");
document.getElementsByName("username");

// NodeList (usually static with querySelectorAll)
document.querySelectorAll(".myClass");
document.querySelectorAll("div, p, span");
document.querySelectorAll("[data-attr]");
```

### 🔥 Differnce between Collections

```js
// HTMLCollection - live, array-like, no forEach
const liveCollection = document.getElementsByClassName("item");

// NodeList - static (except childNodes), has forEach, ww cannot change the elements directly, instead forEach is used
const staticList = document.querySelectorAll(".item");

// Convert to Array
const array1 = Array.from(liveCollection);
const array2 = [...staticList];
```

<br>

### 🔥 Parent/ Child Navigation

```js
const element = document.querySelector(".child");

// Upward traversal
element.parentElement; // Element parent only
element.parentNode; // All Nodes (elements, text, somments)
element.closest(".parent-class"); // Nearest ancestor matching selector

// Downward traversal
element.children; // Element children only
element.childNodes; // All nodes (elements, text, comments)
element.firstElementChild;
element.lastElementChild;

// Sibling traversal
element.nextElementSibling;
element.previousElementSibling;
element.nextSibling; // Any node type
element.previousSibling; // Any node type
```

---

### 🔥 Creating and Modifying Elements

⚡ Creating Elements

```js
// Create element
const div = document.createElement("div");
const text = document.createTextNode("Hello World");
const comment = document.createComment("This is a comment");
const fragment = document.createDocumentFragment(); // For batch operations

// Create with attributes
const input = document.createElement("input");
input.type = "text";
input.name = "username";
```

⚡ Adding Element to DOM

```js
const parent = document.querySelector(".container");
const newElement = document.createElement("div");

// Append methods
parent.appendChild(newElement); // Add to end
parent.append(newElement, "text node"); // Multiple nodes/text
parent.prepend(newElement); // Add to beginning
parent.insertBefore(newElement, reference); // Insert before specific child
parent.replaceChild(newElement, oldChild); // Replace child

// Insert adjacent HTML
element.insertAdjacentHTML(
  "beforebegin/beforeend/afterbegin/afterend",
  "<div>HTML CODE</div>",
);
element.insertAdjacentText("beforebegin/beforeend/afterbegin/afterend", "Text");
element.insertAdjacentElement(
  "beforebegin/beforeend/afterbegin/afterend",
  "Element",
);

// Using DocumentFragment for performance
const fragment = document.createDocumentFragment();
for (let i = 0; i < 1000; i++) {
  const div = document.createElement("div");
  fragment.appendChild(div);
}
parent.appendChild(fragment);
```

### 🔥 Removing Elements

```js
const element = document.querySelector(".to-remove");

// Remove from parent
element.remove(); // Modern

// Remove all children
while (container.firstChild) {
  container.removeChild(container.firstChild);
}

// Alternative clear methods
container.innerHTML = "";
container.textContent = "";
```

---

### 🔥 Manipulating eLement Properties

⚡ Classes and Attributes

```js
const element = document.querySelector("#myElement");

// Class manipulation
element.className = "new-class"; // Replace all
element.classList.add("new-class"); // Add
element.classList.remove("old-class"); // Remove
element.classList.toggle("active"); // Toggle
element.classList.contains("active"); // Check
element.classList.replace("old", "new"); // Replace

// Attribute manipulation
element.setAttribute("data-id", "123");
element.getAttribute("data-id"); // '123'
element.hasAttribute("data-id"); // true
element.removeAttribute("data-id");
element.attributes; // NamedNodeMap

// Data attributes (dataset)
element.dataset.userId = "123"; // data-user-id="123"
element.dataset.userRole = "admin"; // data-user-role="admin"
console.log(element.dataset.userId); // '123'
```

> 📝 NOTE : We can add custom data attribute to the tags like data-name, data-value which constitute the data set

```js
element.dataset; // returns the data Set
```

---

⚡ Style Manipulation

```js
// Inline styles
element.style.color = "red";
element.style.backgroundColor = "#fff";
element.style.fontSize = "16px";

// Get computed style (actual rendered style)
const computedStyle = window.getComputedStyle(element);
const color = computedStyle.color;

// CSS custom properties
element.style.setProperty("--primary-color", "#007bff");
element.style.getPropertyValue("--primary-color");

// Multiple styles at once
element.style.cssText = "color: red; font-size: 16px;";

// Toggle visibility
element.style.display = "none";
element.style.display = "block";
element.style.visibility = "hidden";
element.style.visibility = "visible";
```

⚡ Content Manipulation

```js
// Text content (safe from XSS)
element.textContent = "Hello World";
const text = element.textContent;

// HTML content (potential XSS risk)
element.innerHTML = "<span>Hello</span>";
const html = element.innerHTML;

// Outer HTML
element.outerHTML = '<div class="new">Content</div>';

// Value for form elements
input.value = "new value";
textarea.value = "text";
select.value = "option1";
checkbox.checked = true;
radio.checked = true;

element.innerText; // give the text in element
element.textContant; // gives text removing the tags
element.outerHTML; // gives itself also along with content
element.innerHTML; // used to get the content of the element including the tags
```

### 🔥 DOM Events

⚡ Event Basics

```js
// Add event listener
element.addEventListener("click", handler, options);

// Event listener options
const options = {
  capture: false, // Bubble phase (default) or capture phase
  once: true, // Remove after first execution
  passive: true, // Never call preventDefault()
  signal: abortSignal, // AbortController signal
};

// Remove event listener
element.removeEventListener("click", handler);

// Event object properties
function handler(event) {
  event.target; // Element that triggered event
  event.currentTarget; // Element with event listener
  event.type; // Event type ('click')
  event.timeStamp; // When event occurred
  event.preventDefault(); // Prevent default action
  event.stopPropagation(); // Stop bubbling
  event.stopImmediatePropagation(); // Stop other handlers
}
```

> 📝 NOTE: Event bubbling occur when parents and child have some overlaping event listner, then by triggering the child javascript by default triggers parents events also, to prevent this we use `stopPropagartion()` method

```js
parent.addEventListner("click", () => {
  console.log("Parent was Clicked");
});
child.addEventListner("click", (e) => {
  e.stopPropagartion();
  console.log("Child was Clicked");
});
```

⚡ Common Event Types

```js
// Mouse events
("click", "dblclick", "mousedown", "mouseup");
("mouseenter", "mouseleave", "mouseover", "mouseout");
("mousemove", "contextmenu");

// Keyboard events
("keydown", "keyup", "keypress");

// Form events
("focus", "blur", "change", "input", "submit", "reset");
("invalid", "select");

// Window events
("load", "DOMContentLoaded", "resize", "scroll");
("beforeunload", "unload", "hashchange");

// Touch events
("touchstart", "touchmove", "touchend", "touchcancel");

// Drag and drop
("dragstart", "drag", "dragend");
("dragenter", "dragover", "dragleave", "drop");

// Media events
("play", "pause", "ended", "volumechange");
```

⚡ Timer and Intervels

```js
let time = setInterval(() => {
  // function
}, 1000);
clearInterval(time);

let timer = setTimeout(() => {
  // function
}, 1000);
clearTimeout(timer);
```

⚡ Event Delegation

```js
// Instead of adding listeners to each child
const list = document.querySelector("#myList");
list.addEventListener("click", (event) => {
  if (event.target.matches("li")) {
    console.log("List item clicked:", event.target.textContent);
  }

  // Using closest() for nested elements
  const item = event.target.closest("li");
  if (item) {
    console.log("Found item:", item);
  }
});
```

⚡ Custom Events

```js
// Create and dispatch custom events
const event = new CustomEvent("myEvent", {
  detail: { message: "Hello World" },
  bubbles: true,
  cancelable: true,
});

element.dispatchEvent(event);

// Listen for custom event
element.addEventListener("myEvent", (e) => {
  console.log(e.detail.message);
});
```

### 🔥 Forms and Inputs

⚡ Form Access and validation

```js
const form = document.querySelector("form");

// Access form elements
form.elements.username; // By name
form.elements["username"]; // By name with brackets
form.querySelector('[name="email"]');

// Form submission
form.addEventListener("submit", (e) => {
  e.preventDefault(); // Prevent page reload

  // Form data
  const formData = new FormData(form);
  const data = Object.fromEntries(formData);

  // Validation
  if (!form.checkValidity()) {
    form.reportValidity();
    return;
  }

  // Submit via AJAX
  fetch("/submit", {
    method: "POST",
    body: formData,
  });
});

// Input events
input.addEventListener("input", handleInput); // Every change
input.addEventListener("change", handleChange); // After blur
input.addEventListener("focus", handleFocus);
input.addEventListener("blur", handleBlur);
```

<br>

## 🐦‍🔥 MODERN DOM APIs

### 🔥 Mutation Observer

```js
// Observe DOM changes
const observer = new MutationObserver((mutations) => {
  mutations.forEach((mutation) => {
    if (mutation.type === "childList") {
      console.log(
        "Nodes added/removed:",
        mutation.addedNodes,
        mutation.removedNodes,
      );
    }
    if (mutation.type === "attributes") {
      console.log("Attribute changed:", mutation.attributeName);
    }
  });
});

// Start observing
observer.observe(element, {
  childList: true,
  attributes: true,
  subtree: true,
  attributeOldValue: true,
  characterData: true,
});

// Stop observing
observer.disconnect();
```

### 🔥 Intersection Observer

```js
// Lazy loading and visibility detection
const observer = new IntersectionObserver(
  (entries) => {
    entries.forEach((entry) => {
      if (entry.isIntersecting) {
        console.log("Element is visible");
        entry.target.classList.add("visible");
        observer.unobserve(entry.target); // Stop observing
      }
    });
  },
  {
    root: null, // Viewport
    rootMargin: "0px",
    threshold: 0.5, // 50% visible
  },
);

// Observe elements
elements.forEach((el) => observer.observe(el));
```

### 🔥 ResizeObserver

```js
// Observe element size changes
const resizeObserver = new ResizeObserver((entries) => {
  for (let entry of entries) {
    console.log("Size changed:", entry.contentRect);
  }
});

resizeObserver.observe(element);
```

</div>
</div>
