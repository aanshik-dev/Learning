# ML Practical Exam – Code Cheat Sheet

> **Pen & Paper Ready** — Every block is self-contained. Comments explain the _why_.
> Sections ordered by exam likelihood. Graphs/Visualization at the bottom.

---

## Table of Contents

1. [Imports (Common)](#1-imports)
2. [Data Reading & Preprocessing](#2-data-reading--preprocessing)
   - [Label / Categorical Encoding](#categorical--label-encoding-class-names-to-numbers)
   - [Synthetic Dataset Generation](#generating-synthetic-regression-dataset)
3. [Train-Test Split](#3-train-test-split)
   - [Multi-Ratio Split Loop (10:90 to 90:10)](#multi-ratio-train-test-split-loop-1090-to-9010)
4. [Normalization & Scaling](#4-normalization--scaling)
5. [OLS – Ordinary Least Squares](#5-ols--ordinary-least-squares)
   - [Covariance, Variance & Pearson Correlation](#covariance-variance-and-pearson-correlation-from-scratch)
6. [Gradient Descent (All Variants)](#6-gradient-descent)
   - [Batch GD (1D)](#6a-batch-gradient-descent-uses-all-samples-per-step)
   - [Stochastic GD (1D)](#6b-stochastic-gradient-descent-uses-1-sample-per-step)
   - [Mini-Batch GD (1D)](#6c-mini-batch-gradient-descent-uses-a-batch-of-b-samples)
   - [Multiple Linear Regression GD (Vectorized)](#6d-multiple-linear-regression-via-batch-gradient-descent-vectorized)
   - [Weight Initializations Comparison](#6e-weight-initializations-comparison)
7. [Performance Metrics – Regression](#7-performance-metrics--regression)
   - [Saving & Loading Parameters to Text File](#saving--loading-model-parameters-to-text-file)
   - [Multi-Sheet Excel Reports](#saving-results--multi-sheet-excel-reports)
8. [Logistic Regression (Binary & One-vs-All)](#8-logistic-regression)
9. [Confusion Matrix & Classification Metrics](#9-confusion-matrix--classification-metrics)
   - [Class-Specific Accuracy & Macro Averaging](#class-specific-accuracy--macro-averaging)
10. [K-Fold Cross Validation](#10-k-fold-cross-validation)
    - [Hyperparameter Grid Search (Manual)](#hyperparameter-grid-search-manual)
11. [K-Means Clustering](#11-k-means-clustering)
    - [Vectorized Pairwise Distance Matrix](#vectorized-pairwise-distance-matrix-broadcasting)
12. [DBSCAN](#12-dbscan)
13. [Standard Library Implementations (scikit-learn)](#13-standard-library-implementations-scikit-learn)
    - [13.1 Label Encoding](#131-label-encoding)
    - [13.2 Train-Test Split](#132-train-test-split)
    - [13.3 Normalization & Scaling](#133-normalization--scaling)
    - [13.4 Linear Regression / OLS](#134-linear-regression--ols)
    - [13.5 Gradient Descent (SGDRegressor)](#135-gradient-descent-sgdregressor)
    - [13.6 Regression Metrics](#136-performance-metrics--regression)
    - [13.7 Logistic Regression](#137-logistic-regression-binary--multi-class)
    - [13.8 Confusion Matrix & Metrics](#138-confusion-matrix--classification-metrics)
    - [13.9 K-Fold CV & Grid Search](#139-k-fold-cross-validation--grid-search)
    - [13.10 K-Means Clustering & Silhouette](#1310-k-means-clustering--silhouette-score)
    - [13.11 DBSCAN](#1311-dbscan)
14. [Visualization / Graphs](#14-visualization--graphs)
    - [Train vs Test Comparison Curves](#train-vs-test-mean-rss--r2-comparison-curves)
    - [Feature Variance Analysis (without PCA)](#feature-variance-analysis-for-2d-visualization-without-pca)
15. [Quick Reference – Formulas](#quick-reference--formulas)

---

## 1. Imports

```python
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
```

> **Tip:** On paper, write these once at the top. Examiners expect them.

---

## 2. Data Reading & Preprocessing

### Using pandas

```python
df = pd.read_csv('data.csv')

# Drop rows with missing values in specific columns
df = df.dropna(subset=['col1', 'col2'])

# Shuffle the dataset
df = df.sample(frac=1, random_state=42).reset_index(drop=True)

# Access columns
X = df['feature_col'].values        # returns numpy array
Y = df['target_col'].values

# Basic stats
print(df.describe())
print(df.shape)                      # (rows, cols)
print(df.head())
```

> `dropna()` removes NaN rows. `sample(frac=1)` shuffles all rows.
> `.values` converts a pandas Series to a numpy array — needed for math.

### Categorical / Label Encoding (Class Names to Numbers)

```python
# Manual dictionary mapping (without package)
class_map = {
    'Iris-setosa': 0,
    'Iris-versicolor': 1,
    'Iris-virginica': 2
}
df['target'] = df['Species'].map(class_map)
y = df['target'].values
```

> Maps text category strings to integer numbers (0, 1, 2) needed for classification models.

### Generating Synthetic Regression Dataset

```python
# Create synthetic dataset with known weights and noise
np.random.seed(42)
n = 100

x1 = np.random.uniform(10, 100, n)      # continuous feature 1
x2 = np.random.randint(1, 10, n)        # discrete feature 2
noise = np.random.normal(0, 5, n)       # Gaussian noise mean=0, std=5

# Target: y = 5 + 2*x1 + 3*x2 + noise
y = 5 + 2 * x1 + 3 * x2 + noise

df_synthetic = pd.DataFrame({
    'x1': x1,
    'x2': x2,
    'y': y
})
df_synthetic.to_csv('synthetic_data.csv', index=False)
```

> Useful when an exam question asks to create custom synthetic data with specified features and noise.

---

## 3. Train-Test Split

### From scratch

```python
def train_test_split_manual(X, Y, train_ratio=0.8, seed=42):
    np.random.seed(seed)
    indices = np.arange(len(X))
    np.random.shuffle(indices)

    split = int(len(X) * train_ratio)

    X_train, X_test = X[indices[:split]], X[indices[split:]]
    Y_train, Y_test = Y[indices[:split]], Y[indices[split:]]

    return X_train, X_test, Y_train, Y_test
```

> Shuffles indices first, then slices. `train_ratio=0.8` means 80% train.

### Multi-Ratio Train-Test Split Loop (10:90 to 90:10)

```python
# Iterating over 9 different train-test split ratios
# x = train proportion (1 to 9), y = test proportion (9 to 1)
df = df.sample(frac=1, random_state=42).reset_index(drop=True)

for x in range(1, 10):
    y = 10 - x
    train_size = int(len(df) * (x / 10))

    train_data = df.iloc[:train_size]
    test_data  = df.iloc[train_size:]

    # Save splits to csv (common exam requirement)
    train_data.to_csv(f'set_{x}_{y}_train.csv', index=False)
    test_data.to_csv(f'set_{x}_{y}_test.csv', index=False)

    print(f"Split {x*10}:{(10-x)*10} -> Train: {len(train_data)}, Test: {len(test_data)}")
```

> Systematically generates 9 splits from 10:90 to 90:10 to evaluate how training set size impacts model performance.

---

## 4. Normalization & Scaling

### Min-Max Normalization (scales to [0, 1])

```python
# From scratch
def min_max_normalize(X):
    X_min = np.min(X, axis=0)
    X_max = np.max(X, axis=0)
    return (X - X_min) / (X_max - X_min)
```

> Formula: `X_norm = (X - X_min) / (X_max - X_min)`.
> Each feature is independently scaled to range [0, 1].

### Standardization / Z-score (mean=0, std=1)

```python
# From scratch
def standardize(X_train, X_test):
    mean = np.mean(X_train, axis=0)
    std  = np.std(X_train, axis=0)
    std[std == 0] = 1                  # avoid division by zero

    X_train_scaled = (X_train - mean) / std
    X_test_scaled  = (X_test  - mean) / std
    return X_train_scaled, X_test_scaled
```

> Formula: `X_std = (X - mean) / std`.
> **Important:** Fit on train only, then apply same mean/std to test.

---

## 5. OLS – Ordinary Least Squares

### From scratch (Simple Linear Regression: y = w0 + w1\*x)

```python
def ols_simple(X, Y):
    # w1 = Cov(X,Y) / Var(X)
    X_mean = np.mean(X)
    Y_mean = np.mean(Y)

    w1 = np.sum((X - X_mean) * (Y - Y_mean)) / np.sum((X - X_mean) ** 2)
    w0 = Y_mean - w1 * X_mean

    return w0, w1

# Predict
def predict_ols(X, w0, w1):
    return w0 + w1 * X
```

> `w1 = sum(xi - x_mean)(yi - y_mean) / sum(xi - x_mean)^2` — slope.
> `w0 = y_mean - w1 * x_mean` — intercept. This is the closed-form solution.

### From scratch (Multiple Linear Regression: Y = Xw)

```python
def ols_multiple(X, Y):
    # Add bias column of 1s
    X_b = np.c_[np.ones(X.shape[0]), X]   # shape: (n, d+1)

    # Normal equation: w = (X^T X)^(-1) X^T Y
    w = np.linalg.inv(X_b.T @ X_b) @ X_b.T @ Y
    return w                               # w[0]=intercept, w[1:]=slopes

# Predict
def predict_multiple(X, w):
    X_b = np.c_[np.ones(X.shape[0]), X]
    return X_b @ w
```

> Normal equation gives the exact solution in one step.
> `np.c_` adds a column of 1s for the bias/intercept term.

### Covariance, Variance, and Pearson Correlation (from scratch)

```python
def statistical_metrics(X, Y):
    n = len(X)
    x_mean = np.mean(X)
    y_mean = np.mean(Y)

    # Sample variance with Bessel's correction (n-1)
    var_x = np.sum((X - x_mean) ** 2) / (n - 1)
    var_y = np.sum((Y - y_mean) ** 2) / (n - 1)

    # Sample covariance (n-1)
    cov_xy = np.sum((X - x_mean) * (Y - y_mean)) / (n - 1)

    # Standard deviations
    std_x = np.sqrt(var_x)
    std_y = np.sqrt(var_y)

    # Pearson correlation coefficient r in [-1, +1]
    r_xy = cov_xy / (std_x * std_y)

    # Slope and intercept from covariance & correlation
    w1 = cov_xy / var_x                  # w1 = r_xy * (std_y / std_x)
    w0 = y_mean - w1 * x_mean

    return {
        'var_x': var_x,
        'cov_xy': cov_xy,
        'r_xy': r_xy,
        'w0': w0,
        'w1': w1
    }
```

> Proves that OLS slope is `w1 = Cov(X,Y) / Var(X) = r * (std_y / std_x)`.
> Bessel's correction `(n - 1)` provides an unbiased sample variance/covariance estimator.

---

## 6. Gradient Descent

### 6a. Batch Gradient Descent (uses ALL samples per step)

```python
def batch_gradient_descent(X, Y, alpha=0.001, epochs=1000):
    w0 = 0.0
    w1 = 0.0
    m = len(X)

    for _ in range(epochs):
        Y_pred = w0 + w1 * X
        error  = Y_pred - Y

        # Gradients (average over all m samples)
        dw0 = np.sum(error) / m
        dw1 = np.sum(error * X) / m

        # Update
        w0 = w0 - alpha * dw0
        w1 = w1 - alpha * dw1

    return w0, w1
```

> Uses **all** data points in each iteration to compute the gradient.
> Slow for large datasets but stable convergence.

### 6b. Stochastic Gradient Descent (uses 1 sample per step)

```python
def stochastic_gradient_descent(X, Y, alpha=0.001, epochs=100):
    w0 = 0.0
    w1 = 0.0
    m = len(X)

    for _ in range(epochs):
        for i in range(m):                   # one sample at a time
            Y_pred = w0 + w1 * X[i]
            error  = Y_pred - Y[i]

            w0 = w0 - alpha * error          # update per sample
            w1 = w1 - alpha * error * X[i]

    return w0, w1
```

> Updates weights after **each** single sample -> noisy but fast.
> Good for very large datasets. Can escape local minima due to noise.

### 6c. Mini-Batch Gradient Descent (uses a batch of B samples)

```python
def mini_batch_gd(X, Y, alpha=0.001, epochs=100, batch_size=32):
    w0 = 0.0
    w1 = 0.0
    m = len(X)

    for _ in range(epochs):
        for i in range(0, m, batch_size):
            X_batch = X[i:i + batch_size]
            Y_batch = Y[i:i + batch_size]

            b = len(X_batch)
            Y_pred = w0 + w1 * X_batch
            error = Y_pred - Y_batch

            dw0 = sum(error) / b
            dw1 = sum(error * X_batch) / b

            w0 = w0 - alpha * dw0
            w1 = w1 - alpha * dw1

    return w0, w1
```

> Middle ground: uses `batch_size` samples per update.
> Balances speed (SGD) and stability (Batch GD).

### 6d. Multiple Linear Regression via Batch Gradient Descent (Vectorized)

```python
def batch_gd_multiple(X, Y, alpha=0.01, epochs=1000):
    m = len(X)
    # Add bias column of 1s (shape: m, d+1)
    X_b = np.c_[np.ones(m), X]
    # X_b = np.concatenate((np.ones((m,1)), X), axis=1)
    w = np.zeros(X_b.shape[1])

    for _ in range(epochs):
        Y_pred = X_b @ w
        error  = Y_pred - Y
        gradient = (X_b.T @ error) / m
        w = w - alpha * gradient

    return w   # w[0] = intercept, w[1:] = feature slopes
```

> Matrix formulation for d features: `Y_pred = X_b @ w`, `gradient = (X_b.T @ error) / m`.
> Features must be scaled before running this for stable convergence.

### 6e. Weight Initializations Comparison

```python
# Testing different starting weights for gradient descent
np.random.seed(42)
initializations = {
    'Zero': (0.0, 0.0),
    'Random [0, 1]': (np.random.uniform(0, 1), np.random.uniform(0, 1)),
    'Random [0, 100]': (np.random.uniform(0, 100), np.random.uniform(0, 100))
}

for name, (w0_init, w1_init) in initializations.items():
    print(f"Init: {name} -> w0={w0_init:.2f}, w1={w1_init:.2f}")
    # run GD with w0_init, w1_init and compare final MSE / R2
```

> Large initial weights with large learning rate can cause gradient divergence (overflow).
> Zero or small random values near 0 typically converge reliably.

---

## 7. Performance Metrics – Regression

### From scratch

```python
def regression_metrics(Y_true, Y_pred):
    residuals = Y_true - Y_pred

    # RSS – Residual Sum of Squares
    RSS = np.sum(residuals ** 2)

    # Mean RSS (MSE)
    mean_RSS = RSS / len(Y_true)

    # TSS – Total Sum of Squares
    TSS = np.sum((Y_true - np.mean(Y_true)) ** 2)

    # R2 Score
    R2 = 1 - (RSS / TSS)

    # MAE – Mean Absolute Error
    MAE = np.mean(np.abs(residuals))

    # RMSE – Root Mean Squared Error
    RMSE = np.sqrt(mean_RSS)

    return {
        'RSS': RSS,
        'MSE': mean_RSS,
        'R2': R2,
        'MAE': MAE,
        'RMSE': RMSE
    }
```

> **R2 = 1 - RSS/TSS** -> closer to 1 is better.
> **MSE = RSS/n** -> average squared error. **RMSE = sqrt(MSE)**.
> **MAE** is more robust to outliers than MSE.

### Saving & Loading Model Parameters to Text File

```python
# Writing learned parameters to a text file
with open('model_params.txt', 'w') as f:
    f.write(f'w0 = {w0}\n')
    f.write(f'w1 = {w1}\n')

# Reading parameters back to make predictions
with open('model_params.txt', 'r') as f:
    w0_loaded = float(f.readline().split(' = ')[1])
    w1_loaded = float(f.readline().split(' = ')[1])

Y_pred = w0_loaded + w1_loaded * X_test
```

> Frequently asked in assignments/exams to persist model weights across runs.

### Saving Results & Multi-Sheet Excel Reports

```python
# Save results dataframe to CSV
results_df = pd.DataFrame(results_list)
results_df.to_csv('evaluation_results.csv', index=False)

# Save multiple dataframes into distinct sheets in one Excel file
with pd.ExcelWriter('model_report.xlsx') as writer:
    train_results_df.to_excel(writer, sheet_name='Train_Metrics', index=False)
    test_results_df.to_excel(writer, sheet_name='Test_Metrics', index=False)
```

> `pd.ExcelWriter` organizes multiple split results into clean labeled Excel sheets.

---

## 8. Logistic Regression

### From scratch (Binary Logistic Regression)

```python
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

def train_logistic(X, y, alpha=0.01, rho=0.001, epochs=1000):
    X_b = np.c_[np.ones(X.shape[0]), X]
    # X_b = np.contatenate((np.ones((len(X))), X), axis = 1)
    theta = np.zeros(X_b.shape[1])       # initialize weights to 0

    prev_error = float('inf')

    for epoch in range(epochs):
        z = X_b @ theta   # linear combination
        h = sigmoid(z)    # apply sigmoid

        h_safe = np.clip(h, 1e-15, 1 - 1e-15)

        # Binary Cross-Entropy Loss
        error = -np.mean(
            y * np.log(h_safe) + (1 - y) * np.log(1 - h_safe)
        )

        # Gradient
        gradient = (X_b.T @ (h - y)) / len(y)

        # Update weights
        theta = theta - alpha * gradient

        # Stopping condition
        if abs(prev_error - error) < rho:
            break
        prev_error = error

    return theta

def predict_logistic(X, theta):
    X_b = np.c_[np.ones(X.shape[0]), X]
    probs = sigmoid(X_b @ theta)
    return (probs >= 0.5).astype(int), probs
```

> **Sigmoid** squashes any value to (0, 1) -> interpreted as probability.
> **BCE Loss** = -[y*log(h) + (1-y)*log(1-h)].
> `rho` = convergence threshold; stop if loss barely changes.

### One-vs-All (Multi-class using Binary Logistic)

```python
def train_ova(X, y, alpha=0.01, rho=0.001, epochs=1000):
    all_theta = []
    num_classes = len(np.unique(y))

    for c in range(num_classes):
        # Current class = 1, all others = 0
        binary_y = (y == c).astype(int)
        theta = train_logistic(X, binary_y, alpha, rho, epochs)
        all_theta.append(theta)

    return np.array(all_theta)

def predict_ova(X, all_theta):
    X_b = np.c_[np.ones(len(X)), X]
    probs = sigmoid(X_b @ all_theta.T)    # (n, num_classes)
    predictions = np.argmax(probs, axis=1) # pick class with highest prob
    return predictions, probs
```

> Trains one binary classifier per class. At prediction, picks the class
> whose classifier gives the highest probability.

---

## 9. Confusion Matrix & Classification Metrics

### From scratch

```python
def confusion_matrix_manual(y_true, y_pred, num_classes):
    cm = np.zeros((num_classes, num_classes), dtype=int)

    for actual, predicted in zip(y_true, y_pred):
        cm[actual][predicted] += 1

    return cm
    # Rows = Actual class, Columns = Predicted class
    # cm[i][j] = count of samples that are class i but predicted as class j
    # Diagonal = correct predictions
```

> **Row i, Col j** = "was class i, predicted class j".
> Diagonal values = correct predictions (TP for each class).

### Metrics from Confusion Matrix

```python
def classification_metrics(cm):
    num_classes = cm.shape[0]
    total   = np.sum(cm)
    correct = np.trace(cm)                # sum of diagonal
    accuracy = correct / total

    precision_list = []
    recall_list    = []

    for i in range(num_classes):
        TP = cm[i][i]
        FP = np.sum(cm[:, i]) - TP       # column sum minus diagonal
        FN = np.sum(cm[i, :]) - TP       # row sum minus diagonal
        TN = total - TP - FP - FN

        precision = TP / (TP + FP) if (TP + FP) != 0 else 0
        recall    = TP / (TP + FN) if (TP + FN) != 0 else 0

        precision_list.append(precision)
        recall_list.append(recall)

    return {
        'accuracy': accuracy,
        'precision': precision_list,       # per class
        'recall': recall_list              # per class
    }
```

> **Accuracy** = correct / total.
> **Precision** = TP / (TP + FP) -> "of all predicted positive, how many correct?"
> **Recall** = TP / (TP + FN) -> "of all actual positive, how many found?"
> **F1 = 2 _ (P _ R) / (P + R)**.

### F1 Score (extra)

```python
def f1_score_manual(precision, recall):
    if precision + recall == 0:
        return 0
    return 2 * (precision * recall) / (precision + recall)
```

### Class-Specific Accuracy & Macro Averaging

```python
# From confusion matrix cm:
def extended_classification_metrics(cm, precision_list, recall_list):
    num_classes = cm.shape[0]
    class_acc = []

    for i in range(num_classes):
        TP = cm[i, i]
        class_total = np.sum(cm[i, :])    # actual instances of class i (TP + FN)
        acc = TP / class_total if class_total != 0 else 0
        class_acc.append(acc)

    # Macro averages (unweighted average across all classes)
    macro_precision = np.mean(precision_list)
    macro_recall    = np.mean(recall_list)
    macro_f1 = (
        2 * (macro_precision * macro_recall) / (macro_precision + macro_recall)
        if (macro_precision + macro_recall) != 0 else 0
    )

    return {
        'class_accuracy': class_acc,
        'macro_precision': macro_precision,
        'macro_recall': macro_recall,
        'macro_f1': macro_f1
    }
```

> **Class Accuracy** = TP / (TP + FN) = Recall of that class.
> **Macro Average** gives equal weight to every class regardless of class frequency.

---

## 10. K-Fold Cross Validation

### From scratch

```python
def k_fold_evaluate(X, y, k=5):
    idx = np.random.permutation(len(X))
    folds = np.array_split(idx, k)
    scores = []

    for fold_num in range(k):
        # Current fold = test, rest = train
        test_idx  = folds[fold_num]
        train_idx = np.concatenate([folds[i] for i in range(k) if i != fold_num])

        X_train, X_test = X[train_idx], X[test_idx]
        y_train, y_test = y[train_idx], y[test_idx]

        # --- Train your model here ---
        # e.g., w0, w1 = batch_gradient_descent(X_train, y_train)
        # Y_pred = w0 + w1 * X_test
        # score = r2_score or accuracy
        # scores.append(score)

    avg_score = np.mean(scores)
    return avg_score
```

> Each fold takes turns being the test set. The other k-1 folds are training.
> `fold_sizes[:len(X) % k] += 1` handles cases where n is not divisible by k.

### Validation Split (within training data for hyperparameter tuning)

```python
def validation_split(X, y, val_pct=0.10, seed=42):
    np.random.seed(seed)
    indices = np.arange(len(X))
    np.random.shuffle(indices)

    val_size = int(len(X) * val_pct)

    val_idx   = indices[:val_size]
    train_idx = indices[val_size:]

    return X[train_idx], X[val_idx], y[train_idx], y[val_idx]
```

> Used inside each fold: split the training portion further to tune hyperparams.

### Hyperparameter Grid Search (Manual)

```python
# Manual Grid Search using itertools.product (Assignment 06 style)
from itertools import product

learning_rates = [0.001, 0.01, 0.1]
epochs_list    = [500, 1000]

best_score  = -1
best_params = None

for alpha, epochs in product(learning_rates, epochs_list):
    # Train model on training split
    theta = train_logistic(X_train, y_train, alpha=alpha, epochs=epochs)

    # Evaluate on validation split
    y_val_pred, _ = predict_logistic(X_val, theta)
    val_acc = np.mean(y_val_pred == y_val)

    if val_acc > best_score:
        best_score = val_acc
        best_params = {'alpha': alpha, 'epochs': epochs}

print("Best Parameters:", best_params, "Best Val Acc:", best_score)
```

> **Grid search** tries every Cartesian product combination of candidate hyperparameters.
> Always select best parameters on the **validation set**, then test on the unseen **test set**.

---

## 11. K-Means Clustering

### From scratch

```python
def euclidean_distance(p1, p2):
    return np.sqrt(np.sum((p1 - p2) ** 2))

def kmeans_manual(X, k, max_iter=100, seed=42):
    np.random.seed(seed)

    # Step 1: Pick k random points as initial centroids
    random_idx = np.random.choice(len(X), k, replace=False)
    centroids  = X[random_idx]

    for _ in range(max_iter):
        # Step 2: Assign each point to nearest centroid
        clusters = []
        for point in X:
            distances = [euclidean_distance(point, c) for c in centroids]
            clusters.append(np.argmin(distances))
        clusters = np.array(clusters)

        # Step 3: Recalculate centroids
        new_centroids = []
        for i in range(k):
            points = X[clusters == i]
            if len(points) == 0:
                new_centroids.append(centroids[i])   # keep old if empty
            else:
                new_centroids.append(np.mean(points, axis=0))
        new_centroids = np.array(new_centroids)

        # Step 4: Check convergence
        if np.allclose(centroids, new_centroids):
            break
        centroids = new_centroids

    return clusters, centroids
```

> **K-Means algorithm:** (1) Init centroids -> (2) Assign points -> (3) Update centroids -> Repeat until stable.
> `np.allclose` checks if centroids stopped moving (converged).

### WCSS (Within-Cluster Sum of Squares)

```python
def calculate_wcss(X, clusters, centroids):
    wcss = 0
    for i in range(len(centroids)):
        points = X[clusters == i]
        for point in points:
            wcss += euclidean_distance(point, centroids[i]) ** 2
    return wcss
```

> WCSS measures how tight each cluster is. Lower = better.
> Used in the **Elbow Method** to find optimal K.

### Silhouette Score (from scratch)

```python
def silhouette_score_manual(X, clusters):
    n = len(X)
    labels = np.unique(clusters)
    scores = []

    for i in range(n):
        # a(i) = avg distance to same-cluster points
        same = X[clusters == clusters[i]]
        a_i = np.mean([euclidean_distance(X[i], p) for p in same
                        if not np.array_equal(p, X[i])])

        # b(i) = min avg distance to any other cluster
        b_i = float('inf')
        for label in labels:
            if label == clusters[i]:
                continue
            other = X[clusters == label]
            avg_dist = np.mean([euclidean_distance(X[i], p) for p in other])
            b_i = min(b_i, avg_dist)

        s_i = (b_i - a_i) / max(a_i, b_i)
        scores.append(s_i)

    return np.mean(scores)
```

> **Silhouette** ranges [-1, 1]. Higher = better separated clusters.
> `a` = intra-cluster distance, `b` = nearest other-cluster distance.

### Vectorized Pairwise Distance Matrix (Broadcasting)

```python
# Compute pairwise distance matrix between all samples (Eval 2 style)
def compute_distance_matrix(X):
    # Shape of diff is (n, n, d) via broadcasting
    diff = X[:, np.newaxis, :] - X[np.newaxis, :, :]
    return np.sqrt(np.sum(diff ** 2, axis=2))

# Compute distances from all samples to k centroids
def distances_to_centroids(X, centroids):
    # Shape of diff is (n, k, d)
    diff = X[:, np.newaxis, :] - centroids[np.newaxis, :, :]
    dist_matrix = np.linalg.norm(diff, axis=2)    # shape: (n, k)
    closest_cluster = np.argmin(dist_matrix, axis=1)
    return closest_cluster
```

> Avoids slow nested Python loops over samples when calculating pairwise or centroid distances.

---

## 12. DBSCAN

### From scratch

```python
def dbscan_manual(X, eps, min_pts):
    n = len(X)
    labels = np.full(n, -1)       # all start as noise (-1)
    cluster_id = 0

    # Precompute distance matrix
    dist_matrix = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            dist_matrix[i][j] = euclidean_distance(X[i], X[j])

    visited = [False] * n

    for i in range(n):
        if visited[i]:
            continue
        visited[i] = True

        # Find all neighbors within eps
        neighbors = list(np.where(dist_matrix[i] <= eps)[0])

        if len(neighbors) < min_pts:
            continue                      # noise point, skip

        # Start a new cluster
        labels[i] = cluster_id
        seeds = [nb for nb in neighbors if nb != i]

        while seeds:
            q = seeds.pop(0)

            if not visited[q]:
                visited[q] = True
                q_neighbors = list(np.where(dist_matrix[q] <= eps)[0])

                if len(q_neighbors) >= min_pts:    # q is also a core point
                    seeds.extend([nb for nb in q_neighbors if labels[nb] == -1])

            if labels[q] == -1:
                labels[q] = cluster_id

        cluster_id += 1

    return labels
```

> **Core point:** has >= min_pts neighbors within eps distance.
> **Border point:** within eps of a core point but has < min_pts neighbors.
> **Noise:** neither core nor border -> label stays -1.
> Unlike K-Means, DBSCAN finds clusters of arbitrary shape and doesn't need K.

---

## 13. Standard Library Implementations (scikit-learn)

> **Package Reference** — Sklearn implementations in the same chronological order as the syllabus above.

### 13.1 Label Encoding

```python
from sklearn.preprocessing import LabelEncoder

le = LabelEncoder()
y = le.fit_transform(df['Species'])
```

> Converts categorical text labels to integer values [0, 1, 2, ...].

### 13.2 Train-Test Split

```python
from sklearn.model_selection import train_test_split

X_train, X_test, Y_train, Y_test = train_test_split(
    X, Y, test_size=0.2, random_state=42
)
```

> `test_size=0.2` -> 20% test, 80% train.

### 13.3 Normalization & Scaling

```python
from sklearn.preprocessing import StandardScaler, MinMaxScaler

# Standardization (mean=0, std=1)
scaler = StandardScaler()
X_train_sc = scaler.fit_transform(X_train)   # fit + transform on train
X_test_sc  = scaler.transform(X_test)        # only transform on test

# Min-Max Scaling [0, 1]
scaler = MinMaxScaler()
X_train_mm = scaler.fit_transform(X_train)
X_test_mm  = scaler.transform(X_test)
```

> Always fit scaler on training data only to prevent data leakage.

### 13.4 Linear Regression / OLS

```python
from sklearn.linear_model import LinearRegression

model = LinearRegression()
model.fit(X_train.reshape(-1, 1), Y_train)   # reshape if 1D

w0 = model.intercept_
w1 = model.coef_[0]

Y_pred = model.predict(X_test.reshape(-1, 1))
```

> `intercept_` = w0, `coef_` = array of slopes.

### 13.5 Gradient Descent (SGDRegressor)

```python
from sklearn.linear_model import SGDRegressor

model = SGDRegressor(
    loss='squared_error',
    max_iter=50000,
    tol=1e-3,
    random_state=42
)
model.fit(X_train.reshape(-1, 1), Y_train)

w0 = model.intercept_[0]
w1 = model.coef_[0]

Y_pred = model.predict(X_test.reshape(-1, 1))
```

> `SGDRegressor` implements linear regression via stochastic gradient descent.

### 13.6 Performance Metrics – Regression

```python
from sklearn.metrics import mean_squared_error, r2_score, mean_absolute_error

mse  = mean_squared_error(Y_true, Y_pred)
r2   = r2_score(Y_true, Y_pred)
mae  = mean_absolute_error(Y_true, Y_pred)
rmse = np.sqrt(mse)
```

### 13.7 Logistic Regression (Binary & Multi-class)

```python
from sklearn.linear_model import LogisticRegression

model = LogisticRegression(max_iter=1000, random_state=42)
model.fit(X_train, Y_train)

Y_pred = model.predict(X_test)
probs  = model.predict_proba(X_test)         # class probabilities
```

> Handles multi-class automatically (uses OvR / multinomial).

### 13.8 Confusion Matrix & Classification Metrics

```python
from sklearn.metrics import (
    confusion_matrix, accuracy_score,
    precision_score, recall_score,
    f1_score, classification_report
)

cm        = confusion_matrix(y_true, y_pred)
accuracy  = accuracy_score(y_true, y_pred)
precision = precision_score(y_true, y_pred, average='macro')
recall    = recall_score(y_true, y_pred, average='macro')
f1        = f1_score(y_true, y_pred, average='macro')

# Full report (precision, recall, F1 per class)
print(classification_report(y_true, y_pred))
```

### 13.9 K-Fold Cross Validation & Grid Search

```python
from sklearn.model_selection import KFold, cross_val_score, GridSearchCV
from sklearn.linear_model import LogisticRegression

# 5-Fold Cross Validation
kf = KFold(n_splits=5, shuffle=True, random_state=42)
scores = cross_val_score(model, X, y, cv=kf, scoring='accuracy')
print("Mean CV score:", np.mean(scores))

# Manual loop with KFold
for train_idx, test_idx in kf.split(X):
    X_train, X_test = X[train_idx], X[test_idx]
    y_train, y_test = y[train_idx], y[test_idx]

# Hyperparameter Grid Search
param_grid = {'C': [0.01, 0.1, 1.0, 10.0], 'max_iter': [500, 1000]}
grid = GridSearchCV(LogisticRegression(), param_grid, cv=5, scoring='accuracy')
grid.fit(X, y)
print("Best Parameters:", grid.best_params_)
print("Best CV Score:", grid.best_score_)
```

### 13.10 K-Means Clustering & Silhouette Score

```python
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score

model = KMeans(n_clusters=3, random_state=42, n_init=10)
clusters = model.fit_predict(X_scaled)

wcss  = model.inertia_                       # within-cluster sum of squares
score = silhouette_score(X_scaled, clusters)
print("Centroids:", model.cluster_centers_)
```

### 13.11 DBSCAN

```python
from sklearn.cluster import DBSCAN

model = DBSCAN(eps=0.5, min_samples=5)
labels = model.fit_predict(X_scaled)

n_clusters = len(set(labels)) - (1 if -1 in labels else 0)
n_noise    = list(labels).count(-1)
print("Clusters:", n_clusters)
print("Noise points:", n_noise)
```

---

## 14. Visualization / Graphs

> _Lower exam probability but keep handy._

### Scatter Plot with Regression Line

```python
plt.figure(figsize=(8, 5))
plt.scatter(X, Y, c='blue', alpha=0.5, label='Data')

x_line = np.linspace(min(X), max(X), 100)
y_line = w0 + w1 * x_line
plt.plot(x_line, y_line, c='red', label='Regression Line')

plt.xlabel("Feature")
plt.ylabel("Target")
plt.title("Linear Regression")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('plot.png')
plt.show()
```

### Elbow Method (for K-Means)

```python
wcss_list = []
k_range = range(2, 9)

for k in k_range:
    clusters, centroids = kmeans_manual(X_scaled, k)
    wcss_list.append(calculate_wcss(X_scaled, clusters, centroids))

plt.plot(list(k_range), wcss_list, marker='o')
plt.xlabel("K")
plt.ylabel("WCSS")
plt.title("Elbow Method")
plt.grid(True)
plt.show()
```

> Look for the "elbow" — the K where WCSS stops dropping sharply.

### Confusion Matrix Heatmap

```python
plt.figure(figsize=(5, 4))
plt.imshow(cm, cmap='Blues')
plt.title("Confusion Matrix")
plt.xlabel("Predicted")
plt.ylabel("Actual")

# Add text labels
for i in range(cm.shape[0]):
    for j in range(cm.shape[1]):
        plt.text(j, i, cm[i, j], ha='center', va='center')

plt.colorbar()
plt.tight_layout()
plt.show()
```

### Cluster Visualization (with PCA)

```python
from sklearn.decomposition import PCA

pca = PCA(n_components=2)
X_2d = pca.fit_transform(X_scaled)

plt.scatter(X_2d[:, 0], X_2d[:, 1], c=clusters, cmap='viridis', s=50)
plt.xlabel("PCA 1")
plt.ylabel("PCA 2")
plt.title("Cluster Visualization")
plt.grid(True)
plt.show()
```

> PCA reduces 4+ features to 2D for plotting. Colors = cluster labels.

### Mean-RSS / R2 vs Train Percentage

```python
train_pcts = [10, 20, 30, 40, 50, 60, 70, 80, 90]

plt.plot(train_pcts, mse_list, marker='o', label='Test MSE')
plt.xlabel("% Training Samples")
plt.ylabel("MSE")
plt.title("MSE vs Training Size")
plt.legend()
plt.grid(True)
plt.show()
```

### Train vs Test Mean-RSS / R2 Comparison Curves

```python
# Comparing Train vs Test error across different training splits (Assignment 04 style)
training_percentages = [10, 20, 30, 40, 50, 60, 70, 80, 90]

plt.figure(figsize=(8, 5))
plt.plot(training_percentages, train_mse_list, marker='o', color='blue', label='Train MSE')
plt.plot(training_percentages, test_mse_list, marker='s', color='red', label='Test MSE')
plt.xlabel("Percentage of Training Samples")
plt.ylabel("Mean-RSS (MSE)")
plt.title("Train vs Test MSE vs Training Size")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
```

> If train error is very low but test error is high -> **Overfitting (High Variance)**.
> If both train and test errors are high -> **Underfitting (High Bias)**.

### Feature Variance Analysis for 2D Visualization (without PCA)

```python
# Select top 2 features with highest variance for 2D plotting (Eval 2 style)
tot_var = np.sum(np.var(X, axis=0))

for col_idx in range(X.shape[1]):
    var_i = np.var(X[:, col_idx])
    pct_var = (var_i / tot_var) * 100
    print(f"Feature {col_idx} variance: {var_i:.4f} ({pct_var:.2f}% of total)")

# Scatter plot using chosen top 2 features (e.g. index 0 and 1)
plt.figure(figsize=(8, 6))
plt.scatter(X[:, 0], X[:, 1], c=clusters, cmap='tab10', alpha=0.7, edgecolors='k')
plt.scatter(centroids[:, 0], centroids[:, 1], c='red', marker='X', s=180, label='Centroids')
plt.xlabel("Feature 0 (Highest Variance)")
plt.ylabel("Feature 1 (Second Highest Variance)")
plt.title("Cluster Visualization using High-Variance Features")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
```

> Explains why specific 2D projection axes are chosen when PCA is not allowed.

---

## Quick Reference – Formulas

| Metric                       | Formula                                     |
| ---------------------------- | ------------------------------------------- |
| **MSE**                      | `(1/n) * sum(yi - yi_hat)^2`                |
| **RMSE**                     | `sqrt(MSE)`                                 |
| **MAE**                      | `(1/n) * sum(abs(yi - yi_hat))`             |
| **R2**                       | `1 - (RSS / TSS)`                           |
| **RSS**                      | `sum(yi - yi_hat)^2`                        |
| **TSS**                      | `sum(yi - y_mean)^2`                        |
| **Sample Variance**          | `(1/(n-1)) * sum(xi - x_mean)^2`            |
| **Sample Covariance**        | `(1/(n-1)) * sum(xi - x_mean)(yi - y_mean)` |
| **Pearson Correlation (r)**  | `Cov(X,Y) / (std_x * std_y)`                |
| **OLS slope (simple)**       | `Cov(X,Y) / Var(X) = r * (std_y / std_x)`   |
| **OLS intercept**            | `y_mean - w1 * x_mean`                      |
| **OLS Matrix (Normal Eq)**   | `w = (X^T X)^(-1) X^T Y`                    |
| **GD Gradient (vectorized)** | `(1/m) * X_b^T (X_b w - Y)`                 |
| **Sigmoid**                  | `1 / (1 + e^(-z))`                          |
| **BCE Loss**                 | `-[y*log(h) + (1-y)*log(1-h)]`              |
| **Precision**                | `TP / (TP + FP)`                            |
| **Recall**                   | `TP / (TP + FN)`                            |
| **F1**                       | `2 * P * R / (P + R)`                       |
| **Accuracy**                 | `correct / total`                           |
| **Euclidean**                | `sqrt(sum(ai - bi)^2)`                      |
| **Silhouette**               | `(b - a) / max(a, b)`                       |
| **Z-score**                  | `(X - mean) / std`                          |
| **Min-Max**                  | `(X - X_min) / (X_max - X_min)`             |

---

> **Exam Tip:** For "without package" questions, write the from-scratch version.
> For "with package" questions, use sklearn imports. Always add `import` lines.
> Keep variable names clear (`X_train`, `Y_pred`, `w0`, `w1`) — examiners appreciate readability.
