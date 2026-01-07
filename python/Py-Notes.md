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

## 🔥 F-Strings

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

## 🐦‍🔥 User Input

```py
num = input("Enter a number: ")
# input data is always a string

num = int(input("Enter a number: "))
# type casted to integer
```

<br>

## 🐦‍🔥 PYTHON STRINGS

Strings can be created by wrapping with `''` or `""` or `''' '''` or `""" """`

```py
# name = 'Aanshik's Phone' # Wrong
name = "Aanshik's Phone" # Right
# different ways are to distinguish between single and double quotes
```

## 🔥 String Methods

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

## 🐦‍🔥 Conditional Statements

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

</div>
</div>
