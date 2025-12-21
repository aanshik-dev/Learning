<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **JavaScript Notes** 🔥🐦‍🔥

<br>

## 🐦‍🔥 VARIABLES

♦️ **`var`**&nbsp; // Not used widely, because scope is global

♦️ **`const`**&nbsp; // Used to hold constant values cannot be changed later

♦️ **`let`**&nbsp; // Work similar as var but with block scope

> 📝 NOTE : A variable name may contain `a-z, 0-9, _, $` and should not start with a number.

<br>

## 🐦‍🔥 COMMENTS

🔸 `//`&nbsp; Singe Line Commments
🔸 `\* *\`&nbsp; Multi line Comments

<br>

## 🐦‍🔥 PRIMITIVE DATA TYPE

🔸 `null`&nbsp; // Reported as object in Browser
🔸 `number`
🔸 `string`
🔸 `symbol`
🔸 `undefined`
🔸 `boolean`
🔸 `bigint`

<br>

## 🐦‍🔥 OBJECTS

> ```js
> let obj = {
>   name: "Rohit",
>   age: 21,
>   gender: "Male",
> }; // I am an Object
> ```

> 📝 NOTE : later we can add new keys to the object like
> &nbsp; &nbsp; &nbsp; // obj.salery = 75000

<br>

## 🐦‍🔥 OPERATORS

## 🔥 Arithematic Operators

🔸 `+`
🔸 `-`
🔸 `*`
🔸 `/`
🔸 `%`
🔸 `**`

## 🔥 Relational Operators

🔸 `===`&nbsp; checks the value as well as type
🔸 `==`
🔸 `!=`
🔸 `<`
🔸 `>`
🔸 `<=`
🔸 `>=`

## 🔥 Logical Operators

🔸 `and`
🔸 `or`
🔸 `not`

## 🔥 Unary Operators

🔸 `i++`
🔸 `++i`
🔸 `i--`
🔸 `--i`

## 🔥 Bitwise Operators

🔸 `&` // And
🔸 `|` // Or
🔸 `<<` // Left Shift
🔸 `>>` // Right shift
🔸 `^` // Bitwise Or
🔸 `~` // Bitwise Not
🔸 `>>>` // Right shift with zero

## 🔥 Assignment Operators

🔸 `=`
🔸 `+=`
🔸 `-=`
🔸 `*=`
🔸 `/=`
🔸 `%=`
🔸 `**=`

> 📝 NOTE : REPL- Read Evaluate Print Loop is feature of node which can run in cmd using node
> &nbsp; &nbsp; just write `node repl` and press enter
> &nbsp; &nbsp; After that simply do `5 + 12` to perform operation

<br>

## 🐦‍🔥 LOOP CONSTRUCT

## 🔥 for loop

> ```js
> for (let i = 0; i < num; i++) {
>   console.log(i);
>   // do something
> }
> ```

## 🔥 forin loop

```js
for (const key in obj) {
  const element = obj[key];
  console.log(key, ":", element);
  // do something
}
```

## 🔥 for of loop

> ```js
> for (const iterator of "iterable Object") {
>   console.log(i);
>   // do something
> }
> ```

## 🔥 while loop

> ```js
> while (condition) {
>   console.log(i);
>   // do something
> }
> ```

## 🔥 do while loop

> ```js
> do {
>   console.log(i);
>   // do something
> } while (condition);
> ```

## 🔥 forEach

> // used for array or any iterable elements

> ```js
> let num = [1, 5, 3, 79, 15, 45];
> num.forEach((element, idx, arr) => {
>   console.log(element, idx, arr);
> });
> ```

<br>

## 🐦‍🔥 FUNCTIONS

## 🔥 simple function

```js
function fun(val) {
  if (val === 0) {
    console.log("Hi");
  } else {
    console.log("Hello");
  }
}
```

## 🔥 arrow function

```js
const proc = (name) => {
  console.log("hello", name);
};
```

> 📝 NOTE : Template leterals are used when there are many varibles to concatenate, this is called string interpolation
> format is `` ( `I like \${fruit1} \${fruit2} \${fruit3}` ) ``
> we can use `'` & `"` inside it

## 🔥 ESCAPE SEQUENCE CHARACTERS

> \n , \t , \" , \r are some escape sequence characters which appear to be two char but bahave as one

<br>

## 🐦‍🔥 STRING FUNCTION

## 🔥 String functions

> ```js
> let str = "Hello! hello Aanshik";
> console.log("");
> console.log(str.length);
> console.log(str.toUpperCase());
> console.log(str.toLowerCase());
> console.log(str.slice(14, 18));
> console.log(str.slice(16));
> console.log(str.replace("hello", "hi"));
> console.log(str.split(" "));
> console.log(str.concat(" How are you? ", "All good?"));
> ```

<br>

## 🐦‍🔥 ARRAYS IN JS

> Note: 🔸 The arrays in js can contain elements with different data types
> 🔸 we can use spice method to create a copy of the array without modifying it as `newArr = arr.lice()`

<br>

## 🐦‍🔥 DOCUMENT OBJECT MODEL (DOM)

> 📝 NOTE :
> 🔸 documment is a child of the window object hence window.document.body is equivalent to document.body
> 🔸 window is a global object , which act as the root

> ```js
> document.designMode = "on";
> document.title = "DOM Manipulation";
> document.body.style.backgroundColor = "green";
> ```

> ```js
> document.body.children[0].parentElement; // Body itself;
> ```

> ```js
> // Gives all child including the element and text spaces
> window.document.body.childNodes;
> document.body.firstChild;
> document.body.lastChild;
> document.body.children[0].children[0].nextSibling;
> document.body.children[0].children[0].PreviousSibling;
> ```

> ```js
> // Gives only the child element
> window.document.body.children;
> document.body.firstElementChild;
> document.body.lastElementChild;
> document.body.children[0].children[0].nextElementSibling;
> document.body.children[0].children[0].previousElementSibling;
> ```

> ```js
> document.getElementById("Id");
> document.getElementsByClass("Class");
> ```

> ```js
> document.querySelector(".class or #id");
> // selects only the first matching element
> document.querySelectorAll(".class or #id");
> // this gives a collection and we can not directly apply the css property to all the elements rather we need to use loop (forEach)
> ```

> ```js
> document.getElementByTagName("div"); // gives all div
> ```

> ```js
> element.matches("Selector Name");
> // returns boolean if the element has the css selector
> element.closest("Selector");
> // returns boolean if the closest ancistor has css selector
> element.contain("Selector");
> // returns boolen if the element contain the selector or itself is the selector
> ```

> ```js
> element.innerText; // give the text in element
> element.textContant; // gives text removing the tags
> element.outerHTML; // gives itself also along with content
> element.innerHTML; // used to get the content of the element including the tags
> ```

> ```js
> element.tagName; // gives the tag of element
> element.nodeName; // gives the node name of element
> ```

> // Node name include everything, comments, texts, etc.

> ```js
> element.hidden; // gives if hidden
> element.hidden = true; // sets hidden
> ```

> ```js
> element.hasAttribute;
> element.getAttribute;
> element.setAttribute;
> element.removeAttribute;
> ```

> ```js
> element.dataset; // returns the data-set of the element
> ```

> 📝 NOTE : // NOTE: We can add custom data attribute to the tags like data-name, data-value which constitute the data set

> ```js
> let div = document.createElement("div");
> div.setAttribute("class", "ClassName");
> element.append(div);
> element.prepend(div);
> element.before(div);
> element.after(div);
> element.replaceWith(div);
> element.remove();
> element.className;
> element.classList;
> element.classList.add / remove;
> element.classList.toggle;
> ```

> ```
> element.insertAdjacentHTML("beforebegin/beforeend/afterbegin/afterend", "HTML Code");
> element.insertAdjacentText("beforebegin/beforeend/afterbegin/afterend", "Text");
> element.insertAdjacentElement("beforebegin/beforeend/afterbegin/afterend", "Element");
> ```

## 🔥 EVENT LISTNER

> ```js
> element.addEventListner("click", () => {
>   console.log("I was Clicked");
> });
> element.removeEventListner("click", () => {
>   console.log("I was Clicked");
> });
> ```

> 📝 NOTE: Event bubbling occur when parents and child have some overlaping event listner, then by triggering the child javascript by default triggers parents events also, to prevent this we use `stopPropagartion()` method

> ```js
> parent.addEventListner("click", () => {
>   console.log("Parent was Clicked");
> });
> child.addEventListner("click", (e) => {
>   e.stopPropagartion();
>   console.log("Child was Clicked");
> });
> ```

> ```js
> let time = setInterval(() => {
>   // function
> }, 1000);
> clearInterval(time)> ;
>
> let timer = setTimeout(() => {
>   // function
> }, 1000);
> clearTimeout(timer);
> ```

## ✨🏐🔥💥⭕❌❕❓⁉️💯⚜️✅🌐🟤🟡🟠🔴🟢🟥🟧🟨🟩🟦🟪▪️▫️🔸🔹♦️⚡❤️‍🔥💖💫🔺🔻🐦‍🔥 📝👁️👀

</div>
</div>
