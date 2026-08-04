import random

# 1. Write a function to break down a string into a list of characters.
def string_to_list(string):
  return list(string)

# 2. Write a function to reverse output of the problem 1 back into a string.
def list_to_string(list):
  return "".join(list)


# 3. Write  a  function  to  generate  a  list  of  n  random  numbers.  Use  the  inbuilt  `random` module.
def n_rand(n):
  return [random.randint(0, 10) for _ in range(n)]


# 4. Write a function to sort a given list of numbers in descending order.
def sort_list(list):
  return sorted(list, reverse=True)


# 5. Write a function to get the frequency of each number in a list of numbers. Use a python `dict` to solve this
def get_frequency(list):
  frequency = {}
  for num in list:
    if num in frequency:
      frequency[num] += 1
    else:
      frequency[num] = 1
  return frequency


# 6. Write a function to get all the unique elements from a given list. Your solution must use `set` to solve this
def get_unique(list):
  return list(set(list))


# 7. Write  a  function  to  get  the  first  repeating  element  from  a  list.  Your  solution  must  use `set` to solve this.
def repeating(list):
  ls = set()
  for num in list:
    if num in ls:
      return num
    else:
      ls.add(num)


# 8. Write a function that takes an integer n and output a `dict` containing keys from 0,2 ... to n and each key is mapped to a list containing the square and cube of the number
def  sq_Cube(n):
  dictionary = {}
  for num in range(n):
    



print(repeating([1,2,3,5,4,6,1]))
print(n_rand(10))