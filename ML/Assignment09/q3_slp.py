import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Setup directories
script_dir = os.path.dirname(os.path.abspath(__file__))
dataset_dir = os.path.join(script_dir, "dataset")
plots_dir = os.path.join(script_dir, "plots")
output_dir = os.path.join(script_dir, "output")

os.makedirs(plots_dir, exist_ok=True)
os.makedirs(output_dir, exist_ok=True)

print("=" * 60)
print("PRACTICE ASSIGNMENT 8 - QUESTION 3: SINGLE-LAYER PERCEPTRON (SLP)")
print("=" * 60)

# -------------------------------------------------------------
# 3. Read Dataset
# -------------------------------------------------------------
csv_path = os.path.join(dataset_dir, "Iris.csv")
df = pd.read_csv(csv_path)

feature_cols = ["SepalLengthCm", "SepalWidthCm", "PetalLengthCm", "PetalWidthCm"]
species_map = {
    "Iris-setosa": 0,
    "Iris-versicolor": 1,
    "Iris-virginica": 2
}
df["target"] = df["Species"].map(species_map)

X_raw = df[feature_cols].values
y = df["target"].values.astype(int)

class_names = ["Setosa", "Versicolor", "Virginica"]
num_classes = len(class_names)


# -------------------------------------------------------------
# Single Architecture SLP Implementation
# -------------------------------------------------------------
def sigmoid(z):
    z_clipped = np.clip(z, -500, 500)
    return 1.0 / (1.0 + np.exp(-z_clipped))


def one_hot_encode(y, num_classes):
    m = len(y)
    Y = np.zeros((m, num_classes))
    Y[np.arange(m), y] = 1.0
    return Y


class SingleLayerPerceptron:
    """Multiclass Single-Layer Perceptron (SLP) in a single architecture."""
    def __init__(self, input_dim=4, output_dim=3, alpha=0.1, epochs=500, seed=42):
        self.input_dim = input_dim
        self.output_dim = output_dim
        self.alpha = alpha
        self.epochs = epochs
        self.seed = seed
        self.W = None
        self.loss_history = []

    def fit(self, X, y):
        np.random.seed(self.seed)
        m = X.shape[0]
        # Include bias: W shape is (input_dim + 1, output_dim)
        X_bias = np.c_[np.ones(m), X]
        self.W = np.random.randn(self.input_dim + 1, self.output_dim) * 0.01
        Y_onehot = one_hot_encode(y, self.output_dim)
        self.loss_history = []

        for _ in range(self.epochs):
            # Forward pass: Z = X_bias * W, A = sigmoid(Z)
            Z = X_bias @ self.W
            A = sigmoid(Z)
            A_safe = np.clip(A, 1e-15, 1.0 - 1e-15)

            # Cross-entropy loss across all classes
            loss = -np.mean(np.sum(Y_onehot * np.log(A_safe) + (1.0 - Y_onehot) * np.log(1.0 - A_safe), axis=1))
            self.loss_history.append(loss)

            # Backward pass: dZ = (A - Y) / m
            dZ = (A - Y_onehot) / m
            dW = X_bias.T @ dZ

            # Update weights
            self.W -= self.alpha * dW

        return self

    def predict_proba(self, X):
        m = X.shape[0]
        X_bias = np.c_[np.ones(m), X]
        return sigmoid(X_bias @ self.W)

    def predict(self, X):
        probs = self.predict_proba(X)
        return np.argmax(probs, axis=1)


# -------------------------------------------------------------
# Stratified 5-Fold Cross Validation
# -------------------------------------------------------------
def create_stratified_k_folds(y, k=5, seed=42):
    np.random.seed(seed)
    folds = [[] for _ in range(k)]
    for c in np.unique(y):
        c_indices = np.where(y == c)[0]
        np.random.shuffle(c_indices)
        for i, idx in enumerate(c_indices):
            folds[i % k].append(idx)
    return [np.array(f) for f in folds]


def confusion_matrix_manual(y_true, y_pred, n_classes=3):
    cm = np.zeros((n_classes, n_classes), dtype=int)
    for actual, pred in zip(y_true, y_pred):
        cm[actual, pred] += 1
    return cm


def calculate_metrics(cm, class_labels):
    total = np.sum(cm)
    correct = np.trace(cm)
    accuracy = correct / total if total > 0 else 0.0

    class_accuracies = []
    precisions = []
    recalls = []

    for i in range(len(class_labels)):
        tp = cm[i, i]
        fn = np.sum(cm[i, :]) - tp
        fp = np.sum(cm[:, i]) - tp
        tn = total - tp - fn - fp

        c_acc = tp / (tp + fn) if (tp + fn) > 0 else 0.0
        p = tp / (tp + fp) if (tp + fp) > 0 else 0.0
        r = tp / (tp + fn) if (tp + fn) > 0 else 0.0

        class_accuracies.append(c_acc)
        precisions.append(p)
        recalls.append(r)

    return accuracy, class_accuracies, precisions, recalls


folds = create_stratified_k_folds(y, k=5, seed=42)
fold_results = []
total_cm = np.zeros((num_classes, num_classes), dtype=int)
sample_loss_history = None

print("\n--- Running 5-Fold Cross Validation with SLP ---")
for fold_idx in range(5):
    test_idx = folds[fold_idx]
    train_idx = np.concatenate([folds[j] for j in range(5) if j != fold_idx])

    X_train, X_test = X_raw[train_idx], X_raw[test_idx]
    y_train, y_test = y[train_idx], y[test_idx]

    # Standardize
    mean_tr = np.mean(X_train, axis=0)
    std_tr = np.std(X_train, axis=0)
    std_tr[std_tr == 0] = 1.0

    X_train_s = (X_train - mean_tr) / std_tr
    X_test_s = (X_test - mean_tr) / std_tr

    # Train SLP
    slp = SingleLayerPerceptron(input_dim=4, output_dim=3, alpha=0.2, epochs=600, seed=fold_idx)
    slp.fit(X_train_s, y_train)

    if fold_idx == 0:
        sample_loss_history = slp.loss_history

    y_pred = slp.predict(X_test_s)
    cm = confusion_matrix_manual(y_test, y_pred, n_classes=num_classes)
    total_cm += cm

    acc, class_accs, precs, recs = calculate_metrics(cm, class_names)

    row = {
        "Fold": fold_idx + 1,
        "Overall Accuracy": acc,
        "Setosa Accuracy": class_accs[0],
        "Versicolor Accuracy": class_accs[1],
        "Virginica Accuracy": class_accs[2],
        "Setosa Precision": precs[0],
        "Versicolor Precision": precs[1],
        "Virginica Precision": precs[2],
        "Setosa Recall": recs[0],
        "Versicolor Recall": recs[1],
        "Virginica Recall": recs[2]
    }
    fold_results.append(row)

results_df = pd.DataFrame(fold_results)
print("\nFOLD-WISE EVALUATION RESULTS:")
print(results_df.to_string(index=False))

# Average across 5 folds
avg_metrics = results_df.drop(columns=["Fold"]).mean()
print("\n5-FOLD AVERAGE METRICS:")
print(avg_metrics.to_frame(name="5-Fold Average"))

best_fold_idx = results_df["Overall Accuracy"].idxmax()
best_fold = results_df.loc[best_fold_idx]
print("\nBEST FOLD:")
print(best_fold)


# -------------------------------------------------------------
# Visualizations
# -------------------------------------------------------------
# 1. Loss curve
plt.figure(figsize=(7, 4.5))
plt.plot(sample_loss_history, color="darkblue", linewidth=2)
plt.xlabel("Epoch", fontsize=11)
plt.ylabel("Cross-Entropy Loss", fontsize=11)
plt.title("Single-Layer Perceptron (SLP) Training Loss", fontsize=12, fontweight="bold")
plt.grid(True, linestyle="--", alpha=0.6)
plt.tight_layout()
plt.savefig(os.path.join(plots_dir, "q3_slp_loss_curve.png"), dpi=300)
plt.close()

# 2. Cumulative 5-Fold Confusion Matrix
fig, ax = plt.subplots(figsize=(6, 5))
im = ax.imshow(total_cm, cmap="Blues", interpolation="nearest")
ax.set_title("5-Fold Cumulative Confusion Matrix (SLP)", fontsize=12, fontweight="bold")
ax.set_xlabel("Predicted Class", fontsize=11)
ax.set_ylabel("Actual Class", fontsize=11)
ax.set_xticks(range(3))
ax.set_yticks(range(3))
ax.set_xticklabels(class_names)
ax.set_yticklabels(class_names)

for r in range(3):
    for c in range(3):
        color = "white" if total_cm[r, c] > np.max(total_cm)/2 else "black"
        ax.text(c, r, str(total_cm[r, c]), ha="center", va="center", color=color, fontsize=12, fontweight="bold")

plt.colorbar(im, ax=ax, fraction=0.046, pad=0.04)
plt.tight_layout()
plt.savefig(os.path.join(plots_dir, "q3_slp_confusion_matrix.png"), dpi=300)
plt.close()


# -------------------------------------------------------------
# Save Outputs to Excel and CSV
# -------------------------------------------------------------
out_excel = os.path.join(output_dir, "q3_slp_results.xlsx")
out_csv = os.path.join(output_dir, "q3_slp_average_metrics.csv")

with pd.ExcelWriter(out_excel, engine="openpyxl") as writer:
    results_df.to_excel(writer, sheet_name="Fold Results", index=False)
    avg_metrics.to_frame(name="Average").to_excel(writer, sheet_name="Average Metrics")
    best_fold.to_frame(name="Best Fold").to_excel(writer, sheet_name="Best Fold")
    cm_df = pd.DataFrame(total_cm, index=[f"Actual {c}" for c in class_names], columns=[f"Predicted {c}" for c in class_names])
    cm_df.to_excel(writer, sheet_name="Cumulative CM")

avg_metrics.to_frame(name="Average").to_csv(out_csv)

print(f"\nQ3 Outputs saved to:")
print(f"  - {out_excel}")
print(f"  - {out_csv}")
print(f"  - Plots saved in {plots_dir}")

