import numpy as np
import matplotlib.pyplot as plt

# Question 1
arr = np.arange(1, 21)
mean = np.mean(arr)
std = np.std(arr)
print("Array:", arr)
print("Mean:", mean)
print("Standard Deviation:", std)

# Question 2
arr = np.arange(1,13)
arr = arr.reshape(3,4)
col = arr[:,1]
print(col)
print(arr)

# Question 3
arr = np.array([[1,2,3],[4,5,6]])
rowRep = np.repeat(arr, 2, axis=0)
colRep = np.repeat(arr, 3, axis=1)
print(arr)
print(rowRep)
print(colRep)

# Question 4
arr1 = np.array([[1],[4],[2]])
arr2 = np.array([[1,4,2,6]])
arr = arr1 + arr2
print (arr.shape)
print (arr)

# Question 5
arr = np.array([1,3,5,6,5,5])
mean = np.mean(arr)
st = np.std(arr)
z = (arr - mean) / st
print(z)

# Question 6
x = np.random.rand (100)
plt.xlabel('X - axis')
plt.ylabel('Y - axis')
plt.title('Histogram')
plt.hist(x)
plt.show()

# Question 7
x = np.random.rand(20)
y = np.random.rand(20)
plt.xlabel('X - axis')
plt.ylabel('Y - axis')
plt.title('Scatter plot')
plt.scatter(x, y)
plt.show()

# Question 8
arr = np.array([[1,2,3,4,5],[6,7,8,9,10],[11,12,13,14,15],[16,17,18,19,20]])
meanRow = np.mean(arr, axis=0)
meanCol = np.mean(arr, axis=1)
print(meanRow)
print(meanCol)