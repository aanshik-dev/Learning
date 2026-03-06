num = input("Enter a number: ")

file = open("./Learning/AI/0Lab/Assignment02/example.txt", "r")
file.seek(0)
print(file.read(int(num)))
file.close()