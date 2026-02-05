import numpy as np

arr = np.array([
    [10, 20, 30],
    [40, 50, 60],
    [70, 80, 90]
])

second_column = arr[:, 1]

last_row = arr[-1, :]

print("Original array:\n", arr)
print("Second column:", second_column)
print("Last row:", last_row)
