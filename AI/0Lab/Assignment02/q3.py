num = input("Enter a number: ")

file = open("./Learning/AI/0Lab/Assignment02/example.txt", "r")
file.seek(0)
print(file.read(int(num)))
file.close()

file = open("./Learning/AI/0Lab/Assignment02/example.txt", "a+")
file.write("Ask me if you need any assistance!!\n")

file.seek(0)
print(file.read())
file.close()