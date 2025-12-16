<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **PYTHON NOTES** 🔥🐦‍🔥

<br>

## 🐦‍🔥 VARIABLES

A variable is like a container that holds a value. Python is dynamically typed, meaning you `don't have to declare the variable's type` when you define it.

## 🐦‍🔥 DATA TYPES

🔸 `Integer (int)`&nbsp; // By default integeres are big
🔸 `String`&nbsp; // Can be used as 'Str', "Str", '''Str'''
🔸 `float`&nbsp; // number with decimal point
🔸 `boolen (bool)` represent True/False
🔸 `None`
// There is no double

```py
name = "Aanshik"
age = 20
height = 5.6
print(type(name), type(age), type(height) )

#OUTPUT
# <class 'str'> <class 'int'> <class 'float'>
```

<br>

## 🐦‍🔥 COMMENTS

🔸 `#`&nbsp; Singe Line Commments
🔸 `""" """`&nbsp; Multi line Comments

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

🔸 `objects(s)` # single or multiple objects which are printed
🔸 `sep=' '` # it is the connector between objects, by default ' '
🔸 `end='\n'` # it tell what to print after last object, by default '\n'
🔸 `file=sys.stdout` # it tells where the output should be written, by default sys.stdout i.e. console
🔸 `flush=false` # It forces output buffer to be written immediately, by default false, allowing OS to manage

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

## 🔥 Arithematic Operators

🔸 `+`
🔸 `-`
🔸 `*`
🔸 `/`
🔸 `%`
🔸 `**`

## 🔥 Relational Operators

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

🔸 `&`
🔸 `|`
🔸 `<<`
🔸 `>>`
🔸 `^`

## 🔥 Assignment Operators

🔸 `=`
🔸 `+=`
🔸 `-=`
🔸 `*=`
🔸 `/=`
🔸 `%=`
🔸 `**=`



</div>
</div>
