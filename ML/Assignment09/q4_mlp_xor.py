import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Setup directories
script_dir = os.path.dirname(os.path.abspath(__file__))
plots_dir = os.path.join(script_dir, "plots")
output_dir = os.path.join(script_dir, "output")

os.makedirs(plots_dir, exist_ok=True)
os.makedirs(output_dir, exist_ok=True)

print("=" * 60)
print("PRACTICE ASSIGNMENT 8 - QUESTION 4: BACKPROPAGATION MLP ON XOR GATE")
print("=" * 60)

# -------------------------------------------------------------
# 4. Generate XOR Dataset with 70:10:20 Split
# -------------------------------------------------------------
np.random.seed(42)

# Generate 200 samples (50 per XOR quadrant) to enable 70:10:20 split
num_samples_per_state = 50
xor_bases = np.array([
    [0, 0],
    [0, 1],
    [1, 0],
    [1, 1]
])
xor_targets = np.array([0, 1, 1, 0])

X_list, y_list = [], []
for base, target in zip(xor_bases, xor_targets):
    # Add slight Gaussian noise around the binary coordinates
    cluster = base + np.random.normal(0, 0.05, size=(num_samples_per_state, 2))
    X_list.append(cluster)
    y_list.extend([target] * num_samples_per_state)

X = np.vstack(X_list)
y = np.array(y_list)

# Stratified 70:10:20 Split (140 train, 20 val, 40 test)
train_idx, val_idx, test_idx = [], [], []
for cls in [0, 1]:
    cls_indices = np.where(y == cls)[0]
    np.random.shuffle(cls_indices)
    # Total 100 per class -> 70 train, 10 val, 20 test
    train_idx.extend(cls_indices[:70])
    val_idx.extend(cls_indices[70:80])
    test_idx.extend(cls_indices[80:100])

train_idx = np.array(train_idx)
val_idx = np.array(val_idx)
test_idx = np.array(test_idx)

X_train, y_train = X[train_idx], y[train_idx]
X_val, y_val = X[val_idx], y[val_idx]
X_test, y_test = X[test_idx], y[test_idx]

print(f"XOR Dataset Generated: Total = {len(X)}")
print(f"Split: Train = {len(X_train)} (70%), Val = {len(X_val)} (10%), Test = {len(X_test)} (20%)")


# -------------------------------------------------------------
# MLP Implementation from Scratch (No in-built packages)
# -------------------------------------------------------------
def sigmoid(z):
    z_clipped = np.clip(z, -500, 500)
    return 1.0 / (1.0 + np.exp(-z_clipped))


def sigmoid_derivative(a):
    return a * (1.0 - a)


class MLP_XOR:
    """
    MLP with Error Back-propagation from scratch.
    - Architecture: 2 Inputs -> 1 Hidden Layer (2 neurons) -> 1 Output (Sigmoid)
    - Activation: Sigmoid
    - Weight Init: Random initialization
    - Learning rate: alpha = 0.1
    """
    def __init__(self, input_dim=2, hidden_dim=2, output_dim=1, alpha=0.1, seed=42):
        np.random.seed(seed)
        self.alpha = alpha
        # Random weight initialization
        self.W1 = np.random.randn(input_dim, hidden_dim) * 0.5
        self.b1 = np.zeros((1, hidden_dim))
        self.W2 = np.random.randn(hidden_dim, output_dim) * 0.5
        self.b2 = np.zeros((1, output_dim))
        self.losses = []

    def forward(self, X):
        self.Z1 = X @ self.W1 + self.b1
        self.A1 = sigmoid(self.Z1)
        self.Z2 = self.A1 @ self.W2 + self.b2
        self.A2 = sigmoid(self.Z2)
        return self.A2

    def compute_loss(self, y_true, y_pred):
        m = len(y_true)
        y_safe = np.clip(y_pred, 1e-15, 1.0 - 1e-15)
        loss = -np.mean(y_true * np.log(y_safe) + (1.0 - y_true) * np.log(1.0 - y_safe))
        return loss

    def backward(self, X, y_true):
        m = X.shape[0]
        y_true = y_true.reshape(-1, 1)

        # Output layer error
        dZ2 = self.A2 - y_true
        dW2 = (self.A1.T @ dZ2) / m
        db2 = np.sum(dZ2, axis=0, keepdims=True) / m

        # Hidden layer error
        dA1 = dZ2 @ self.W2.T
        dZ1 = dA1 * sigmoid_derivative(self.A1)
        dW1 = (X.T @ dZ1) / m
        db1 = np.sum(dZ1, axis=0, keepdims=True) / m

        # Gradient descent weight updates
        self.W2 -= self.alpha * dW2
        self.b2 -= self.alpha * db2
        self.W1 -= self.alpha * dW1
        self.b1 -= self.alpha * db1

    def train(self, X, y, epochs=2, verbose=True):
        for epoch in range(epochs):
            y_pred = self.forward(X)
            loss = self.compute_loss(y.reshape(-1, 1), y_pred)
            self.losses.append(loss)
            self.backward(X, y)
            if verbose or (epoch + 1) % 500 == 0:
                print(f"Epoch {epoch + 1}/{epochs} - Train Loss: {loss:.5f}")
        return self

    def predict(self, X, threshold=0.5):
        probs = self.forward(X)
        return (probs >= threshold).astype(int).flatten()


# -------------------------------------------------------------
# Metrics Function
# -------------------------------------------------------------
def confusion_matrix_manual(y_true, y_pred):
    cm = np.zeros((2, 2), dtype=int)
    for actual, pred in zip(y_true, y_pred):
        cm[actual, pred] += 1
    return cm


def evaluate_metrics(cm, dataset_name=""):
    total = np.sum(cm)
    accuracy = np.trace(cm) / total if total > 0 else 0.0

    class_names = ["Class 0", "Class 1"]
    records = []
    for i, c_name in enumerate(class_names):
        tp = cm[i, i]
        fn = np.sum(cm[i, :]) - tp
        fp = np.sum(cm[:, i]) - tp
        tn = total - tp - fn - fp

        c_acc = tp / (tp + fn) if (tp + fn) > 0 else 0.0
        p = tp / (tp + fp) if (tp + fp) > 0 else 0.0
        r = tp / (tp + fn) if (tp + fn) > 0 else 0.0
        f1 = (2 * p * r) / (p + r) if (p + r) > 0 else 0.0

        records.append({
            "Dataset": dataset_name,
            "Class": c_name,
            "Accuracy (Sensitivity)": round(c_acc, 4),
            "Precision": round(p, 4),
            "Recall": round(r, 4),
            "F1-Score": round(f1, 4),
            "TP": tp,
            "FP": fp,
            "FN": fn,
            "TN": tn
        })

    return accuracy, pd.DataFrame(records)


# -------------------------------------------------------------
# 4(a) Train for Exactly 2 Epochs & Report Metrics
# -------------------------------------------------------------
print("\n--- Training MLP for exactly 2 Epochs (as specified) ---")
mlp = MLP_XOR(input_dim=2, hidden_dim=2, output_dim=1, alpha=0.1, seed=42)
mlp.train(X_train, y_train, epochs=2)

train_preds = mlp.predict(X_train)
test_preds = mlp.predict(X_test)

cm_train = confusion_matrix_manual(y_train, train_preds)
cm_test = confusion_matrix_manual(y_test, test_preds)

train_acc, train_metrics_df = evaluate_metrics(cm_train, dataset_name="Train (2 Epochs)")
test_acc, test_metrics_df = evaluate_metrics(cm_test, dataset_name="Test (2 Epochs)")

print(f"\nTraining Results (after 2 epochs) - Overall Accuracy: {train_acc:.4f}:")
print(train_metrics_df.to_string(index=False))

print(f"\nTesting Results (after 2 epochs) - Overall Accuracy: {test_acc:.4f}:")
print(test_metrics_df.to_string(index=False))

# Also test on exact 4 canonical points of XOR
canonical_X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
canonical_y = np.array([0, 1, 1, 0])
canonical_preds = mlp.predict(canonical_X)
print("\nPredictions on canonical 4 XOR coordinates after 2 epochs:")
for pt, target, pred in zip(canonical_X, canonical_y, canonical_preds):
    print(f"  Input: {pt} -> True: {target}, Predicted: {pred}")


# -------------------------------------------------------------
# Extended Training for Convergence Analysis (Demonstrating MLP capability)
# -------------------------------------------------------------
print("\n--- Extended Training for 2000 Epochs to demonstrate XOR non-linear convergence ---")
mlp_extended = MLP_XOR(input_dim=2, hidden_dim=2, output_dim=1, alpha=0.5, seed=42)
mlp_extended.train(X_train, y_train, epochs=2000, verbose=False)

ext_train_preds = mlp_extended.predict(X_train)
ext_test_preds = mlp_extended.predict(X_test)
ext_train_acc = np.mean(ext_train_preds == y_train)
ext_test_acc = np.mean(ext_test_preds == y_test)
print(f"Extended Training Converged Accuracy: Train = {ext_train_acc:.2%}, Test = {ext_test_acc:.2%}")


# -------------------------------------------------------------
# Visualizations
# -------------------------------------------------------------
# 1. Confusion Matrix after 2 Epochs
fig, axes = plt.subplots(1, 2, figsize=(10, 4))
for ax, cm, title, acc in [
    (axes[0], cm_train, "Train Confusion Matrix (2 Epochs)", train_acc),
    (axes[1], cm_test, "Test Confusion Matrix (2 Epochs)", test_acc)
]:
    im = ax.imshow(cm, cmap="Blues", interpolation="nearest")
    ax.set_title(f"{title}\nAccuracy = {acc:.2%}", fontweight="bold")
    ax.set_xlabel("Predicted")
    ax.set_ylabel("Actual")
    ax.set_xticks([0, 1])
    ax.set_yticks([0, 1])
    ax.set_xticklabels(["Class 0", "Class 1"])
    ax.set_yticklabels(["Class 0", "Class 1"])
    for r in range(2):
        for c in range(2):
            color = "white" if cm[r, c] > np.max(cm)/2 else "black"
            ax.text(c, r, str(cm[r, c]), ha="center", va="center", color=color, fontsize=12, fontweight="bold")

plt.subplots_adjust(right=0.88)
cbar_ax = fig.add_axes([0.90, 0.2, 0.02, 0.6])
fig.colorbar(im, cax=cbar_ax)
plt.savefig(os.path.join(plots_dir, "q4_xor_cm_2_epochs.png"), dpi=300)
plt.close()

# 2. Decision Boundary Comparison (2 Epochs vs Converged)
fig, axes = plt.subplots(1, 2, figsize=(12, 5))
x_min, x_max = X[:, 0].min() - 0.2, X[:, 0].max() + 0.2
y_min, y_max = X[:, 1].min() - 0.2, X[:, 1].max() + 0.2
xx, yy = np.meshgrid(np.linspace(x_min, x_max, 200), np.linspace(y_min, y_max, 200))
grid_pts = np.c_[xx.ravel(), yy.ravel()]

for ax, model, title in [
    (axes[0], mlp, "Decision Boundary (After 2 Epochs)"),
    (axes[1], mlp_extended, "Decision Boundary (Converged)")
]:
    Z = model.forward(grid_pts).reshape(xx.shape)
    ax.contourf(xx, yy, Z, levels=50, cmap="RdBu", alpha=0.7)
    ax.scatter(X[y == 0, 0], X[y == 0, 1], color="blue", edgecolors="k", label="Class 0", s=40)
    ax.scatter(X[y == 1, 0], X[y == 1, 1], color="red", edgecolors="k", label="Class 1", s=40)
    ax.set_title(title, fontweight="bold")
    ax.set_xlabel("x1")
    ax.set_ylabel("x2")
    ax.legend()
    ax.grid(True, linestyle="--", alpha=0.4)

plt.tight_layout()
plt.savefig(os.path.join(plots_dir, "q4_xor_decision_boundary.png"), dpi=300)
plt.close()


# -------------------------------------------------------------
# Save Outputs to Excel and CSV
# -------------------------------------------------------------
out_excel = os.path.join(output_dir, "q4_mlp_xor_results.xlsx")
out_csv = os.path.join(output_dir, "q4_mlp_xor_metrics.csv")

combined_df = pd.concat([train_metrics_df, test_metrics_df], ignore_index=True)

with pd.ExcelWriter(out_excel, engine="openpyxl") as writer:
    combined_df.to_excel(writer, sheet_name="2 Epochs Metrics", index=False)
    summary_df = pd.DataFrame([
        {"Setting": "Activation", "Value": "Sigmoid"},
        {"Setting": "Hidden Layers", "Value": 1},
        {"Setting": "Hidden Neurons", "Value": 2},
        {"Setting": "Learning Rate", "Value": 0.1},
        {"Setting": "Epochs", "Value": 2},
        {"Setting": "Train Accuracy (2 Epochs)", "Value": train_acc},
        {"Setting": "Test Accuracy (2 Epochs)", "Value": test_acc},
        {"Setting": "Train Accuracy (Converged)", "Value": ext_train_acc},
        {"Setting": "Test Accuracy (Converged)", "Value": ext_test_acc}
    ])
    summary_df.to_excel(writer, sheet_name="Summary", index=False)

combined_df.to_csv(out_csv, index=False)

print(f"\nQ4 Outputs saved to:")
print(f"  - {out_excel}")
print(f"  - {out_csv}")
print(f"  - Plots saved in {plots_dir}")
