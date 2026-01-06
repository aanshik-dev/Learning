x = 10
print(type(x))

x = 3.5
print(type(x))

x = "Python"
print(type(x))

name = input("Enter your name : ")
age = int(input("Enter your age : "))
print("Name :", name)
print("Age :", age)

x = 15
if(x >10):
  print("Greater than 10")
elif x == 10:
  print("Equal to 10")
else:
  print("Less than 10")

for i in range(5):
  print(i)

numbers = [2,4,6,8]
for num in numbers:
  print(num)

count = 0
while count < 5:
  print(count)
  count += 1

numbers = [1,2,3,4]
numbers.append(5)
numbers[0] = 10
print(numbers)

nums = [0,1,2,3,4,5]
print(nums[1:4])
print(nums[:3])
print(nums[::2])

point = (3, 4)
x, y = point
print(x, y)

student = {
  "name" : "Aanshik",
  "roll" : 2401037,
  "marks" : 85
}

print(student["name"])
student["marks"] = 90

def compute(a,b):
  return a + b, a * b

s,p = compute(2,3)
print(s,p)