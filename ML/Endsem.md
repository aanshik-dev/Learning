# ML Practical Written Exam – Complete Endsem Code Sheet

> **Pen & Paper Friendly:** Every code block is written in clean, concise, standard Python/NumPy that is easy to memorize and write on paper.
> **Format:** Every algorithm includes **(1) From Scratch (Without Package)** and **(2) Using Scikit-Learn (With Package)**, followed by a short explanation of the math and parameters.
> **Graphs/Visualizations:** Kept at the bottom as requested.

---

## 1. The 5-Minute Master Template (Parts A to G)

Most ML lab exam questions follow this exact 6-to-7-step pipeline. Memorize this skeleton:

```python
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# A) Read dataset
df = pd.read_csv('dataset.csv')
print("Shape:", df.shape)

# B) Remove nulls, describe, and encode target
df = df.dropna()
print(df.describe())
if df['Species'].dtype == 'object':
    df['target'] = df['Species'].map({'Iris-setosa': 0, 'Iris-versicolor': 1, 'Iris-virginica': 2})

# Select the X and Y
X = df['col_name'].values
Y = df['target'].values
# OR
X = df.iloc[:, :-1].values
y = df.iloc[:, -1].values

# C) Feature scaling (Z-score standardization)
mean = np.mean(X, axis=0)
std = np.std(X, axis=0)
X_scaled = (X - mean) / std

# D) K-Fold cross validation split (k=5)
k = 5
indices = np.arange(len(X))  # [1,2,3,4,5,6,7,...]
np.random.seed(42)
np.random.shuffle(indices)
folds = np.array_split(indices, k)

# E) Train & Evaluate across folds
for test_idx in folds:
    train_idx = np.setdiff1d(indices, test_idx)

    X_train, y_train = X_scaled[train_idx], y[train_idx]
    X_test, y_test = X_scaled[test_idx], y[test_idx]

    # --- FIT YOUR MODEL HERE (e.g. KNN, OLS, Logistic, etc.) ---
    # y_pred = model.predict(X_test)

# F) Confusion Matrix & Metrics
# G) Plot Visualization (at the end)
```

---

## 2. Data Reading, Handling Nulls & Encoding

### A) Read Dataset & Basic Inspection

```python
import pandas as pd

df = pd.read_csv('dataset.csv')

print("Dimensions:", df.shape)       # (rows, columns)
print("Column names:", df.columns)   # list of column headers
print(df.head(5))                    # first 5 rows
print(df.describe())                 # count, mean, std, min, max
```

### B) Handling Null / Missing Values

```python
# 1. Check total null values in each column
print(df.isnull().sum())

# 2. Drop rows with any null value
df = df.dropna()

# 3. Drop rows where specific columns are null
df = df.dropna(subset=['Age', 'Salary'])

# 4. Fill null values with column mean
df['Age'] = df['Age'].fillna(df['Age'].mean())
```

### C) Label Encoding (Categorical to Numerical)

```python
# WITHOUT PACKAGE: Manual dictionary mapping
class_map = {'Iris-setosa': 0, 'Iris-versicolor': 1, 'Iris-virginica': 2}
df['target'] = df['Species'].map(class_map)
y = df['target'].values

# WITH PACKAGE: Scikit-Learn
from sklearn.preprocessing import LabelEncoder
le = LabelEncoder()
y = le.fit_transform(df['Species'])
```

---

## 3. Feature Scaling & Normalization (Z-Score & Min-Max)

### A) Z-Score Standardization: $x' = \frac{x - \mu}{\sigma}$ (Mean = 0, Std = 1)

```python
# WITHOUT PACKAGE: Pure NumPy
def standardize(X_train, X_test):
    mean = np.mean(X_train, axis=0)
    std = np.std(X_train, axis=0)
    X_train_s = (X_train - mean) / std
    X_test_s = (X_test - mean) / std
    return X_train_s, X_test_s

# WITH PACKAGE: Scikit-Learn
from sklearn.preprocessing import StandardScaler
scaler = StandardScaler()
X_train_s = scaler.fit_transform(X_train)
X_test_s = scaler.transform(X_test)
```

> **Explanation:** Always compute `mean` and `std` using **only the training set**, then transform both train and test. This prevents _data leakage_.

### B) Min-Max Normalization: $x' = \frac{x - x_{min}}{x_{max} - x_{min}}$ (Range $[0, 1]$)

```python
# WITHOUT PACKAGE: Pure NumPy
def min_max_scale(X_train, X_test):
    x_min = np.min(X_train, axis=0)
    x_max = np.max(X_train, axis=0)
    diff = x_max - x_min
    return (X_train - x_min) / diff, (X_test - x_min) / diff

# WITH PACKAGE: Scikit-Learn
from sklearn.preprocessing import MinMaxScaler
scaler = MinMaxScaler()
X_train_s = scaler.fit_transform(X_train)
X_test_s = scaler.transform(X_test)
```

---

## 4. Train-Test Split & K-Fold Cross Validation

### A) Train-Test Split (e.g. 80:20 or 70:30)

```python
# WITHOUT PACKAGE:
def train_test_split_manual(X, y, train_ratio=0.8, seed=42):
    np.random.seed(seed)
    n = len(X)
    indices = np.arange(n)
    np.random.shuffle(indices)
    split = int(n * train_ratio)

    train_idx, test_idx = indices[:split], indices[split:]
    return X[train_idx], X[test_idx], y[train_idx], y[test_idx]

# WITH PACKAGE:
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
```

### B) Train : Validation : Test Split (70:10:20)

```python
# WITHOUT PACKAGE:
def train_val_test_split(X, y, seed=42):
    np.random.seed(seed)
    indices = np.arange(len(X))
    np.random.shuffle(indices)

    train_end = int(0.70 * len(X))
    val_end = int(0.80 * len(X))

    tr_idx, val_idx, ts_idx = indices[:train_end], indices[train_end:val_end], indices[val_end:]
    return X[tr_idx], X[val_idx], X[ts_idx], y[tr_idx], y[val_idx], y[ts_idx]
```

### C) K-Fold Cross Validation (k=5)

```python
# WITHOUT PACKAGE:
def k_fold_cv(X, k=5, seed=42):
    np.random.seed(seed)
    indices = np.arange(len(X))
    np.random.shuffle(indices)
    folds = np.array_split(indices, k)  # Splits array into k roughly equal parts
    return folds

# Loop structure to write on paper:
folds = k_fold_cv(X, k=5)
for i in range(5):
    test_idx = folds[i]
    train_idx = np.setdiff1d(np.arange(len(X)), test_idx)
    X_train, y_train = X[train_idx], y[train_idx]
    X_test, y_test = X[test_idx], y[test_idx]

# WITH PACKAGE:
from sklearn.model_selection import KFold
kf = KFold(n_splits=5, shuffle=True, random_state=42)
for train_idx, test_idx in kf.split(X):
    X_train, X_test = X[train_idx], X[test_idx]
    y_train, y_test = y[train_idx], y[test_idx]
```

---

## 5. Evaluation Metrics & Confusion Matrix

### A) Confusion Matrix (Binary 2x2 and Multiclass)

```python
# WITHOUT PACKAGE:
def confusion_matrix_manual(y_true, y_pred, n_classes=2):
    cm = np.zeros((n_classes, n_classes), dtype=int)
    for actual, pred in zip(y_true, y_pred):
        cm[actual, pred] += 1
    return cm

# WITH PACKAGE:
from sklearn.metrics import confusion_matrix
cm = confusion_matrix(y_true, y_pred)
```

> **Matrix Layout:** Rows = **Actual Class**, Columns = **Predicted Class**.
> For binary: `cm[0,0] = TN`, `cm[0,1] = FP`, `cm[1,0] = FN`, `cm[1,1] = TP`.

### B) Classification Metrics from Confusion Matrix

```python
# WITHOUT PACKAGE:
def calculate_metrics(cm):
    total = np.sum(cm)
    overall_acc = np.trace(cm) / total  # Sum of diagonal / total

    n_classes = cm.shape[0]
    precisions = []
    recalls = []
    class_accuracies = []

    for i in range(n_classes):
        TP = cm[i, i]
        FN = np.sum(cm[i, :]) - TP
        FP = np.sum(cm[:, i]) - TP
        TN = total - TP - FN - FP

        # Precision = TP / (TP + FP)
        prec = TP / (TP + FP) if (TP + FP) > 0 else 0.0
        # Recall / Sensitivity / Class-wise Accuracy = TP / (TP + FN)
        rec = TP / (TP + FN) if (TP + FN) > 0 else 0.0

        precisions.append(prec)
        recalls.append(rec)
        class_accuracies.append(rec)

    return overall_acc, class_accuracies, precisions, recalls

# WITH PACKAGE:
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score
acc = accuracy_score(y_true, y_pred)
prec = precision_score(y_true, y_pred, average='macro')
rec = recall_score(y_true, y_pred, average='macro')
f1 = f1_score(y_true, y_pred, average='macro')
```

### C) Regression Metrics (MSE, RMSE, MAE, $R^2$)

```python
# WITHOUT PACKAGE:
mse = np.mean((y_true - y_pred) ** 2)
rmse = np.sqrt(mse)
mae = np.mean(np.abs(y_true - y_pred))
r2 = 1 - (np.sum((y_true - y_pred) ** 2) / np.sum((y_true - np.mean(y_true)) ** 2))

# WITH PACKAGE:
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score
mse = mean_squared_error(y_true, y_pred)
rmse = np.sqrt(mse)
mae = mean_absolute_error(y_true, y_pred)
r2 = r2_score(y_true, y_pred)
```

---

## 6. Ordinary Least Squares (OLS) Regression

### A) Simple Linear Regression (1 Feature): $y = \beta_0 + \beta_1 x$

```python
# WITHOUT PACKAGE: Direct formulas
# beta_1 = Cov(x, y) / Var(x)
# beta_0 = mean(y) - beta_1 * mean(x)
x_mean = np.mean(x)
y_mean = np.mean(y)

beta_1 = np.sum((x - x_mean) * (y - y_mean)) / np.sum((x - x_mean) ** 2)
beta_0 = y_mean - beta_1 * x_mean

y_pred = beta_0 + beta_1 * x_test
```

### B) Multiple Linear Regression (Closed-Form): $\theta = (X^T X)^{-1} X^T y$

```python
# WITHOUT PACKAGE: Normal Equation
def ols_fit(X, y):
    # Add column of 1s for bias term (intercept)
    X_bias = np.c_[np.ones(X.shape[0]), X]
    # theta = inv(X^T * X) * X^T * y
    theta = np.linalg.inv(X_bias.T @ X_bias) @ (X_bias.T @ y)
    return theta

def ols_predict(X, theta):
    X_bias = np.c_[np.ones(X.shape[0]), X]
    return X_bias @ theta

# WITH PACKAGE:
from sklearn.linear_model import LinearRegression
model = LinearRegression()
model.fit(X_train, y_train)
y_pred = model.predict(X_test)
```

> **Explanation:** The Normal Equation directly minimizes the Mean Squared Error $\frac{1}{m}\|X\theta - y\|^2$ by setting gradient to zero. `np.c_[np.ones(m), X]` prepends a column of ones for the bias/intercept $\theta_0$.

---

## 7. Gradient Descent Variants (Batch, Stochastic, Mini-Batch)

For linear regression: Loss $J = \frac{1}{2m} \sum (h_\theta(x) - y)^2$, Gradient $\nabla_\theta J = \frac{1}{m} X^T (X\theta - y)$.

```python
# WITHOUT PACKAGE: All 3 variants in one unified, clear structure
def gradient_descent(X, y, lr=0.01, epochs=100, mode='batch', batch_size=16):
    m, d = X.shape
    X_b = np.c_[np.ones(m), X]         # shape: (m, d+1)
    theta = np.zeros(d + 1)            # initialize weights to 0

    for epoch in range(epochs):
        indices = np.arange(m)
        np.random.shuffle(indices)
        X_shuffled = X_b[indices]
        y_shuffled = y[indices]

        # 1. BATCH GD: Uses entire dataset at once
        if mode == 'batch':
            error = X_b @ theta - y
            grad = (X_b.T @ error) / m
            theta -= lr * grad

        # 2. STOCHASTIC GD (SGD): Updates sample-by-sample (m times per epoch)
        elif mode == 'sgd':
            for i in range(m):
                xi = X_shuffled[i:i+1]
                yi = y_shuffled[i:i+1]
                error = xi @ theta - yi
                grad = xi.T @ error
                theta -= lr * grad.flatten()

        # 3. MINI-BATCH GD: Updates per batch of size B
        elif mode == 'mini_batch':
            for i in range(0, m, batch_size):
                xb = X_shuffled[i:i+batch_size]
                yb = y_shuffled[i:i+batch_size]
                error = xb @ theta - yb
                grad = (xb.T @ error) / len(yb)
                theta -= lr * grad

    return theta

# WITH PACKAGE: Scikit-Learn SGDRegressor
from sklearn.linear_model import SGDRegressor
model = SGDRegressor(learning_rate='constant', eta0=0.01, max_iter=100)
model.fit(X_train, y_train)
```

---

## 8. Logistic Regression (Binary & One-vs-All Multiclass)

### A) Binary Logistic Regression

- **Hypothesis:** $h_\theta(x) = \sigma(z) = \frac{1}{1 + e^{-z}}$, where $z = X\theta$.
- **Gradient:** $\nabla_\theta J = \frac{1}{m} X^T (h - y)$.

```python
# WITHOUT PACKAGE:
def sigmoid(z):
    z = np.clip(z, -500, 500)  # Avoid overflow
    return 1.0 / (1.0 + np.exp(-z))

def train_logistic(X, y, lr=0.1, epochs=500, rho=1e-5):
    m, d = X.shape
    X_b = np.c_[np.ones(m), X]
    theta = np.zeros(d + 1)
    prev_loss = float('inf')

    for _ in range(epochs):
        z = X_b @ theta
        h = sigmoid(z)

        # Binary cross-entropy loss
        loss = -np.mean(y * np.log(h + 1e-15) + (1 - y) * np.log(1 - h + 1e-15))
        if abs(prev_loss - loss) < rho:   # Stopping condition rho
            break
        prev_loss = loss

        # Gradient update
        grad = (X_b.T @ (h - y)) / m
        theta -= lr * grad

    return theta

def predict_logistic(X, theta, threshold=0.5):
    X_b = np.c_[np.ones(X.shape[0]), X]
    probs = sigmoid(X_b @ theta)
    return (probs >= threshold).astype(int)
```

### B) Multiclass via One-vs-All (OVA) Strategy

```python
# WITHOUT PACKAGE:
def train_ova(X, y, n_classes, lr=0.1, epochs=500):
    all_thetas = []
    for c in range(n_classes):
        # Convert multiclass labels to binary: 1 if class==c else 0
        y_binary = (y == c).astype(int)
        theta_c = train_logistic(X, y_binary, lr=lr, epochs=epochs)
        all_thetas.append(theta_c)
    return np.array(all_thetas)

def predict_ova(X, all_thetas):
    X_b = np.c_[np.ones(X.shape[0]), X]
    # Compute probability for each class: shape (m, n_classes)
    probs = sigmoid(X_b @ all_thetas.T)
    return np.argmax(probs, axis=1)

# WITH PACKAGE:
from sklearn.linear_model import LogisticRegression
model = LogisticRegression(multi_class='ovr', solver='liblinear')
model.fit(X_train, y_train)
y_pred = model.predict(X_test)
```

---

## 9. K-Nearest Neighbors (Standard & Weighted KNN)

### A) Standard K-NN (Euclidean Distance & Majority Vote)

```python
# WITHOUT PACKAGE:
def predict_knn(X_train, y_train, X_test, k=3):
    predictions = []
    for test_pt in X_test:
        # 1. Calculate Euclidean distances to all train points
        distances = np.sqrt(np.sum((X_train - test_pt) ** 2, axis=1))
        # 2. Get indices of k smallest distances
        k_indices = np.argsort(distances)[:k]
        k_labels = y_train[k_indices]
        # 3. Majority vote
        pred = np.bincount(k_labels).argmax()
        predictions.append(pred)
    return np.array(predictions)

# WITH PACKAGE:
from sklearn.neighbors import KNeighborsClassifier
model = KNeighborsClassifier(n_neighbors=3, metric='euclidean')
model.fit(X_train, y_train)
y_pred = model.predict(X_test)
```

### B) Weighted K-NN (Inverse Distance Weighting: $w_i = \frac{1}{d_i + \epsilon}$)

```python
# WITHOUT PACKAGE:
def predict_weighted_knn(X_train, y_train, X_test, k=3, epsilon=0.01):
    predictions = []
    classes = np.unique(y_train)

    for test_pt in X_test:
        distances = np.sqrt(np.sum((X_train - test_pt) ** 2, axis=1))
        k_indices = np.argsort(distances)[:k]
        k_distances = distances[k_indices]
        k_labels = y_train[k_indices]
        # Calculate inverse distance weights
        w = 1.0 / (k_distances + epsilon)
        # Sum weights for each candidate class
        pred = np.bincount(k_labels, weights=w).argmax()
        predictions.append(pred)
    return np.array(predictions)

# WITH PACKAGE:
from sklearn.neighbors import KNeighborsClassifier
# weights='distance' uses 1 / d
model = KNeighborsClassifier(n_neighbors=3, weights='distance')
model.fit(X_train, y_train)
```

> **Explanation:** Weighted K-NN assigns higher voting power to closer neighbors. Even if 2 distant neighbors vote class A and 1 extremely close neighbor votes class B, class B can win due to its high weight. $\epsilon$ prevents division by zero when $d=0$.

---

## 10. Artificial Neural Networks (ANN)

### A) McCulloch-Pitts (MP) Neuron (Binary Inputs & Threshold $\theta$)

- **Rule:** $y = 1$ if $\sum_{i=1}^n x_i \ge \theta$, else $0$.

```python
# WITHOUT PACKAGE:
def mp_neuron(X, threshold):
    output = []
    for x in X:
        total = sum(x)
        if total >= threshold:
            output.append(1)
        else:
            output.append(0)
    return output

X = [[0, 0], [0, 1], [1, 0], [1, 1]]
andGate = mp_neuron(X, 2)
orGate = mp_neuron(X, 1)
norGate = mp_neuron(X, 0)
```

### B) Perceptron (Rosenblatt: Step Function & Update Rule)

- **Activation:** $\hat{y} = 1$ if $w \cdot x + b \ge 0$, else $0$.
- **Weight update:** $w \leftarrow w + \alpha (y - \hat{y}) x$, $\; b \leftarrow b + \alpha (y - \hat{y})$.

```python
# WITHOUT PACKAGE:
def train_perceptron(X, y, lr=0.1, epochs=50):
    samples, features = X.shape
    w = np.zeros(features)
    b = 0.0

    for _ in range(epochs):
        for i in range(samples):
            z = np.dot(X[i], w) + b
            if z >= 0:
              y_pred = 1
            else:
              y_pred = 0
            # Error-driven update
            error = y[i] - y_pred
            w += lr * error * X[i]
            b += lr * error
    return w, b

def predict_perceptron(X, w, b):
    z = np.dot(X, w) + b
    return (z >= 0).astype(int)

# WITH PACKAGE:
from sklearn.linear_model import Perceptron
clf = Perceptron(max_iter=50, eta0=0.1, random_state=42)
clf.fit(X_train, y_train)
```

### C) Sigmoid Neuron (Smooth Activation $\sigma(z)$ with Gradient Descent)

```python
# WITHOUT PACKAGE:
def train_sigmoid_neuron(X, y, lr=0.1, epochs=500):
    samples, features = X.shape
    w = np.zeros(features)
    b = 0.0

    for _ in range(epochs):
        z = np.dot(X, w) + b
        pred = 1.0 / (1.0 + np.exp(-z)
        # Gradients of Cross-Entropy
        dz = (y-pred)

        w = w + lr * np.dot(X.T, dz)/n_samples
        b = b + lr * np.mean(dz)
    return w , b
```

### D) Single-Layer Perceptron (SLP) – Multiclass in a Single Architecture

```python
# WITHOUT PACKAGE: (Input: d features -> Output: K sigmoid neurons)
def slp_multiclass(X, y, lr=0.1, epochs=100):
    n_samples, n_features = X.shape
    n_classes = len(np.unique(y))

    weights = np.zeros((n_classes, n_features))
    bias = np.zeros(n_classes)

    for epoch in range(epochs):
        for i in range(n_samples):
            z = np.dot(weights, X[i]) + bias
            pred = np.argmax(z)
            if pred != y[i]:
                weights[y[i]] += lr * X[i]
                weights[pred] -= lr * X[i]
                bias[y[i]] += lr
                bias[pred] -= lr
    return weights, bias

def predict_slp(X, W):
    X_b = np.c_[np.ones(X.shape[0]), X]
    A = 1.0 / (1.0 + np.exp(-np.clip(X_b @ W, -500, 500)))
    return np.argmax(A, axis=1)
```

### E) Multi-Layer Perceptron (MLP) with Backpropagation (XOR Problem)

- **Architecture:** 2 inputs $\to$ 1 hidden layer (2 neurons) $\to$ 1 output (sigmoid).

```python
# WITHOUT PACKAGE: Clean, memorizable Backprop
def sigmoid(z):
    return 1.0 / (1.0 + np.exp(-np.clip(z, -500, 500)))

def train_mlp_xor(X, y, lr=0.1, epochs=2000, seed=42):
    np.random.seed(seed)
    m = X.shape[0]
    y = y.reshape(-1, 1)

    # Weights & biases initialization
    W1 = np.random.randn(2, 2)   # input (2) -> hidden (2)
    b1 = np.zeros((1, 2))
    W2 = np.random.randn(2, 1)   # hidden (2) -> output (1)
    b2 = np.zeros((1, 1))

    for epoch in range(epochs):
        # 1. FORWARD PASS
        Z1 = X @ W1 + b1
        A1 = sigmoid(Z1)
        Z2 = A1 @ W2 + b2
        A2 = sigmoid(Z2)

        # 2. BACKWARD PASS (Error Backpropagation)
        dZ2 = (A2 - y) / m
        dW2 = A1.T @ dZ2
        db2 = np.sum(dZ2, axis=0, keepdims=True)

        dA1 = dZ2 @ W2.T
        dZ1 = dA1 * (A1 * (1.0 - A1))  # Sigmoid derivative: A1 * (1 - A1)
        dW1 = X.T @ dZ1
        db1 = np.sum(dZ1, axis=0, keepdims=True)

        # 3. WEIGHT UPDATES
        W2 -= lr * dW2
        b2 -= lr * db2
        W1 -= lr * dW1
        b1 -= lr * db1

    return W1, b1, W2, b2

def predict_mlp_xor(X, W1, b1, W2, b2):
    A1 = sigmoid(X @ W1 + b1)
    A2 = sigmoid(A1 @ W2 + b2)
    return (A2 >= 0.5).astype(int).flatten()

# WITH PACKAGE: Scikit-Learn MLPClassifier
from sklearn.neural_network import MLPClassifier
mlp = MLPClassifier(hidden_layer_sizes=(2,), activation='logistic', solver='sgd', learning_rate_init=0.1, max_iter=100, random_state=42)
mlp.fit(X_train, y_train)
y_pred = mlp.predict(X_test)
```

---

## 11. Bayesian & Naive Bayes Classifiers (Discrete & Gaussian)

Bayes Theorem: $P(y|X) \propto P(y) \prod_{i=1}^d P(x_i | y)$.

### A) Bayesian Classifier

```python
def bayesian_classifier(X_train, y_train, X_test):
    classes = np.unique(y_train)
    predictions = []

    for x in X_test:
        scores = []
        for c in classes:
            prior = np.sum(y_train == c) / len(y_train)
            likelihood = 1
            for j in range(X_train.shape[1]):
                count = np.sum((X_train[:, j] == x[j]) & (y_train == c))
                total = np.sum(y_train == c)
                prob = count / total
                likelihood = likelihood * prob
            scores.append(prior * likelihood)
        predictions.append(classes[np.argmax(scores)])
    return np.array(predictions)


# Example
X_train = np.array([
    [1, 0],
    [1, 1],
    [0, 0],
    [0, 1],
    [1, 0],
    [0, 0]
])

y_train = np.array([1, 1, 0, 0, 1, 0])

X_test = np.array([
    [1, 1],
    [0, 1]
])

predictions = bayesian_classifier(X_train, y_train, X_test)
print(predictions)
```

### B) Gaussian Naive Bayes (Continuous Features: Normal Distribution)

- Likelihood: $P(x_i | c) = \frac{1}{\sqrt{2\pi \sigma_c^2}} \exp\left(-\frac{(x_i - \mu_c)^2}{2\sigma_c^2}\right)$.

```python
# WITHOUT PACKAGE:
class GaussianNaiveBayes:
    def fit(self, X, y):
        self.classes = np.unique(y)
        self.mean = {}
        self.var = {}
        self.priors = {}

        for c in self.classes:
            X_c = X[y == c]
            self.mean[c] = np.mean(X_c, axis=0)
            self.var[c] = np.var(X_c, axis=0) + 1e-9  # small epsilon avoids zero variance
            self.priors[c] = len(X_c) / len(X)

    def _pdf(self, c, x):
        mean = self.mean[c]
        var = self.var[c]
        numerator = np.exp(-((x - mean) ** 2) / (2 * var))
        denominator = np.sqrt(2 * np.pi * var)
        return numerator / denominator

    def predict(self, X):
        preds = []
        for x in X:
            posteriors = {}
            for c in self.classes:
                prior = np.log(self.priors[c])
                likelihood = np.sum(np.log(self._pdf(c, x) + 1e-15))
                posteriors[c] = prior + likelihood
            preds.append(max(posteriors, key=posteriors.get))
        return np.array(preds)

# WITH PACKAGE:
from sklearn.naive_bayes import GaussianNB
gnb = GaussianNB()
gnb.fit(X_train, y_train)
y_pred = gnb.predict(X_test)
```

---

## 12. Clustering Algorithms

### A) K-Means Clustering

```python
# WITHOUT PACKAGE:
def custom_kmeans(X, k=3, max_iter=100):
    np.random.seed(42)
    # 1. Randomly pick k points as initial centroids
    centroids = X[np.random.choice(len(X), k, replace=False)]

    for _ in range(max_iter):
        # 2. Assign points to closest centroid
        clusters = []
        for point in X:
          distances = [euclid(point, c) for c in centroids]
          cluster.append(np.argmin(distances))
        clusters =np.array(clusters)

        # Step 3: Recalculate centroids
        new_centroids = []
        for i in range(k):
            points = X[clusters == i]
            if len(points) == 0:
                new_centroids.append(centroids[i])   # keep old if empty
            else:
                new_centroids.append(np.mean(points, axis=0))
        new_centroids = np.array(new_centroids)
        centroids = new_centroids
  
    # Calculate WCSS / SSD (Within-Cluster Sum of Squares)
    wcss = np.sum([np.sum((X[clusters == i] - centroids[i]) ** 2) for i in range(k)])
    return clusters, centroids, wcss

# WITH PACKAGE:
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score

kmeans = KMeans(n_clusters=3, random_state=42, n_init=10)
clusters = kmeans.fit_predict(X)
wcss = kmeans.inertia_
sil_score = silhouette_score(X, clusters)
```

### B) DBSCAN (Density-Based Spatial Clustering of Applications with Noise)

```python
# WITHOUT PACKAGE:
def custom_dbscan(X, eps=0.5, min_pts=5):
    n = len(X)
    labels = np.full(n, -1)   # -1 represents Noise
    visited = np.zeros(n, dtype=bool)
    cluster_id = 0

    # Distance matrix between all pairs of points
    dist_matrix = np.zeros((n, n))
	for i in range(n):
    	for j in range(n):
        	dist_matrix[i][j] = np.linalg.norm(X[i] - X[j])

    for i in range(n):
        if visited[i]:
            continue
        visited[i] = True

        # Find neighbors within eps

      	neighbors = []
		for j in range(n):
    		if dist_matrix[i][j] <= eps:
        		neighbors.append(j)

        if len(neighbors) < min_pts:
            labels[i] = -1  # Noise point
        else:
            # Expand cluster
            labels[i] = cluster_id
            seeds = [p for p in neighbors if p != i]

            while seeds:
                q = seeds.pop(0)
                if not visited[q]:
                    visited[q] = True
                    q_neighbors = []
                    for j in range(n):
   				    	if dist_matrix[q][j] <= eps:
            		    	q_neighbors.append(j)
                    if len(q_neighbors) >= min_pts:
                      for p in q_neighbors:
                         if p not in seeds:
                           seeds.append(p)
                if labels[q] == -1:
                    labels[q] = cluster_id
            cluster_id += 1

    return labels

# WITH PACKAGE:
from sklearn.cluster import DBSCAN
db = DBSCAN(eps=0.5, min_samples=5)
labels = db.fit_predict(X)
n_clusters = len(set(labels)) - (1 if -1 in labels else 0)
n_noise = list(labels).count(-1)
```

### C) Hierarchical Agglomerative Clustering (All 4 Linkages)

- **Single Linkage:** $d(A, B) = \min_{x \in A, y \in B} d(x, y)$ (closest points)
- **Complete Linkage:** $d(A, B) = \max_{x \in A, y \in B} d(x, y)$ (farthest points)
- **Average Linkage:** $d(A, B) = \frac{1}{|A||B|} \sum \sum d(x, y)$ (average distance)
- **Centroid Linkage:** $d(A, B) = \|\mu_A - \mu_B\|$ (distance between cluster means)

```python
# WITHOUT PACKAGE: Linkage distance calculation logic
def cluster_distance(A, B, method='single'):
    dists = []
    for a in A:
        for b in B:
            dists.append(np.linalg.norm(a - b))
    if method == 'single':
        return np.min(dists)
    elif method == 'complete':
        return np.max(dists)
    elif method == 'average':
        return np.mean(dists)
    elif method == 'centroid':
        c1 = np.mean(A, axis=0)
        c2 = np.mean(B, axis=0)
        return np.linalg.norm(c1 - c2)

def agglomerative(X, k, method='single'):
    clusters = []
    # Initially, every point is a separate cluster
    for i in range(len(X)):
        clusters.append([X[i]])
    # Continue until k clusters remain
    while len(clusters) > k:
        min_dist = float('inf')
        merge_i = -1
        merge_j = -1
        # Find the closest pair of clusters
        for i in range(len(clusters)):
            for j in range(i + 1, len(clusters)):

                d = cluster_distance(
                    clusters[i], clusters[j], method
                )

                if d < min_dist:
                    min_dist = d
                    merge_i = i
                    merge_j = j

        # Merge the closest clusters
        clusters[merge_i].extend(clusters[merge_j])

        clusters.pop(merge_j)

    return clusters
# WITH PACKAGE: Scikit-Learn
from sklearn.cluster import AgglomerativeClustering
# Options for linkage: 'single', 'complete', 'average'
model = AgglomerativeClustering(n_clusters=3, linkage='average')
labels = model.fit_predict(X)

# WITH SCIPY: (Generates linkage matrix for Dendrograms)
from scipy.cluster.hierarchy import linkage, dendrogram
# Options: 'single', 'complete', 'average', 'centroid'
Z = linkage(X, method='single')
```

### D) Fuzzy C-Means (FCM) Clustering

- **Membership matrix $U$:** $u_{ij} \in [0, 1]$, and $\sum_{j=1}^c u_{ij} = 1$.
- **Centroid:** $V_j = \frac{\sum_{i=1}^n u_{ij}^m X_i}{\sum_{i=1}^n u_{ij}^m}$ (fuzzifier $m=2$).
- **Update $U$:** $u_{ij} = \frac{1}{\sum_{k=1}^c \left(\frac{\|X_i - V_j\|}{\|X_i - V_k\|}\right)^{2/(m-1)}}$.

```python
# WITHOUT PACKAGE: Pure NumPy FCM
def fuzzy_c_means(X, c=3, m=2, max_iter=100, tol=1e-4):
    np.random.seed(42)
    n, d = X.shape

    # 1. Initialize random membership matrix U (normalized so rows sum to 1)
    U = np.random.rand(n, c)
    U = U / np.sum(U, axis=1, keepdims=True)

    for _ in range(max_iter):
        U_prev = U.copy()

        # 2. Compute centroids Vj
        Um = U ** m
        V = (Um.T @ X) / np.sum(Um.T, axis=1, keepdims=True)

        # 3. Update membership matrix U
        dist = np.linalg.norm(X[:, None, :] - V[None, :, :], axis=2)
        dist = np.maximum(dist, 1e-10)  # Avoid divide-by-zero

        # u_ij formula
        power = 2.0 / (m - 1)
        inv_dist = 1.0 / dist
        U = (inv_dist ** power) / np.sum(inv_dist ** power, axis=1, keepdims=True)

        if np.linalg.norm(U - U_prev) < tol:
            break

    # Defuzzification: Hard cluster assignments
    hard_clusters = np.argmax(U, axis=1)
    return hard_clusters, V, U
```

---

## 13. Decision Trees (ID3 / Information Gain)

- **Entropy:** $H(S) = - \sum_{i=1}^c p_i \log_2(p_i)$
- **Information Gain:** $IG(S, A) = H(S) - \sum_{v \in \text{values}(A)} \frac{|S_v|}{|S|} H(S_v)$

```python
# WITHOUT PACKAGE: Core Information Gain logic
def entropy(y):
    probs = np.bincount(y) / len(y)
    probs = probs[probs > 0]
    return -np.sum(probs * np.log2(probs))

def information_gain(X_col, y, threshold):
    """Calculates IG for continuous attribute thresholding (X <= threshold)."""
    parent_entropy = entropy(y)
    left_mask = X_col <= threshold
    right_mask = ~left_mask

    if np.sum(left_mask) == 0 or np.sum(right_mask) == 0:
        return 0

    n = len(y)
    n_left, n_right = np.sum(left_mask), np.sum(right_mask)
    left_entropy = entropy(y[left_mask])
    right_entropy = entropy(y[right_mask])

    child_entropy = (n_left / n) * left_entropy + (n_right / n) * right_entropy
    return parent_entropy - child_entropy

# WITH PACKAGE: Scikit-Learn
from sklearn.tree import DecisionTreeClassifier
tree = DecisionTreeClassifier(criterion='entropy', max_depth=3, random_state=42)
tree.fit(X_train, y_train)
y_pred = tree.predict(X_test)
```

---

## 14. Plots & Visualizations

> Keep plot code simple and memorizable. Always call `plt.tight_layout()` and `plt.show()` (or `plt.savefig('plot.png')`).

### A) 2D Scatter Plot of Clusters / Classes (e.g. PCA or Feature 1 vs Feature 2)

```python
plt.figure(figsize=(6, 4))
plt.scatter(X[:, 0], X[:, 1], c=y, cmap='viridis', edgecolors='k', s=40)
plt.title("Cluster / Class Scatter Plot")
plt.xlabel("Feature 1")
plt.ylabel("Feature 2")
plt.colorbar()
plt.tight_layout()
plt.show()
```

### B) Confusion Matrix Plot

```python
plt.figure(figsize=(5, 4))
plt.imshow(cm, cmap='Blues')
plt.title("Confusion Matrix")
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.xticks([0, 1], ["Class 0", "Class 1"])
plt.yticks([0, 1], ["Class 0", "Class 1"])

for r in range(cm.shape[0]):
    for c in range(cm.shape[1]):
        plt.text(c, r, str(cm[r, c]), ha="center", va="center", color="red", fontweight="bold")

plt.colorbar()
plt.tight_layout()
plt.show()
```

### C) Elbow Method Curve (K vs. WCSS)

```python
plt.figure(figsize=(6, 4))
plt.plot(range(2, 9), wcss_list, marker='o', color='b')
plt.title("Elbow Method for Optimal K")
plt.xlabel("Number of Clusters (K)")
plt.ylabel("WCSS / SSD")
plt.grid(True)
plt.tight_layout()
plt.show()
```

### D) Loss / Error Curve across Epochs

```python
plt.figure(figsize=(6, 4))
plt.plot(loss_history, color='darkred', linewidth=2)
plt.title("Training Loss Curve")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.grid(True)
plt.tight_layout()
plt.show()
```

### E) Dendrogram for Hierarchical Clustering

```python
from scipy.cluster.hierarchy import linkage, dendrogram

Z = linkage(X, method='average')
plt.figure(figsize=(7, 4))
dendrogram(Z)
plt.title("Hierarchical Clustering Dendrogram")
plt.xlabel("Sample Index")
plt.ylabel("Distance")
plt.tight_layout()
plt.show()
```
