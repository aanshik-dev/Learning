let a = "Hello Boss";
let b = 21.999;
let c = true;
let d = null;
let e = undefined;
let f = 55;

console.log(a, b, c, d, e, f);
console.log(typeof a, typeof b, typeof c, typeof d, typeof e, typeof f);

let obj = {
  "name": "Rohit",
  "age": 21,
  "gender": "Male"
};
console.log(obj);
console.log(`The type is ${typeof obj}`);
obj.salery = 75000;

/////// FOR LOOP
for (let i = 0; i < 2; i++) {
  console.log(i);
}

/////// FORIN LOOP
for (const key in obj) {
  const element = obj[key];
  console.log(key, ":", element);
}

/////// FOROF LOOP
for (const i of "Fun") {
  console.log(i);
}

/////// WHILE LOOP
let i = 0;
while (i < 1) {
  console.log(i);
  i++;
}

/////// DO-WHILE LOOP
let j = 0;
do {
  console.log(j);
  j++;
} while (j < 1);

/////// FOREACH LOOP
let matrix = [1, 2, 3];
matrix.forEach((element, idx, arr) => {
  console.log(element, idx, arr);
});

////////// FUNCTIONS
function fun(val) {
  if (val === 0) {
    console.log('Hi');
  } else {
    console.log('Hello');
  }
}

///////// ARROW FUNCTION
const proc = (name) => {
  console.log("Hello", name)
}

fun("0");
proc("Aanshik");


////////// String functions
let str = "Hello! hello Aanshik";
console.log("");
console.log(str.length);
console.log(str.toUpperCase());
console.log(str.toLowerCase());
console.log(str.slice(14, 18));
console.log(str.slice(16));
newStr = str.slice();  // this create a copy of the string
console.log(str.replace("hello", "hi"));
console.log(str.split(" "));
console.log(str.concat(" How are you? ", "All good?"));


//////////// ARRAYS & ITS METHODS
let arr = [21, "hi", 2.4, true];
console.log(`\nArr : [${arr}]    Type : ${typeof arr}    Length : ${arr.length}`);
console.log(typeof arr.toString(), arr.toString());
console.log(arr.join(" and "));
console.log(arr.pop(), arr);
console.log(`Returned Updated length: ${arr.push(false)}    Arr: ${arr}`);
console.log(arr.shift(), arr);
console.log(arr.unshift(25), arr);
console.log("Is Deleted:", delete arr[0], "  ", "Arr:", arr, "  ", typeof arr[0]);    // Memory is not freed
console.log(arr.sort());
console.log(arr.pop(), arr, "\n");
let num = [1, 5, 3, 79, 15, 45]
console.log("Spliced:", num, "  ", num.splice(2, 3, 12, 23, 25), "  ", num);
console.log("Sliced:", num, "  ", num.slice(2, 4), "  ", num.slice(3), "  ", num);
console.log("Reversed:", num, "  ", num.reverse(), "  ", num);

num.forEach((element, idx, arr) => {
  console.log(element, idx, arr);
});
console.log("\n")

arr = [1, 2, 6, 7, 8, 3];
console.log(arr.map((element, idx, arr) => {
  console.log(element, idx, arr);
  return element * (idx + 1);
}));

console.log(arr.filter((element) => {
  console.log(element, element % 2 === 0);
  return element % 2 === 0;
}));
console.log(arr, "\n");

console.log(arr.reduce((prev, curr, idx, arr) => {
  console.log(prev, curr, idx, arr);
  return prev + curr;
}));

console.log(arr.reduceRight((prev, curr, idx, arr) => {
  console.log(prev, curr, idx, arr);
  return prev + curr;     /// reverse of reduce method
}))

console.log(Array.from("Aanshik"));

console.log(Array.from(Array(5).keys()));