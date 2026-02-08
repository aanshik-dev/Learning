import numpy as np

arr1 = np.random.randint(1, 10, (2, 3, 4))
arr2 = np.random.randint(1, 10, (2, 3, 4))

con = np.concatenate((arr1, arr2), axis=0)
sort1 = np.sort(arr1)
sort2 = np.sort(arr2)
add = arr1 + arr2
sub = arr1 - arr2
mul = arr1 * arr2
dev = arr1 / arr2

print(arr1)
print("--------------------------")
print(arr2)
print("--------------------------")

print(con)
print("--------------------------")
print(sort1)
print("--------------------------")
print(sort2)
print("--------------------------")
print(add)
print("--------------------------")
print(sub)
print("--------------------------")
print(mul)
print("--------------------------")
print(dev)
