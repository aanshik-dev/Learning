import numpy as np

n = int(input("Enter number of rows: "))
mat = np.array((input("Enter a elements of matrix: ")).split(" "))
mat = mat.reshape(n, int(mat.size/n))

trans = mat.T
print(trans)

flat = mat.flatten()
print(flat)