import numpy as np
import time

rows = 106
cols = 104

P = np.random.rand(rows, cols)
Q = np.random.rand(rows, cols)

start_time = time.time()

result_loop = np.zeros((rows, rows))

for i in range(rows):
    for j in range(rows):
        for k in range(cols):
            result_loop[i, j] += P[i, k] * Q[j, k]

t1 = time.time() - start_time

start_time = time.time()
result_numpy = P.dot(Q.T)
t2 = time.time() - start_time

speedup = t1 / t2

print(f"Time using nested loops (t1): {t1:.6f} seconds")
print(f"Time using NumPy vectorization (t2): {t2:.6f} seconds")
print(f"Speedup (t1 / t2): {speedup:.2f}x")
