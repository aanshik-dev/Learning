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