<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **C++ NOTES** 🔥🐦‍🔥

<br>

## 🐦‍🔥 FACTS

> - The foundation of C++ language is the Standard C language of Dennis Ritchie hence all the library functions of C are valid in C++
> - Block Structured: These are those languages that allow procedures and functions to be declared inside another function
> - C is a Structured language

## 🔥 Keywords in C++

|          |        | Keywords |          |           |
| :------- | :----: | :------: | :------: | --------: |
| auto     | double |   int    |  struct  |       asm |
| break    |  else  |   long   |  switch  |      \_cs |
| case     |  enum  | register |  typeof  |      \_ds |
| char     | extern |  return  |  union   |       far |
| const    | floar  |  short   | unsigned |      huge |
| continue |  for   |  signed  |   void   |      near |
| default  |  goto  |  sizeof  | volatile | interrupt |
| do       |   if   |  static  |  while   |    pascal |

<br>

## 🐦‍🔥 HEADER FILE

> `#include<iostream>`
> This is the preprocessor directive which tells to include the code of this file during compilation

> `using namespace std;`
> many files may contain functions with same name, so we define std file to use by default for functions like cin and cout.

<br>

## 🐦‍🔥 MAIN FUNCTION

> Every c++ code must contain a `main()` funtion and a `return 0;` statement

> ```cpp
> int main(){
>   // rest of the code
>   return 0;
> }
> ```

<br>

## 🐦‍🔥 COUT AND ENDL

<br>

> `cout` is used to print on the screen using `<<`, like `cout << Hello Boss! << how are you ?`

> 📝 NOTE : We declare std as standard file to use functions like cout and cin. Either declare it once at top or write as `std::cout` when using funtions written in it

> ```cpp
> #include <iostream>
> using namespace std;
> int main(){
> cout << "Aanshik is learning CPP" << endl << endl;
> }
> ```

<h3 style="width: 100%; text-align: center; font-size: 20px"> OR </h3>

> ```cpp
> #include <iostream>
> int main(){
> std::cout << "Aanshik is learning CPP" << endl << endl;
> }
> ```

> 📝 NOTE :&nbsp; `endl` is the endline character newly introduced in c++, although `\n` also exist and is faster than `endl`

## 🔥CIN

```cpp
int main(){
  int num;
  cout << "Enter a number: " ;
  cin >> num;
  cout << " The number is : " <<  num << endl;
}
```

<br>

## 🐦‍🔥 DATA TYPES

> 📝 NOTE : variables start with `_` , `a-z`, `A-Z`

## 🔥 Primary Data Types

🔸 `int` Integer : 4 Bytes
🔸 `char` Character : 1 Byte
🔸 `float` Float : 4 Bytes
🔸 `double` Double : 8 Bytes
🔸 `bool` Boolean : 1 Bytes
🔸 `void` Void : Byte
🔸 `wchar_t` Wide Character : 2 Bytes

| 🔥 Derived | 🔥 User Derived | 🔥Modifiers |
| :--------- | :-------------: | ----------: |
| Function   |      Class      |       short |
| Array      |    Structure    |        long |
| Pointer    |      Union      |    unsigned |
| Reference  |      Enum       |      signed |
|            |    Type Def     |       const |

<br>

## 🐦‍🔥 VARIABLES & IDENTIFIERS

## 🔥 Identifiers

> The names of variables, functions, labels, and various other user-defined objects are called identifiers. They start `a-z`, `A-Z` & `_` and following may contain `0-9` also

## 🔥 Variables

> Variables are containers which may hold constants and expressions, they start with a data type followed by an identifier

```cpp
 int num;
 char c = 'A'
 int x = 5, y = 8;
 short int age = 25;
 const PI = 3.1415;
 wchar_t = L'A';
 int infinity = INT_MAX;
```

### 🔥Access Modifiers

> 🔸 `const` is used to prevent future altering the value of identifiers
> 🔸 `volatile` allows system to overwrite the variable

### 🔥 Storage Class Specifiers

> 🔸 `extern` keyword before variable tells the compiler that the variable is defined elsewhere, in an external file
> 🔸 `static` is used to store the variable even after a function return, they retain value for various function calls
> 🔸 `Register` store the variable in the registers of the processor (not recommended)
> 🔸 `auto` makes the type of variable flexible and let compiler decide it

<br>

## 🐦‍🔥 OPERATORS

| 🔥 Arithematic Operators | 🔥 Relational Operators |
| :----------------------: | :---------------------: |
|        🔸 a `+` b        |       🔸 a `==` b       |
|        🔸 a `-` b        |       🔸 a `!=` b       |
|        🔸 a `*` b        |       🔸 a `<` b        |
|        🔸 a `/` b        |       🔸 a `>` b        |
|        🔸 a `%` b        |       🔸 a `<=` b       |
|                          |       🔸 a `>=` b       |

| 🔥 Logical Operators | 🔥 Unary Operators |
| :------------------: | :----------------: |
|     🔸 a `&&` b      |      🔸 `i++`      |
|    🔸 a `\|\|` b     |      🔸 `++i`      |
|       🔸 `!`a        |      🔸 `i--`      |
|                      |      🔸 `--i`      |

| 🔥 Bitwise Operators | 🔥 Assignment Operators |
| :------------------: | :---------------------: |
|      🔸 a `&` b      |       🔸 a `=` b        |
|     🔸 a `\|` b      |       🔸 a `+=` b       |
|      🔸 a `<<`3      |       🔸 a `-=` b       |
|      🔸 a `>>`2      |       🔸 a `*=` b       |
|      🔸 a `^` b      |       🔸 a `/=` b       |
|       🔸 `~` b       |       🔸 a `%=` b       |

> 📝 NOTE : Multiple assignment are possible like
> `int a = b = c = 10`

## 🔥 Pointer Operators

> 🔸 `&` it means 'Address of'
> 🔸 `*` it means 'at Address'

## 🔥 Sizeof and Comma Operators

> 🔸 `sizeof(datatype)` gives size of data type in bytes
> 🔸 `,` is used to strings together several expression

> 📝 NOTE : The `,` operators always evaluate left side as void and then combined with right side becomes the final value
> `int x = (y = 4, y + 1)` in this expression, y = 4 is calculated and then y + 1 is done to finally assign to x as 5

## 🔥 Reference operator &

```cpp
  int var = 10;
  int &ref = var;  // `ref` is alias for 'var'     ref     var
  ref = 20;      // Modifies 'var' directly          \    /
  cout << var;     // Output: 20                      [20]
```

<br>

## 🐦‍🔥 CONDITIONAL STATEMENTS

## 🔥 if.. else-if.. else ladder

```c++
if (int grade > 90){
  cout << "Outstanding !!" << "you got A !!" << endl;
}else if (int grade > 80){
  cout << "Excellent !!" << "you got B !!" << endl;
}else if (int grade > 70){
  cout << "Good !!" << "you got C !!" << endl;
}else if (int grade > 60){
  cout << "Improve !!" << "you got D !!" << endl;
}else if (int grade > 50){
  cout << "Poor !!" << "you got E !!" << endl;
}else if (int grade > 40){
  cout << "Failed !!" << "you got F !!" << endl;
}
```

## 🔥 Switch Case

```cpp
switch(key){
  case a: cout << "Hello" << endl;
          break;
  case b: cout << "I am good" << endl;
          break;
  default: cout << " Bye!!" << endl;
}
```

## 🐦‍🔥 LOOP CONSTRUCT

## 🔥 for loop

```cpp
for (int i = 0; i < num; i++) {
  cout << i << endl;
  // do something
}
```

## 🔥 while loop

```cpp
int i = 0
while (i < 10 ) {
  cout << i << endl;
  // do something
}
```

## 🔥 do while loop

```js
int i = 5
do {
  cout << i << endl;
  // do something
} while (i > 10);
```

## 🔥 for each loop

```cpp
  for (int value : vector) {
    cout << value << endl;
  }     // here value is not index but value itself
```

## 🔥 goto, break and continue

```cpp
// goto
x = 1;
loop1:
  x++;
  if ( x < 10 ) goto loop1;
```

```cpp
// break
for (int i = 0; i < 6; i++) {
  if(i == 4)
    break;
  cout << i << " ";
}                        // Output:  0 1 2 3
```

```cpp
// continue
for (int i = 0; i < 6; i++) {
  if(i == 3)
    continue;
  cout << i << " ";
}                        // Output:  0 1 2 4 5
```

<br>

## 🐦‍🔥 FUNCTIONS

```cpp
#include <iostream>
using namespace std;

int sum(int, int);    // function declaration or Prototype

int main() {
  int a = 10, b = 20;
  int c = sum(a, b);     // function call with arguments

  cout << "Sum of " << a << " and " << b << " is " << c;
  return 0;
}

int sum(int x, int y) {    // function definition
  return x + y;
}
```

> 📝 NOTE : funtion declaration can be skipped if it is written before call. `int x, int y` are parameters and the values passed `a,b` are the arguments.

## 🔥 Recursion

```cpp
int fibo(int num) {
  if (num <= 0)
    return 0;
  if (num > 2)
    return fibo(num - 1) + fibo(num - 2);
  return 1;
}
```

> 📝 NOTE : Recursion of function uses the stack memory after every call new space is allocated and new variables are created and after every return statement control is given to previous call and variables are freed.

> 📝 TASK : read about pass by value and pass by reference

<br>

## 🐦‍🔥 STL - STANDARD TEMPLATE LIBRARY

It is a library of C++ which contain all the prebuilt containers like array, vectors, stack etc and algorithms like sorting etc.

It contains the following:
♦️ `Container`
♦️ `Iterators`
♦️ `Algorithms`
♦️ `Functors`

## 🐦‍🔥 ARRAYS

Arrays in C++ are of two type, one which are basic to C, without any methods, and the other which are included in C++ STL.

## 🔥 Basic C Array

```cpp
// arrays in cpp have fixed size
int arr[5] = {1,2,5,9,7};
char charset[4];
bool truth[] = {true, false, false, true};
```

## 🔥 C++ STL Array

```cpp
#include <array>  // Preprocessor directive for the array
```

```cpp
#include <array>
std::array<int, 5> arr = {1, 2, 3, 4, 5};

// or

#include <array>
use namespace std;
array<int, 5> arr = {1, 2, 3, 4, 5};

```

<br>

## 🐦‍🔥 Array Methods

♦️ Element Access
🔸 `arr.at(i)` bounds-checked access (throws exception if out of range).
🔸 `arr[i]` direct access.
🔸`arr.front()` first element.
🔸`arr.back()` last element.
🔸`arr.data()` pointer to underlying raw array, safe even array is empty.
&nbsp;&nbsp;&nbsp; ▫️ `&arr[0]` also give the same thing but undefined behaviour of pointer when empty array.

♦️ Capacity
🔸`arr.size()` number of elements.
🔸`arr.max_size()` maximum size (same as size() since fixed).
🔸`arr.empty()` checks if array is empty.

♦️ Iterators
🔸`arr.begin()`, `arr.end()` forward iteration.
🔸`arr.rbegin()`, `arr.rend()` reverse iteration.
🔸`arr.cbegin()`, `arr.cend()` const iterators

♦️ Modefiers
🔸`arr.fill(value)` fills entire array with a value.
🔸`arr.swap(other)` swaps contents with another array

<br>

## 🐦‍🔥 VECTORS

> 📝 NOTE
> 🔸 Unlike arrays vectors are dinamic in size.
> 🔸 Vector is part of the standard tempelete library (STL) of cpp. It is the collection of basic data structures like queue, stack etc.
> 🔸 All the basic data types of stl are called STL containers, hence vector is a stl container.

```cpp
#include <vector>  // Preprocessor directive
```

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> vect;
  vector<int> vect = {1, 2, 3, 4, 5};
  vector<int> vect2(vect)    // vect2 = {1, 2, 3, 4, 5}
  vector<int> vect(5, 0);    // size five with value 0
  vector<int> vect(5);          // by default value 0
  vector<char> vect(5);          // by default value \0
  vector<string> vect(5);          // by default value ""
  vector<int> temp(Iterator1, Iterator2);
  // Gives temp Sub vector, iterators are like pointers
  return 0;
}
```

## 🔥 Vector Methods

♦️ Capacity
🔸 `vector.size()` returns number of element in vector
🔸 `vector.capacity()` returns the total capacity of vector before new memory allocation
🔸 `vector.shrink_to_fit();` It is used to reduce the capacity to the size of vector.

```cpp
  vector<int> v(10);
  v = {1, 2, 3, 4, 5};
                                    // OUTPUT:
  cout << v.size() << endl;         // 5
  cout << v.capacity();             // 10
```

♦️ Element Access
🔸 `vector.at(index)` It works same as vector[ index ]
🔸 `vector.front()` first element
🔸 `vector.back()` last element

♦️ Element Write
🔸 `vector.push_back(value)` allocates space and copies/moves value at last
🔸 `vector.emplace_back(value)` allocates space and adds value directly at last

```cpp
    v.push_back(10);       // copies/moves 10 into vector
    v.emplace_back(20);    // constructs 20 directly in place
```

🔸 `vector.pop_back()` deletes last element leaving the space

♦️ Iterators
🔸 `vector.begin()` returns the iterator or the pointer to the first element
🔸 `vector.end()` returns the iterator or the pointer to the `NEXT` to last element

```cpp
vector<int> temp(vect.begin() + 1, vect.begin() + 4);
// Gives a Sub Vector on passinng iterators
  for (auto i : temp) {    //  auto takes data type automatically
    cout << i << " ";
  }
  cout << endl;
```

```cpp
*(vect.begin())  // first element
*(vect.begin())  // Next to last element (Garbage value)
```

> 📝 NOTE : for `(Itr1, Itr2)` the set is like [Itr1, Itr2) with Itr1 included and Itr2 excluded

🔸 `vector.rbegin()` returns the iterator to the last element
🔸 `vector.rend()` returns the iterator to the element `BEFORE` the first elemrent

```cpp
vector<int>::iterator itr;
  for(itr = vect.begin(); itr != vect.end(); itr++) {
    cout << *itr << " ";
  }
```

```cpp
   for( vector<int>::reverse_iterator itr2 = vect.begin(); itr2 != vect.end(); itr2++) {
    cout << *itr2 << " ";
  }

  //   OR
  // vector<int>::reverse_iterator itr2  understood by auto keyword
  for( auto itr2 = vect.begin(); itr2 != vect.end(); itr2++) {
    cout << *itr2 << " ";
  }
```

♦️ Miscellaneous
🔸 `vector.clear()` It clears all the elements and size become 0.
🔸 `vector.erase(Iter)` It clears the element or a range pointed by iter
▫️ `vector.erase(IterSt, IterEnd)`
🔸 `vector.empty()` It tells if vector is empty or not.

🔸 `swap(vect1, vect2)` It swaps two vectors not to values in a vecotor

> 📝 NOTE : At runtime when, `push_back()` is used and no further space is left, then new mamory is allocated with double the size of current array.

## 🔥 Static Vs Dynamic Memory

| Static Allocation             | Dynamic Allocation       |
| :---------------------------- | :----------------------- |
| 🔸 Allocated at complile time | 🔸 Allocated at runtime  |
| 🔸 Stored in Stack Memory     | 🔸 Stored in heap memory |
| 🔸 Example: Array             | 🔸 Example: Vector       |

> 📝 NOTE : For Array dynamic memory allocation is done using the malloc, calloc and realloc functions
> 🔸 `ptr = (int*) malloc(n * sizeof(int));`
> 🔸 `ptr = (int*) calloc(n, sizeof(int));`
> 🔸 `ptr = (int*) realloc(ptr, new_size);`

<br>

## 🐦‍🔥 LISTS

Lists are implented using the doubly link list, and can take entry from both sides

```cpp
#include <list>  // Preprocessor directive
```

```cpp
// Initialization

 list<int> ls;
 list<int> ls1 = {2, 5, 6, 8, 9};
 list<int> ls2(ls1);   // Copy of ls1
 list<int> ls3(5, 0);  // {0, 0, 0, 0, 0}
 list<char> l4(10);    // size 10, all '\0'
```

🔸 `list.push_back()`
🔸 `list.push_front()`
🔸 `list.emplace_back()`
🔸 `list.emplace_front()`
🔸 `list.pop_back()`
🔸 `list.pop_front()`
Other methods like the `clear()`, `erase()`, `empty()`, `size()`,`front()`, `end()`, `begin()`, `end()`, `rbegin()`, `rend()` are same as the vectors.

> 📝 NOTE : We cannot directly use the random index to access elements like ls[4], but we have to use iterators like shown

```cpp
  list<int> l = {10, 20, 30, 40, 50};
  auto it = l.begin();   // points to 10
  advance(it, 3);        // move forward 3 steps
  cout << *it << endl;
```

<br>

## 🐦‍🔥 DEQUE

Deque stands for the Double Ended Queue, means the elements can be inserted and removed from both front and back efficiently.

They have same methods like the lists, just the implementation is done using the queue

```cpp
#include <deque>  // Preprocessor directive
```

```cpp
  deque <int> dq= {1, 5, 9, 4}
```

We can use the random index access in deque like the vector or array, which is not possible in case of list.

<br>

## 🐦‍🔥 PAIR

pair a special container inside the utility library of c++. used to create a pair of same or different datatypes

```cpp
  pair <int, int> p = {1, 5}
  pair <int, char> p1 = {1, 'A'}
  pair <int, pair<char, string>> p2 = {1, {'A', "Student"}}
  cout << p1.first();
  cout << p2.first() << p2.second.first() << p2.second.second();
```

</div>
</div>
