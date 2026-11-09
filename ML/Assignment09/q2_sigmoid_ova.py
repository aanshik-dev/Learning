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
print("PRACTICE ASSIGNMENT 8 - QUESTION 2: SIGMOID OVA ON IRIS DATASET")
print("=" * 60)

# -------------------------------------------------------------
# 2. Read Dataset & Prepare Splits
# -------------------------------------------------------------
csv_path = os.path.join(dataset_dir, "Iris.csv")
df = pd.read_csv(csv_path)

# Remove Id column if present
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

print(f"\nDataset loaded: {len(df)} samples, {len(feature_cols)} features.")
print("Class counts:", {name: int(np.sum(y == i)) for i, name in enumerate(class_names)})

# Split: 70% Train (105 samples), 10% Validation (15 samples), 20% (30 samples) Test
# Exact stratified split to ensure equal representation per class (35 train, 5 val, 10 test per class)
np.random.seed(42)
train_indices, val_indices, test_indices = [], [], []

for c in range(num_classes):
    c_idx = np.where(y == c)[0]
    np.random.shuffle(c_idx)
    # 50 per class -> 35 train (70%), 5 val (10%), 10 test (20% = 30 samples total)
    train_indices.extend(c_idx[:35])
    val_indices.extend(c_idx[35:40])
    test_indices.extend(c_idx[40:50])

train_indices = np.array(train_indices)
val_indices = np.array(val_indices)
test_indices = np.array(test_indices)

print(f"Data Split: Train = {len(train_indices)} (70%), Validation = {len(val_indices)} (10%), Test = {len(test_indices)} (30 samples)")

X_train, y_train = X_raw[train_indices], y[train_indices]
X_val, y_val = X_raw[val_indices], y[val_indices]
X_test, y_test = X_raw[test_indices], y[test_indices]

# Standardization
mean_train = np.mean(X_train, axis=0)
std_train = np.std(X_train, axis=0)
std_train[std_train == 0] = 1.0

X_train_s = (X_train - mean_train) / std_train
X_val_s = (X_val - mean_train) / std_train
X_test_s = (X_test - mean_train) / std_train


# -------------------------------------------------------------
# Sigmoid Neuron & OVA Implementation
# -------------------------------------------------------------
def sigmoid(z):
    z_clipped = np.clip(z, -500, 500)
    return 1.0 / (1.0 + np.exp(-z_clipped))


def train_sigmoid_neuron(X, y_binary, alpha=0.1, epochs=500):
    """Train single binary sigmoid neuron with batch gradient descent."""
    m, d = X.shape
    X_bias = np.c_[np.ones(m), X]
    theta = np.zeros(d + 1)
    loss_history = []

    for _ in range(epochs):
        z = X_bias @ theta
        h = sigmoid(z)
        h_safe = np.clip(h, 1e-15, 1 - 1e-15)
        loss = -np.mean(y_binary * np.log(h_safe) + (1 - y_binary) * np.log(1 - h_safe))
        loss_history.append(loss)

        grad = (X_bias.T @ (h - y_binary)) / m
        theta -= alpha * grad

    return theta, loss_history


def train_ova(X, y, alpha=0.1, epochs=500):
    """Train K binary sigmoid neurons under One-vs-All strategy."""
    all_thetas = []
    all_losses = []
    for c in range(num_classes):
        y_binary = (y == c).astype(int)
        theta_c, loss_c = train_sigmoid_neuron(X, y_binary, alpha=alpha, epochs=epochs)
        all_thetas.append(theta_c)
        all_losses.append(loss_c)
    return np.array(all_thetas), all_losses


def predict_ova(X, all_thetas):
    """Predict class using argmax of sigmoid neuron probabilities."""
    X_bias = np.c_[np.ones(X.shape[0]), X]
    probs = sigmoid(X_bias @ all_thetas.T)
    preds = np.argmax(probs, axis=1)
    return preds, probs


# -------------------------------------------------------------
# Metrics Function
# -------------------------------------------------------------
def confusion_matrix_manual(y_true, y_pred, n_classes=3):
    cm = np.zeros((n_classes, n_classes), dtype=int)
    for actual, pred in zip(y_true, y_pred):
        cm[actual, pred] += 1
    return cm


def calculate_metrics(cm, class_labels):
    total = np.sum(cm)
    correct = np.trace(cm)
    accuracy = correct / total if total > 0 else 0.0

    records = []
    for i, c_name in enumerate(class_labels):
        tp = cm[i, i]
        fn = np.sum(cm[i, :]) - tp
        fp = np.sum(cm[:, i]) - tp
        tn = total - tp - fn - fp

        c_acc = tp / (tp + fn) if (tp + fn) > 0 else 0.0
        p = tp / (tp + fp) if (tp + fp) > 0 else 0.0
        r = tp / (tp + fn) if (tp + fn) > 0 else 0.0
        f1 = (2 * p * r) / (p + r) if (p + r) > 0 else 0.0

        records.append({
            "Class": c_name,
            "Accuracy (Sensitivity)": c_acc,
            "Precision": p,
            "Recall": r,
            "F1-Score": f1,
            "TP": tp,
            "FP": fp,
            "FN": fn,
            "TN": tn
        })

    return accuracy, pd.DataFrame(records)


# -------------------------------------------------------------
# 2(a) Hyperparameter Tuning on Validation Split
# -------------------------------------------------------------
learning_rates = [0.01, 0.05, 0.1, 0.5]
epochs_list = [100, 200, 500, 1000]

tuning_results = []
best_val_acc = -1.0
best_params = None

print("\n--- 2(a) Running Hyperparameter Tuning on Validation Split ---")
for alpha in learning_rates:
    for ep in epochs_list:
        thetas, _ = train_ova(X_train_s, y_train, alpha=alpha, epochs=ep)
        val_pred, _ = predict_ova(X_val_s, thetas)
        val_acc = np.mean(val_pred == y_val)

        tuning_results.append({
            "Learning Rate (alpha)": alpha,
            "Epochs": ep,
            "Validation Accuracy": val_acc
        })

        if val_acc > best_val_acc:
            best_val_acc = val_acc
            best_params = (alpha, ep)

tuning_df = pd.DataFrame(tuning_results)
print(tuning_df.to_string(index=False))

best_alpha, best_epochs = best_params
print(f"\nBest Hyperparameters: Learning Rate = {best_alpha}, Epochs = {best_epochs} (Val Accuracy = {best_val_acc:.4f})")


# -------------------------------------------------------------
# 2(b) Final Training & Evaluation on Train and Test Samples
# -------------------------------------------------------------
print("\n--- 2(b) Final Model Training & Evaluation ---")
final_thetas, loss_histories = train_ova(X_train_s, y_train, alpha=best_alpha, epochs=best_epochs)

# Predictions
train_pred, train_probs = predict_ova(X_train_s, final_thetas)
test_pred, test_probs = predict_ova(X_test_s, final_thetas)

cm_train = confusion_matrix_manual(y_train, train_pred, n_classes=num_classes)
cm_test = confusion_matrix_manual(y_test, test_pred, n_classes=num_classes)

train_acc, train_metrics_df = calculate_metrics(cm_train, class_names)
test_acc, test_metrics_df = calculate_metrics(cm_test, class_names)

print(f"\nOverall Training Accuracy: {train_acc:.4f}")
print("Training Class-wise Metrics:")
print(train_metrics_df.to_string(index=False))

print(f"\nOverall Testing Accuracy: {test_acc:.4f}")
print("Testing Class-wise Metrics:")
print(test_metrics_df.to_string(index=False))


# -------------------------------------------------------------
# Visualizations
# -------------------------------------------------------------
# 1. Loss Curves for 3 OVA Neurons
plt.figure(figsize=(8, 5))
for c_idx, c_name in enumerate(class_names):
    plt.plot(loss_histories[c_idx], label=f"Neuron {c_idx} ({c_name} vs All)", linewidth=2)
plt.xlabel("Epoch", fontsize=11)
plt.ylabel("Binary Cross-Entropy Loss", fontsize=11)
plt.title(f"Sigmoid OVA Loss Curves (alpha={best_alpha}, epochs={best_epochs})", fontsize=12, fontweight="bold")
plt.legend()
plt.grid(True, linestyle="--", alpha=0.6)
plt.tight_layout()
plt.savefig(os.path.join(plots_dir, "q2_loss_curves.png"), dpi=300)
plt.close()

# 2. Confusion Matrices for Train and Test
fig, axes = plt.subplots(1, 2, figsize=(11, 4.5))
for ax, cm, title, acc in [
    (axes[0], cm_train, "Training Set", train_acc),
    (axes[1], cm_test, "Testing Set", test_acc)
]:
    im = ax.imshow(cm, cmap="Blues", interpolation="nearest")
    ax.set_title(f"{title} (Accuracy = {acc:.2%})", fontweight="bold")
    ax.set_xlabel("Predicted Class")
    ax.set_ylabel("Actual Class")
    ax.set_xticks(range(3))
    ax.set_yticks(range(3))
    ax.set_xticklabels(class_names)
    ax.set_yticklabels(class_names)

    for r in range(3):
        for c in range(3):
            color = "white" if cm[r, c] > np.max(cm)/2 else "black"
            ax.text(c, r, str(cm[r, c]), ha="center", va="center", color=color, fontsize=12, fontweight="bold")

plt.subplots_adjust(right=0.88)
cbar_ax = fig.add_axes([0.90, 0.15, 0.02, 0.7])
fig.colorbar(im, cax=cbar_ax)
plt.savefig(os.path.join(plots_dir, "q2_cm_train_test.png"), dpi=300)
plt.close()


# -------------------------------------------------------------
# Save Outputs
# -------------------------------------------------------------
out_excel = os.path.join(output_dir, "q2_onevsall_results.xlsx")
out_csv = os.path.join(output_dir, "q2_onevsall_tuning.csv")

with pd.ExcelWriter(out_excel, engine="openpyxl") as writer:
    tuning_df.to_excel(writer, sheet_name="Hyperparameter Tuning", index=False)
    train_metrics_df.to_excel(writer, sheet_name="Train Metrics", index=False)
    test_metrics_df.to_excel(writer, sheet_name="Test Metrics", index=False)
    pd.DataFrame([{
        "Best Learning Rate": best_alpha,
        "Best Epochs": best_epochs,
        "Validation Accuracy": best_val_acc,
        "Train Overall Accuracy": train_acc,
        "Test Overall Accuracy": test_acc
    }]).to_excel(writer, sheet_name="Best Model Summary", index=False)

tuning_df.to_csv(out_csv, index=False)

print(f"\nQ2 Outputs saved to:")
print(f"  - {out_excel}")
print(f"  - {out_csv}")
print(f"  - Plots saved in {plots_dir}")

