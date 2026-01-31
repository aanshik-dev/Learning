file = open("./Learning/AI/Assignment02/example.txt", "w+")
file.write("Hello Boss!! how are you doing !\nI am Jarvis at your service\n")

file.seek(0)
print(file.read())

file.close()


