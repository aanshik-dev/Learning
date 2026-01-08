<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **PYTHON NOTES** 🔥🐦‍🔥

<br>

## 🐦‍🔥 VARIABLES

A variable is like a container that holds a value. Python is dynamically typed, meaning you `don't have to declare the variable's type` when you define it.

## 🐦‍🔥 DATA TYPES

- `Integer (int)`&nbsp; // By default integeres are big
- `String`&nbsp; // Can be used as 'Str', "Str", '''Str'''
- `float`&nbsp; // number with decimal point
- `boolen (bool)` represent True/False
- `None`
  // There is no double

```py
name = "Aanshik"
age = 20
height = 5.6
print(type(name), type(age), type(height) )

#OUTPUT
# <class 'str'> <class 'int'> <class 'float'>
```

## 🔥 Type Conversion Vs Type Casting

- Type Conversion - implicit - small to big - done by compiler
- **Type Casting** - explicit - big to small - done by user

```py
price = 75.56
percent = price + 5 # Conversion
print(percent)
# Output: 80.56

price = 75.56
percent = int(price) # Casting
print(percent)
# Output: 75
```

<br>

## 🐦‍🔥 COMMENTS

- `#`&nbsp; Singe Line Commments
- `""" """`&nbsp; Multi line Comments

<br>

## 🐦‍🔥 PRINT STATEMENT

```py
print(object(s), sep=' ', end='\n', file=sys.stdout, flush=False)
```

```py
print("Hello World", 45, true)
print(10, 20, sep='-', end=' | ')
print(30, 40, sep='+',file=sys.stdout)
# Output: 10-20 | 30+40

import time
print("Starting process...", end='', flush=True) # Forces immediate display
time.sleep(2)
print(" Done.")
```

- `objects(s)` # single or multiple objects which are printed
- `sep=' '` # it is the connector between objects, by default ' '
- `end='\n'` # it tell what to print after last object, by default '\n'
- `file=sys.stdout` # it tells where the output should be written, by default sys.stdout i.e. console
- `flush=false` # It forces output buffer to be written immediately, by default false, allowing OS to manage

### 🔥 F-Strings

While print() handles basic output, a cleaner and more powerful way to format and print complex strings is using f-strings (Formatted String Literals)

F-strings allow you to embed expressions and variables directly inside string literals by prefixing the string with f or F

```py
item = "coffee"
price = 3.50

# Using print() with commas:
print("The", item, "costs", price)

# Using an f-string (cleaner, faster):
print(f"The {item} costs ${price:.2f}.")
# Output: The coffee costs $3.50.
```

<br>

## 🐦‍🔥 OPERATORS

### 🔥 Arithematic Operators

`+`, `-`, `*`, `/`, `%`, `**`(power)

### 🔥 Relational Operators

`==`, `!=`, `<`, `>`, `<=`, `>=`

### 🔥 Logical Operators

`and`, `or`, `not`

### 🔥 Unary Operators

`i++`, `++i`, `i--`, `--i`

### 🔥 Bitwise Operators

`&`, `|`, `<<`, `>>`, `^`

### 🔥 Assignment Operators

`=`, `+=`, `-=`, `*=`, `/=`, `%=`, `**=`

<br>

## 🐦‍🔥 USER INPUT

```py
num = input("Enter a number: ")
# input data is always a string

num = int(input("Enter a number: "))
# type casted to integer
```

<br>

## 🐦‍🔥 CONDITIONAL STATEMENTS

Conditional Statements are used to decide to do something based on some condition.

```py
if condition:
    # code
elif condition:
    # code
else:
    # code
```

> 📝 NOTE : Python can have indentation error

<br>

## 🐦‍🔥 LOOPS

- Loops are used to iterate through a block of code multiple times.
- `Break` statement is used to break out of the loop.
- `Continue` statement is used to skip the current iteration of the loop.
- `pass` statement is used to do nothing.

```py
while condition:
    # code
```

```py
for item in list:
    # code
```

```py
for item in range(start, end, step):
    # code
```

```py
str = "Aanshik"
for char in str:
    if (char == 'i'):
      print("Found")
      break
else:
  print("Not Found") # code runs when loop runs completely
```

- `range(start = 0, end, step = 1)` // creates a sequence of numbers from start to end-1 with step

```py
print(range(5)) # range(0,5)
seq = range(1,10,2)
print(seq) # range(1,10,2)
print(seq[1]) # 3
print(list(seq)) # [1,3,5,7,9]
range(5, 0 , -1) # [5,4,3,2,1]
```

<br>

## 🐦‍🔥 FUNCTIONS

Functions are blocks of code that perform a specific task which can be reused multiple times in a program, hence reducing redundancy.

- we can return multiple values from a function

```py
def prodSum(a, b):
    return a + b, a * b

print(prodSum(3, 2)) # (5, 6)
```

- we can set the default values for the parameters

```py
# def sum(a = 2, b): # Error
def Sum(a, b = 2):
    return a + b
print(Sum(3)) # (5, 6)
print(Sum(5,3)) # (8,15)
```

<br>

## 🐦‍🔥 STRINGS

Strings can be created by wrapping with `''` or `""` or `''' '''` or `""" """`

```py
# name = 'Aanshik's Phone' # Wrong
name = "Aanshik's Phone" # Right
# different ways are to distinguish between single and double quotes
```

### 🔥 String Methods

- `Concatenation`// can be done useing `+`
- `len()` // gives length of the string
- `Repetition` // can be done using `*`

---

- `str[i]` // gives character at index i

  > 📝 NOTE : we cannot change the ith char using this, strings are immutable

- `str[i:j]` // gives substring from i to j-1
- `str[i:j:k]` // gives substring from i to j-1 with step k
- `str[i:]` // gives substring from i to end
- `str[:j]` // gives substring from start to j-1
- `str[-i:-j]` // gives substring from -i to -j-1, minus indexing is allowed and starts from end with -1
- `str[::-1]` // gives reversed string

---

- `endswith("word")` // checks if string ends with word
- `startswith("word")` // checks if string starts with word
- `replace("old", "new")` // replaces all old with new
- `find("word")` // gives index of first occurence of word else -1
- `count("word")` // gives count of word
- `index("word")` // gives index of first occurence of word else error
- `rfind("word")` // gives index of last occurence of word else -1

---

- `capitalize()` // capitalizes first letter
- `islower()` // checks if string is lowercase
- `isupper()` // checks if string is uppercase
- `lower()` // converts to lowercase
- `upper()` // converts to uppercase
- `center(width)` // centers string with width
- `isnumeric()` // checks if string is numeric

---

- `title()` // capitalizes first letter of each word
- `swapcase()` // converts lowercase to uppercase and vice versa
- `strip()` // removes leading and trailing spaces
- `split()` // splits string into list of words`
- `join()` // joins list of words into string
- `join(separator)` // joins list of words into string with separator

<br>

## 🐦‍🔥 LISTS and TOUPLE

- Lists are similar to arrays, but they are mutable while Tuples are immutable, once created cannot be changed.

- There can be different data types in a list

- Lists are enclosed in square brackets `[]` and Tuples are enclosed in round brackets `()`

```py
list = [1,"Python", 3]
tuple = (1, 2, "CPP")
print(list) # [1, "Python", 3]
print(tuple) # (1, 2, 3)
```

- we can access the elements of the list and tuple using index

```py
print(list[0]) # 1
print(list[1]) # "Python"
print(tuple[2]) # CPP
```

```Py
tup = (1,) # Tuple with single element
tup = (1) # Integer
tup = () # Empty tuple is also valid
```

### 🔥 List Methods

- `append()` // adds element to the end of the list
- `pop()` // removes last element
- `remove(element)` // removes first occurence of element

---

- `sort()` // sorts the list
- `sort(reverse=True)` // sorts the list in reverse order, Sorting is not only done with numbers but with strings as well

```py
list = ["S", "V", "A", "b", "z"]
list.sort() # ['A', 'S', 'V', 'b', 'z']
list.sort(reverse=True) # ['z', 'V', 'S', 'b', 'A']
```

---

- `insert(index, element)` // inserts element at index
- `clear()` // removes all elements
- `index(element)` // returns index of first occurence of element
- `count(element)` // returns count of element
- `reverse()` // reverses the list

---

- `list.copy()` // returns a shallow copy of the list, not avaliable for the Tuple

```py
ls = [1, 2, 3]
list2 = ls.copy() # shallow copy created, a new list is created but the element objects are shared
print(list2) # [1, 2, 3] both list point to the same object
ls[0] = 4 # it does not affect the other list, only first pointer points to new integer object 4
print(ls) # [4, 2, 3]
```

---

Slicing in list is similar to the strings

```py
list = [1,2,3,4,5]
print(list[1:]) # [2, 3, 4, 5]
print(list[:3]) # [1, 2, 3]
print(list[1:3]) # [2, 3]
print(list[::2]) # [1, 3, 5]
print(list[::-1]) # [5, 4, 3, 2, 1]
```

### 🔥 Tuple Methods

- `count(element)` // returns count of element
- `index(element)` // returns index of first occurence of element

<br>

## 🐦‍🔥 DICTIONARY

- A dictionary is a collection of key-value pairs.
- They are enclosed in curly braces `{}`
- They are unordered, mutabe, and do not allow duplicate keys.
- They are indexed by keys, which can be of any immutable type.
- keys cannot be list or dictionary, but values can be any data type

```py
dict = {
  "name": "Aanshik",
  "marks": {
    "Physics": 98,
    "Chemistry": 95,
    "Maths": 96
    },
  18 : true
  }
print(dict) # {'name': 'Aanshik', 'marks': {'Physics': 98, 'Chemistry': 95, 'Maths': 96}, 18: True}
dict["name"] = "Vinay"
print(dict["name"]) # Vinay
```

### 🔥 Dictionary Methods

- `keys()` // returns a list of keys
- `values()` // returns a list of values
- `items()` // returns a list of tuples of key-value pairs

```py
dict = {
  "name": "Aanshik",
  18 : true
  }
print(dict.keys()) # dict_keys(['name', 18])
print(dict.values()) # dict_values(['Aanshik', True])
print(dict.items()) # dict_items([('name', 'Aanshik'), (18, True)])
print(list(dict.keys())) # ['name', 18] dict keys type casted to list
```

- `dict["key"]` returns value, error when does not exist
- `get(key, default=None)` // returns the value of the key if it exists, otherwise none
- `pop(key, default=None)` // removes and returns the value of the key if it exists
- `update(dict)` // updates the dictionary with the key-value pairs from another dictionary
- `popitem()` // removes and returns last key-value pair

<br>

## 🐦‍🔥 SET

- Set is a mutable collection of unordered, unique and immutable objects
- we cannot have list, and dictionary in set as they are mutable
- Set is enclosed in curly braces `{}`

```py
set = {1, 2, 3, 4, 5}
print(set) # {1, 3, 2 , 5 , 4} ordered is not maintained
```

### 🔥 Set Methods

- `add(element)` // adds element to set
- `remove(element)` // removes element from set, error if not present
- `discard(element)` // removes element from set if present
- `pop()` // removes and returns an arbitrary element from the set
- `clear()` // removes all elements from the set
- `copy()` // returns a shallow copy of the set
- `set1.union(set2)` // returns a union of sets
- `set1.intersection(set2)` // returns an intersection of sets

```py
set = {1, 2, 3, 4, 5}
print(set) # {1, 3, 2 , 5 , 4}
set.add(6)
print(set) # {1, 3, 2 , 5 , 4, 6}
set.remove(6)
print(set) # {1, 3, 2 , 5 , 4}
set.discard(6)
print(set) # {1, 3, 2 , 5 , 4}
set.pop()
print(set) # {1, 3, 4 , 5 }
set.clear()
print(set) # set()
```

<br>

## 🐦‍🔥 FILE HANDLING

File handling is a process of creating, reading, updating and deleting files in a computer system.

- `open(file, mode = 'r')` // creates a file object

```py
f = open("file.txt", "r")
# MODES
# 'r' - read mode (default)
# 'W' - write mode(overwrites)
# 'a' - append mode
# 'x' - create mode
# 't' - text mode (default)
# 'b' - binary mode
# '+' - update mode (read/write)
# 'w+' - write and read mode
# 'a+' - append and read mode
```

> if a non existing file is opened in `a` or `w` mode then it is created

---

- `close()` // closes the file object
- `read()` // reads the entire content of the file
- `readline()` // reads a single line from the file
- `write(string)` // writes a string to the file
- `seek(offset, from)` // moves the cursor to a specific position in the file

```py
f = open("file.txt", "r")
print(f.read()) # prints entire content
f.close()

f = open("file.txt", "r")
print(f.readline()) # prints 1st line
f.close()
```

</div>
</div>
