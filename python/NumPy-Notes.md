<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **NumPy Notes** 🔥🐦‍🔥

<br>

## 🐦‍🔥 INTRODUCTION TO NUMPY

NumPy (Numerical Python) is a fundamental package for scientific computing in Python. It provides:

- Powerful N-dimensional array objects
- Sophisticated broadcasting functions
- Tools for integrating C/C++ and Fortran code
- Useful linear algebra, Fourier transform, and random number capabilities

### 🔥 How it is different from the list ?

- It is faster (optimised in C)
- It allow only same data type
- Mathematics operations are vectiorized (no loops)
- More powerful built in functions

### 🔥 Installation

```py
# Install NumPy
pip install numpy

# Import convention
import numpy as np
```

## 🐦‍🔥 CREATING ARRAYS

### 🔥 From Python Lists

```py
arr1d = np.array([1, 2, 3, 4, 5])
print(arr1d)  # 1D Array

arr2d = np.array([[1, 2, 3], [4, 5, 6]])
print(arr2d) # 2D Array (Matrix)

arr3d = np.array([[[1, 2], [3, 4]], [[5, 6], [7, 8]]])
print(arr3d) # 3D Array
```

### 🔥 Special Array Creation Functions

```py
# Zeros array
zeros_arr = np.zeros((3, 4))  # 3x4 array of zeros

# Ones array
ones_arr = np.ones((2, 3, 4))  # 2x3x4 array of ones
ones_arr = np.ones([2, 3, 4])  # 2x3x4 array of ones

# Identity matrix
eye_arr = np.eye(3)  # 3x3 identity matrix

# Empty array
empty_arr = np.empty((2, 3))  # 2x3 empty array

# custom valued array
custom_arr = np.full((2, 3), 10)  # 2x3 array of 10

# Array with a range
range_arr = np.arange(0, 10, 2)  # [0, 2, 4, 6, 8]

# Evenly spaced values
lin_arr = np.linspace(0, 1, 5)  # [0. 0.25 0.5 0.75 1. ]

# Logarithmic spaced values
log_arr = np.logspace(0, 5, 5)  # [1. 10. 100. 1000. 10000.]

# repeat
arr = np.repeat([1, 2, 3], 3)  # [1 1 1 2 2 2 3 3 3]
# tile
arr = np.tile([1, 2, 3], 3)  # [1 2 3 1 2 3 1 2 3]

# Random arrays
random_arr = np.random.rand(3, 3)  # 3x3 random values (0-1)
random_arr = np.random.random((3, 3))  # 3x3 random values (0-1)
random_arr = np.random.randn(3, 3)  # 3x3 random values (mean=0, std=1)
randint_arr = np.random.randint(1, 100, (3, 3))  # 3x3 random integers
```

| Function   | How size is passed |
| ---------- | ------------------ |
| `random()` | tuple → `(2,3)`    |
| `rand()`   | arguments → `2, 3` |

### 🔥 Array Properties

```py
arr = np.array([[1, 2, 3], [4, 5, 6]])

print("Shape:", arr.shape)      # (2, 3)
print("Dimensions:", arr.ndim)  # 2
print("Size:", arr.size)        # 6 (total elements)
print("Data type:", arr.dtype)  # int64/int32
print("Item size:", arr.itemsize)  # 8 (bytes per element)
print("Total bytes:", arr.nbytes)  # 48 (total memory)
```

<br>

## 🐦‍🔥 ARRAY DATA TYPES

```py
# Specify data types
arr_int32 = np.array([1, 2, 3], dtype=np.int32)
arr_float64 = np.array([1.0, 2.0, 3.0], dtype=np.float64)
arr_complex = np.array([1+2j, 3+4j], dtype=np.complex128)
arr_bool = np.array([True, False, True], dtype=np.bool_)
arr_string = np.array(['a', 'b', 'c'], dtype=np.str_)

# Type conversion
arr_float = arr_int32.astype(np.float64)
```

<br>

## 🐦‍🔥 ARRAY MANIPULATION

### 🔥 Reshaping Arrays

```py
arr = np.arange(12)

# Reshape
reshaped = arr.reshape(3, 4)
print(reshaped)
# [[ 0  1  2  3]
#  [ 4  5  6  7]
#  [ 8  9 10 11]]

raveled = reshaped.ravel() # Shallow Copy
print(raveled)  # [ 0  1  2  3  4  5  6  7  8  9 10 11]

# Flatten
flattened = reshaped.flatten() # Deep Copy
print(flattened)  # [ 0  1  2  3  4  5  6  7  8  9 10 11]

# Resize (modifies original)
arr.resize(2, 6)

# Transpose
transposed = reshaped.T
transposed = reshaped.transpose()

# swapaxes
arr = np.array([[[1,2],[3,4]]])
swapped = reshaped.swapaxes(0, 1)
```

### 🔥 Stacking & Splitting

```py
a = np.array([1, 2, 3])
b = np.array([4, 5, 6])

# Stacking
print(np.vstack((a, b)))  # Vertical stack
# [[1 2 3]
#  [4 5 6]]
print(np.hstack((a, b)))  # Horizontal stack
# [1 2 3 4 5 6]

# Splitting
arr = np.array([1, 2, 3, 4, 5, 6])
print(np.split(arr, 3))  # Split into 3 equal parts
# [array([1, 2]), array([3, 4]), array([5, 6])]

arr = np.array([[1,2,3,4],[5,6,7,8]])
print(np.vsplit(arr, 2))  # Split into 2 vertical parts
# [array([[1, 2, 3, 4]]), array([[5, 6, 7, 8]])]
print(np.hsplit(arr, 2))  # Split into 2 vertical parts
# [array([[1, 2], [5, 6]]), array([[3, 4], [7, 8]])]
print(np.concatenate((a, b)))  # Concatenate
```

### 🔥 Copy vs View

```py
# View (shallow copy)
arr = np.array([1, 2, 3])
view = arr.view()
view[0] = 10
print(arr)  # [10  2  3] (original changed!)

# Copy (deep copy)
arr = np.array([1, 2, 3])
copy = arr.copy()
copy[0] = 10
print(arr)  # [1 2 3] (original unchanged)
```

<br>

## 🐦‍🔥 LOOP

```py
arr = np.array([2,3,5,9,6])
for x in np.nditer(arr):
  print(x, end=' ')  # 2 3 5 9 6

for ind, val in np.ndenumerate(arr):
  print(ind, val, end=' | ') # (0,) 2 | (1,) 3 | (2,) 5 | (3,) 9 | (4,) 6 |
```

<br>

## 🐦‍🔥 ARRAY INDEXING AND SLICING

### 🔥 1D Array Indexing

```py
arr = np.array([10, 20, 30, 40, 50])

print(arr[0])    # 10
print(arr[-1])   # 50 (last element)
print(arr[1:4])  # [20 30 40]
print(arr[::2])  # [10 30 50] (every 2nd element)
print(arr[::-1]) # [50 40 30 20 10] (reverse)
```

### 🔥 2D Array Indexing

```py
arr = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])

print(arr[0, 1])    # 2 (row 0, column 1)
print(arr[1])       # [4 5 6] (row 1)
print(arr[:, 1])    # [2 5 8] (column 1)
print(arr[0:2, 1:3]) # [[2 3] [5 6]] (submatrix)
```

### 🔥 Boolean Indexing

```py
arr = np.array([1, 2, 3, 4, 5])

# Boolean mask
np.where(arr % 2 == 0, "even", "odd") # ['odd' 'even' 'odd' 'even' 'odd']
np.argwhere(arr % 2 == 0) # [[1] [3]] return index
np.logical_and(arr > 1, arr < 5) # [False  True  True  True  False]

mask = arr > 2
print(mask)          # [False False  True  True  True]
print(arr[mask])     # [3 4 5]
print(arr[arr % 2 == 0])  # [2 4] (even numbers)
```

### 🔥 Fancy Indexing

```py
arr = np.array([10, 20, 30, 40, 50])

# Using integer arrays as indices
indices = [0, 2, 4]
print(arr[indices])  # [10 30 50]
print(np.take(arr, indices))  # [10 30 50]

# For 2D arrays
arr2d = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
rows = [0, 2]
cols = [1, 2]
print(arr2d[rows, cols])  # [2 9]
```

<br>

## 🐦‍🔥 ARRAY OPERATIONS

### 🔥 Arithmetic Operations

```py
a = np.array([1, 2, 3])
b = np.array([4, 5, 6])

print(a + b)   # [5 7 9]
print(a - b)   # [-3 -3 -3]
print(a * b)   # [4 10 18] (element-wise)
print(a / b)   # [0.25 0.4  0.5 ]
print(b // a)  # [4 2 1]
print(b % a)   # [0 1 0]
print(a ** 2)  # [1 4 9]
print(np.sqrt(a))  # [1.         1.41421356 1.73205081]
```

### 🔥 Matrix Operations

```py
A = np.array([[1, 2], [3, 4]])
B = np.array([[5, 6], [7, 8]])


# Element-wise multiplication
print(A * B)
# [[ 5 12]
#  [21 32]]

# Matrix multiplication
print(np.dot(A, B))
print(A @ B)  # Same as np.dot
# [[19 22]
#  [43 50]]

# Transpose
print(A.T)
# [[1 3]
#  [2 4]]

# Inverse (for square matrices)
print(np.linalg.inv(A))
```

### 🔥 Aggregation Operations

```py
arr = np.array([[1, 2, 3], [4, 5, 6]])

print(np.sum(arr))        # 21 (total sum)
print(arr.sum())          # 21 (same)
print(arr.sum(axis=0))    # [5 7 9] (sum along columns)
print(arr.sum(axis=1))    # [6 15] (sum along rows)

print(np.mean(arr))       # 3.5
print(np.median(arr))     # 3.5
print(np.std(arr))        # 1.7078 (standard deviation)
print(np.var(arr))        # 2.9167 (variance)
print(np.min(arr))        # 1
print(np.max(arr))        # 6
print(np.argmax(arr))     # 5 (index of max value)
```

<br>

## 🐦‍🔥 RANDOM MODULE

```py
# Set seed for reproducibility
np.random.seed(42)

# Random numbers
print(np.random.rand(3, 3))        # Uniform distribution [0, 1)
print(np.random.randn(3, 3))       # Standard normal distribution
print(np.random.randint(0, 10, 5)) # Random integers

# Random choice
arr = np.array([1, 2, 3, 4, 5])
print(np.random.choice(arr, size=3, replace=False))

# Shuffle
shuffled = arr.copy()
np.random.shuffle(shuffled)

# Distributions
print(np.random.normal(0, 1, 5))   # Normal distribution
print(np.random.uniform(0, 1, 5))  # Uniform distribution
print(np.random.binomial(10, 0.5, 5))  # Binomial distribution
```

<br>

## 🐦‍🔥 BROADCASTING

Broadcasting allows operations between arrays of different shapes.

### 🔥 Broadcasting Rules

- Compare shapes from right to left
- If shapes are equal, they are compatible
- If one is 1, it can be stretched to match the other
- If shapes are different and not 1 then error
- missing dimensions are treated as 1

```py
# Example 1: Scalar with array
arr = np.array([1, 2, 3])  # Shape (3,)
print(arr + 5)  # [6 7 8]  # Scalar is broadcast to (3,)

# Example 2: Different shapes
A = np.array([[1, 2, 3], [4, 5, 6]])  # Shape (2, 3)
B = np.array([10, 20, 30])            # Shape (3,) missing is 1
print(A + B)  # B is broadcast to (2, 3)
# [[11 22 33]
#  [14 25 36]]

# Example 3: More complex broadcasting
A = np.ones((3, 1, 4))  # Shape (3, 1, 4)
B = np.ones((2, 4))     # Shape (2, 4)
# Result shape: (3, 2, 4)
```

| Dimension | A   | B   | Compatible? | Why      |
| --------- | --- | --- | ----------- | -------- |
| last      | 4   | 4   | ✅          | same     |
| middle    | 1   | 2   | ✅          | one is 1 |
| first     | 3   | 1   | ✅          | one is 1 |

<br>

## 🐦‍🔥 UNIVERSAL FUNCTIONS (UFUNCS)

```py
arr = np.array([1, 4, 9, 16, 25])

# Mathematical functions
print(np.sqrt(arr))      # Square root
print(np.exp(arr))       # Exponential
print(np.log(arr))       # Natural log
print(np.log10(arr))     # Base-10 log
print(np.sin(arr))       # Sine
print(np.cos(arr))       # Cosine
print(np.tan(arr))       # Tangent

# Comparison functions
print(np.greater(arr, 10))  # [False False False  True  True]
print(np.equal(arr, 9))     # [False False  True False False]

# Custom ufunc
def double(x):
    return x * 2

double_ufunc = np.frompyfunc(double, 1, 1)
print(double_ufunc(arr))  # [2 8 18 32 50]
```

<br>

## 🐦‍🔥 LINEAR ALGEBRA

```py
A = np.array([[1, 2], [3, 4]])
B = np.array([[5, 6], [7, 8]])
v = np.array([1, 2])

# Determinant
print(np.linalg.det(A))

# Eigenvalues and eigenvectors
eigenvalues, eigenvectors = np.linalg.eig(A)

# Solve linear equations: Ax = b
b = np.array([3, 4])
x = np.linalg.solve(A, b)

# Matrix rank
print(np.linalg.matrix_rank(A))

# Norms
print(np.linalg.norm(v))  # L2 norm
print(np.linalg.norm(v, 1))  # L1 norm
```

<br>

## 🐦‍🔥 FILE I/O

```py
# Save and load arrays
arr = np.array([[1, 2, 3], [4, 5, 6]])

# Text files
np.savetxt('array.txt', arr)
loaded = np.loadtxt('array.txt')

# Binary files (more efficient)
np.save('array.npy', arr)
loaded = np.load('array.npy')

# Multiple arrays
np.savez('arrays.npz', arr1=arr, arr2=arr*2)
data = np.load('arrays.npz')
print(data['arr1'])
print(data['arr2'])
```

<br>

## 🐦‍🔥 MISSING VALUES

- `np.nan` not a number
- `np.inf` + infinity
- `-np.inf` - infinity
- `np.isnan` Checks if the value is nan
- `np.isinf` Checks if the value is infinity
- `np.isfinite` Checks if the value is finite
- `np.nan_to_num` Replaces nan with 0

```py
np.nan_to_num(arr, nan=0.0, posinf=None, neginf=None)
```

```py
import numpy as np
arr = np.array([1, 2, np.nan, np.inf, -np.inf])
np.nan_to_num(arr)

# [ 1.00000000e+000
#   2.00000000e+000
#   0.00000000e+000
#   1.79769313e+308
#  -1.79769313e+308 ]
```

<br>

## 🐦‍🔥 PERFORMANCE TIPS

### 🔥 Vertorization

```py
# Slow: Python loops
def slow_add(arr1, arr2):
    result = np.empty_like(arr1)
    for i in range(len(arr1)):
        for j in range(arr1.shape[1]):
            result[i, j] = arr1[i, j] + arr2[i, j]
    return result

# Fast: NumPy vectorization
def fast_add(arr1, arr2):
    return arr1 + arr2  # Much faster!
```

### 🔥 In-place Operations

```py
arr = np.array([1, 2, 3, 4, 5])

# Creates new array (slower, more memory)
arr = arr * 2

# In-place operation (faster, less memory)
arr *= 2
```

<br>

## 🐦‍🔥 COMMON USE CASES

### 🔥 Image Processing

```py
# Simulating image operations
image = np.random.randint(0, 256, (100, 100, 3), dtype=np.uint8)

# Convert to grayscale
gray = np.mean(image, axis=2).astype(np.uint8)

# Apply threshold
threshold = 128
binary = (gray > threshold).astype(np.uint8) * 255

# Edge detection (simplified)
edges = np.abs(np.diff(gray, axis=0)) + np.abs(np.diff(gray, axis=1))
```

### 🔥 Data Analysis

```py
# Simulating dataset
data = np.random.randn(1000, 5)  # 1000 samples, 5 features

# Normalize data
normalized = (data - np.mean(data, axis=0)) / np.std(data, axis=0)

# Find outliers
z_scores = np.abs((data - np.mean(data, axis=0)) / np.std(data, axis=0))
outliers = np.any(z_scores > 3, axis=1)

# Correlation matrix
correlation = np.corrcoef(data.T)
```

</div>
</div>
