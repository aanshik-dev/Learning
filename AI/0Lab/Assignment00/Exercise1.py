# Question 1
num = int(input("Enter a number: "))

if num > 0:
  print("Positive")
elif num < 0:
  print("Negative")
else:
  print("Zero")

# Question 2
arr = []
for i in range(3):
  num = int(input("Enter a number: "))
  arr.append(num)

print("The largest number is:", max(arr))
print("The smallest number is:", min(arr))

# Question 3
arr = []
for i in range(5):
  num = int(input("Enter a number: "))
  arr.append(num)

print("The sum is:", sum(arr))
print("The average is:", sum(arr) / len(arr))

# Question 4
ls = [1,3,5,8,9,6,45,2]
odd = 0
even = 0

for num in ls:
  if num % 2 == 0:
    even += 1
  else:
    odd += 1

print("Number of odd numbers:", odd)
print("Number of even numbers:", even)

# Question 5
Student = {}
for i in range(3):
  name = input("Enter student name: ")
  marks = int(input("Enter student marks: "))
  Student[name] = marks

print("Average marks:", sum(Student.values()) / len(Student))

# Question 6

def minMax(arr):
  return min(arr), max(arr)

ls = [1,3,5,8,9,6,4,2]
print(minMax(ls))

# Question 7
string = input("Enter a string: ")
freq = {}

for char in string:
  if char in freq:
    freq[char] += 1
  else:
    freq[char] = 1
print(freq)

# Question 8
n = int(input("Enter a number: "))
a = 1
b = 1

for i in range(n):
  print(a, end=" ")
  a, b = b, a + b