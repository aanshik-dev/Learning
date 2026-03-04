import numpy as np

mat = np.random.randint(1, 20, (4, 5))

mat0 = np.full(10, 0)
mat1 = np.full(10, 1)
mat5 = np.full(10, 5)

evens = np.arange(10, 50, 2)
rand = np.random.rand(1)[0]

file = open("matrix.txt", "w+")
file.write(str(mat))

file.seek(0)
print(file.read())
file.close()

print(mat0)
print(mat1)
print(mat5)
print(evens)
print(rand)
