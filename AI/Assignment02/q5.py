file1 = open("./Learning/AI/Assignment02/text.txt", "r")
file1.seek(0)

file2 = open("./Learning/AI/Assignment02/copy.txt", "w+")
file2.write(file1.read())

file1.close()
file2.close()