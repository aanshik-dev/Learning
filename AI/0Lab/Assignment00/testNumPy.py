import numpy as np
import matplotlib.pyplot as plt

a = np.array([[[1,2,3,4],[5,6,7,8]],[[1,2,3,4],[5,6,7,8]],[[1,2,3,4],[5,6,7,8]]])
print(a.shape)
print(type(a))
print(a)

b = np.array([[[1,2,3],[4,5,6],[1,3,5]],[[1,2,3],[4,5,6],[1,3,5]]])
print(b.shape)
print(b.ndim)

print(b[0,1,2])
print(b[0,1])
print(b[:,1])
print(b[0,:])

c = np.arange(12)
d = c.reshape(3,4)
print(d)

e = d.T
print(e)

f = np.zeros((3,4))
print(f)

g = np.ones((3,4))
print(g)

h = np.empty((3,4))
print(h)

x = np.array ([1, 2, 3])
y = np.array ([[10] ,[20], [30]])
print(y.shape)
z = x + y
print(z)

m = np.array ([[1, 2], [3, 4]])
row_repeat = np.repeat(m, 2, axis =0)
col_repeat = np.repeat(m, 2, axis =1)
print(row_repeat)
print(col_repeat)


data = np.array([2, 4, 6, 8, 10])
print(np.mean(data))
print(np.median(data))
print(np.std(data))

mean = np.mean(data)
std = np.std(data)
z = (data - mean) / std
print(z)

x = np.linspace(0, 10, 50)
y = x ** 2
plt.plot(x, y)
plt.xlabel("x - Axis")
plt.ylabel("y - Axis")
plt.title("Line Plot")
plt.show()


x = np.random.rand (50)
y = np.random.rand (50)
plt.scatter(x, y)
plt.xlabel("x")
plt.ylabel("y")
plt.title("Scatter Plot")
plt.show()