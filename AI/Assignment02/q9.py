import numpy as np

arr = np.random.randint(1, 10, (8, 7))
print(arr)

s = arr.shape


for col in range(s[1]):
  print("[", col+1, "]", " Max:", np.max(arr[:,col]) , " Min:", np.min(arr[:,col]))