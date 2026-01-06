import numpy as np
import matplotlib.pyplot as plt
# arr = np.arange(1, 21)
# mean = np.mean(arr)
# std = np.std(arr)

# print("Array:", arr)
# print("Mean:", mean)
# print("Standard Deviation:", std)

# arr = np.arange(1,13)
# arr = arr.reshape(3,4)
# col = arr[:,1]
# print(col)
# print(arr)

# arr = np.array([[1,2,3],[4,5,6]])
# rowRep = np.repeat(arr, 2, axis=0)
# colRep = np.repeat(arr, 3, axis=1)
# print(arr)
# print(rowRep)
# print(colRep)

# arr1 = np.array([[1],[4],[2]])
# arr2 = np.array([[1,4,2,6]])
# arr = arr1 + arr2
# print (arr.shape)
# print (arr)

# arr = np.array([1,3,5,6,5,5])
# mean = np.mean(arr)
# st = np.std(arr)
# z = (arr - mean) / st
# print(z)

x = np.random.rand (100)
plt.xlabel('X - axis')
plt.ylabel('Y - axis')
plt.title('Histogram')
plt.hist(x)
plt.show()

# x = np.random.rand(20)
# y = np.random.rand(20)
# plt.xlabel('X - axis')
# plt.ylabel('Y - axis')
# plt.title('Scatter plot')
# plt.scatter(x, y)
# plt.show()

arr = np.array([[4,4,4,4,4],[2,2,2,2,2],[1,1,1,1,1],[3,3,3,3,3]])


