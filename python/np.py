import numpy as np

# arr = np.random.uniform(0, 5, (2,2))

# a = np.array([1, 2, 3])
# b = np.array([4, 5, 6])

# arr =  np.array([1,2,3,4,5,6])
# print(arr[-3:-1:])
# print(arr[-1:-3:-1])

# arr = np.array([2,3,5,9,6])
# for x in np.nditer(arr):
#   print(x, end=' ')
# print("\n")

# for ind, val in np.ndenumerate(arr):
#   print(ind, val, end=' | ') 
# print("\n")

# arr = np.array([[1,2,3],[4,5,6]])
# print(arr.transpose())

# arr = np.array([[[1,2],[3,4]]])
# print(arr.shape)
# print(arr)
# print("\n")

# swapped = arr.swapaxes(1, 2)
# print(swapped.shape)
# print(swapped)



# arr = np.array([1, 2, 3, 4, 5])
# print(np.logical_and(arr > 1, arr < 5)) # [False  True  True  True  False]
# res = np.where(arr % 2 == 0, "low", "high")  # ["low" "high" "high" "high" "high"] 
# print(res)

image = np.random.randint(0, 256, (100, 100, 3), dtype=np.uint8)
print(image.shape)
print(image)