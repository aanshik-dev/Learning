import random
import functools

# 1. Write a function to break down a string into a list of characters.
def string_to_list(string):
  return list(string)

# 2. Write a function to reverse output of the problem 1 back into a string.
def list_to_string(lst):
  return "".join(lst)

# 3. Write  a  function  to  generate  a  list  of  n  random  numbers.  Use  the  inbuilt  `random` module.
def n_rand(n):
  return [random.randint(0, 9) for _ in range(n)]


# 4. Write a function to sort a given list of numbers in descending order.
def sort_list(lst):
  return sorted(lst, reverse=True)


# 5. Write a function to get the frequency of each number in a list of numbers. Use a python `dict` to solve this
def get_frequency(lst):
  frequency = {}
  for num in lst:
    if num in frequency:
      frequency[num] += 1
    else:
      frequency[num] = 1
  return frequency


# 6. Write a function to get all the unique elements from a given list. Your solution must use `set` to solve this
def get_unique(lst):
  return list(set(lst))


# 7. Write  a  function  to  get  the  first  repeating  element  from  a  list.  Your  solution  must  use `set` to solve this.
def repeating(lst):
  ls = set()
  for num in lst:
    if num in ls:
      return num
    else:
      ls.add(num)


# 8. Write a function that takes an integer n and output a `dict` containing keys from 0,2 ... to n and each key is mapped to a list containing the square and cube of the number
def  sq_Cube(n):
  dictionary = {}
  for num in range(0,n,2):
    dictionary[num] = [num**2, num**3]
  return dictionary

# 9. Given  two  lists  of  equal  size,  write  a  function  to  create  tuples  of  each  consecutive element having the same index. Use `zip` in some capacity to solve this. 
def tupList(l1, l2):
  return list(zip(l1,l2))


# 10. Write a function that uses list comprehension to generate the squares of 0 to n. 
def sqr(n):
  return [x**2 for x in range(0,n)]

# 11. Write a function that uses dictionary comprehension to generate a mapping from (0 to n) to their squares. 
def sqrMap(n):
  return {x: x**2 for x in range(n)}

# 12. Write a `class` such that : 
# 1.  The  initializer  takes  an  arbitrary  list  of  atomic  values  as  input  and  saves  it  in  an instance variable. 
# 2. Has a method called `apply` which has the following functionality: 
# ●  Accepts a function as a parameter. You can use a lambda function. 
# ●  Applies  the  function  to  the  saved  list  and  returns  the  output.  The  instance  variable must not be modified. 
# ●  If  it  fails  `raise`  an  `Exception`  with  a  custom  error  message.  You can use `try` and `except` here. 

class AtomicList:
    def __init__(self, *values):
        self.values = list(values)

    def apply(self, func):
        try:
            return func(self.values.copy())
        except Exception as e:
            raise Exception(f"Error while applying function: {e}")


# 13. Write  a  function  that  takes  as  input  a  list  of  words  and  upper-cases  each  word.  Use `functools.map` in some capacity to solve this. 
def upper(ls):
  return list(map(lambda x: x.upper(), ls))


# 14. Write a function to find the product of all the numbers in a list using `functools.reduce` in some capacity. 
def product(ls):
  return functools.reduce(lambda x, y: x * y, ls)


print(string_to_list("Hello")) #1
print(list_to_string(["H", "e", "l", "l", "o"])) #2
lst = n_rand(5) #3
print(lst)
print(sort_list(lst)) #4
lst = [1,2,5,2,1,6,3,4,2,5,6,1]
print(get_frequency(lst)) #5
print(get_unique(lst)) #6
print(repeating(lst)) #7
print(sq_Cube(10)) #8
print(tupList([1,2,3],["a2z","b","c"])) #9
print(sqr(10)) #10
print(sqrMap(10)) #11

lst = [1,2,6,5,4]
al = AtomicList(*lst)
print(al.apply(lambda x: [i * 2 for i in x]))
print(upper(["hello", "world"])) #13
print(product([1,2,3,4,5])) #14