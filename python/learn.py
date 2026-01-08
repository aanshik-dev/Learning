# Print Statements
print("Hello World")
print("I'm Jarvis", "Your AI Assistant", sep=" - ")

name = "Aanshik"
age = 20
height = 5.6
print(f"Name : {name} \nAge : {age} \nHeight : {height}")
print(type(name), type(age), type(height) )

print(age.bit_length())

tup = ("A", "B", "C")
print(tup)
print(type(tup))
print(tup[0])

ls = [1,2,3,4]
ls1 = ls.copy()
ls[0] = 100
print(ls)
print(ls1)

dict = {
  "name" : "Aanshik",
  "age" : 20,
  "height" : 5.6
}
print(dict)
print(type(dict))
print(dict["name"])
print(dict.keys())
print(dict.values())

set = {1, "B", "C"}
x = set.pop()
print(x)
print(set)
print(type(set))

ls = [1,2,3,4]
print(sum(ls))

str = "Hi i am learning python"
print(str.split(" "))