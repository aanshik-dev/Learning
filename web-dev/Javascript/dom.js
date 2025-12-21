
















document.title = "DOM Manipulation"
document.body.style.backgroundColor = "green"
// window is a global object , which act as the root
// documment is a child of the window object hence window.document.body is equivalent to document.body
let arr = window.document.body.childNodes  // gives text and element both
arr = window.document.body.children  // gives only elements
document.body.children[0].style.backgroundColor = "red"
console.log(document.body.children[0].parentElement);

console.log(arr);
console.log(document.body)
