import os
import warnings
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.neural_network import MLPClassifier
from sklearn.exceptions import ConvergenceWarning

warnings.filterwarnings('ignore', category=ConvergenceWarning)

# Setup directories
script_dir = os.path.dirname(os.path.abspath(__file__))
dataset_dir = os.path.join(script_dir, "dataset")
plots_dir = os.path.join(script_dir, "plots")
output_dir = os.path.join(script_dir, "output")

os.makedirs(plots_dir, exist_ok=True)
os.makedirs(output_dir, exist_ok=True)

print("=" * 60)
print("PRACTICE ASSIGNMENT 8 - QUESTION 5: MLP ON PIMA DIABETES DATASET")
print("=" * 60)

# -------------------------------------------------------------
# 5. Read Dataset
# -------------------------------------------------------------
csv_path = os.path.join(dataset_dir, "diabetes.csv")
df = pd.read_csv(csv_path)

print(f"\nPima Indian Diabetes Dataset Loaded: {df.shape[0]} rows, {df.shape[1]} columns")
print(df.head())

target_col = "Outcome"
feature_cols = [c for c in df.columns if c != target_col]

X_raw = df[feature_cols].values
y = df[target_col].values.astype(int)

class_names = ["No Diabetes (0)", "Diabetes (1)"]
print(f"Class Counts: Class 0 = {np.sum(y == 0)}, Class 1 = {np.sum(y == 1)}")


# -------------------------------------------------------------
# Stratified 5-Fold Cross Validation Setup
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


def standardize(X_train, X_test):
    mean = np.mean(X_train, axis=0)
    std = np.std(X_train, axis=0)
    std[std == 0] = 1.0
    return (X_train - mean) / std, (X_test - mean) / std


def confusion_matrix_manual(y_true, y_pred):
    cm = np.zeros((2, 2), dtype=int)
    for actual, pred in zip(y_true, y_pred):
        cm[actual, pred] += 1
    return cm


def calculate_metrics(cm):
    total = np.sum(cm)
    correct = np.trace(cm)
    accuracy = correct / total if total > 0 else 0.0

    class_acc = []
    precision = []
    recall = []

    for i in range(2):
        tp = cm[i, i]
        fn = np.sum(cm[i, :]) - tp
        fp = np.sum(cm[:, i]) - tp

        c_acc = tp / (tp + fn) if (tp + fn) > 0 else 0.0
        p = tp / (tp + fp) if (tp + fp) > 0 else 0.0
        r = tp / (tp + fn) if (tp + fn) > 0 else 0.0

        class_acc.append(c_acc)
        precision.append(p)
        recall.append(r)

    return {
        "accuracy": accuracy,
        "class_acc": class_acc,
        "precision": precision,
        "recall": recall
    }


# -------------------------------------------------------------
# Train and Evaluate for 50 and 100 Epochs
# -------------------------------------------------------------
folds = create_stratified_k_folds(y, k=5, seed=42)
epoch_settings = [50, 100]

results_dict = {}
avg_results_dict = {}
cumulative_cms = {ep: np.zeros((2, 2), dtype=int) for ep in epoch_settings}
sample_loss_curves = {}

for epochs in epoch_settings:
    print(f"\n--- Running 5-Fold Cross-Validation for Epochs = {epochs} ---")
    fold_records = []

    for fold_idx in range(5):
        test_idx = folds[fold_idx]
        train_idx = np.concatenate([folds[j] for j in range(5) if j != fold_idx])

        X_train, X_test = X_raw[train_idx], X_raw[test_idx]
        y_train, y_test = y[train_idx], y[test_idx]

        X_train_s, X_test_s = standardize(X_train, X_test)

        # Settings matching Q4:
        # - Activation function: Sigmoid ('logistic')
        # - Number of hidden layers: 1
        # - Number of neurons in hidden layer: 2
        # - Random initialization (random_state=42 + fold_idx)
        # - Learning rate: alpha = 0.1
        # - Solver: 'sgd' with batch/standard gradient descent
        mlp = MLPClassifier(
            hidden_layer_sizes=(2,),
            activation='logistic',
            solver='sgd',
            learning_rate_init=0.1,
            max_iter=epochs,
            random_state=42 + fold_idx,
            shuffle=True
        )

        mlp.fit(X_train_s, y_train)

        if fold_idx == 0:
            sample_loss_curves[epochs] = mlp.loss_curve_

        y_pred = mlp.predict(X_test_s)
        cm = confusion_matrix_manual(y_test, y_pred)
        cumulative_cms[epochs] += cm
        metrics = calculate_metrics(cm)

        fold_records.append({
            "Epochs": epochs,
            "Fold": fold_idx + 1,
            "Overall Accuracy": metrics["accuracy"],
            "Class 0 Accuracy": metrics["class_acc"][0],
            "Class 1 Accuracy": metrics["class_acc"][1],
            "Class 0 Precision": metrics["precision"][0],
            "Class 1 Precision": metrics["precision"][1],
            "Class 0 Recall": metrics["recall"][0],
            "Class 1 Recall": metrics["recall"][1],
        })

    df_epochs = pd.DataFrame(fold_records)
    results_dict[epochs] = df_epochs
    avg_df = df_epochs.drop(columns=["Fold", "Epochs"]).mean()
    avg_results_dict[epochs] = avg_df

    print(f"\nFold-wise Results for {epochs} Epochs:")
    print(df_epochs.to_string(index=False))
    print(f"\n5-Fold Average Results for {epochs} Epochs:")
    print(avg_df.to_frame(name="Average").to_string())

# Comparison table
comparison_df = pd.DataFrame([
    {
        "Epochs": ep,
        "Overall Accuracy": avg_results_dict[ep]["Overall Accuracy"],
        "Class 0 Precision": avg_results_dict[ep]["Class 0 Precision"],
        "Class 1 Precision": avg_results_dict[ep]["Class 1 Precision"],
        "Class 0 Recall": avg_results_dict[ep]["Class 0 Recall"],
        "Class 1 Recall": avg_results_dict[ep]["Class 1 Recall"],
        "Class 0 Accuracy": avg_results_dict[ep]["Class 0 Accuracy"],
        "Class 1 Accuracy": avg_results_dict[ep]["Class 1 Accuracy"],
    }
    for ep in epoch_settings
])

print("\n" + "=" * 60)
print("COMPARISON: 50 EPOCHS vs 100 EPOCHS (5-Fold Average)")
print("=" * 60)
print(comparison_df.to_string(index=False))


# -------------------------------------------------------------
# Visualizations
# -------------------------------------------------------------
# 1. Loss Curves Comparison
plt.figure(figsize=(8, 4.5))
for ep in epoch_settings:
    plt.plot(sample_loss_curves[ep], label=f"Max Iter = {ep}", linewidth=2)
plt.xlabel("Iteration", fontsize=11)
plt.ylabel("Loss (Cross-Entropy)", fontsize=11)
plt.title("MLP Training Loss Curves on Diabetes Dataset (alpha=0.1, hidden=(2,))", fontsize=12, fontweight="bold")
plt.legend()
plt.grid(True, linestyle="--", alpha=0.6)
plt.tight_layout()
plt.savefig(os.path.join(plots_dir, "q5_diabetes_loss_curves.png"), dpi=300)
plt.close()

# 2. Confusion Matrices for 50 vs 100 Epochs
fig, axes = plt.subplots(1, 2, figsize=(10, 4.2))
for ax, ep in zip(axes, epoch_settings):
    cm = cumulative_cms[ep]
    im = ax.imshow(cm, cmap="Blues", interpolation="nearest")
    acc = np.trace(cm) / np.sum(cm)
    ax.set_title(f"Cumulative CM ({ep} Epochs)\nAccuracy = {acc:.2%}", fontweight="bold")
    ax.set_xlabel("Predicted")
    ax.set_ylabel("Actual")
    ax.set_xticks([0, 1])
    ax.set_yticks([0, 1])
    ax.set_xticklabels(["No Diabetes", "Diabetes"])
    ax.set_yticklabels(["No Diabetes", "Diabetes"])

    for r in range(2):
        for c in range(2):
            color = "white" if cm[r, c] > np.max(cm)/2 else "black"
            ax.text(c, r, str(cm[r, c]), ha="center", va="center", color=color, fontsize=12, fontweight="bold")

plt.subplots_adjust(right=0.88)
cbar_ax = fig.add_axes([0.90, 0.15, 0.02, 0.7])
fig.colorbar(im, cax=cbar_ax)
plt.savefig(os.path.join(plots_dir, "q5_diabetes_cm_comparison.png"), dpi=300)
plt.close()

# 3. Bar Chart of Metrics Comparison
fig, ax = plt.subplots(figsize=(9, 5))
metrics_names = ["Overall Accuracy", "Class 0 Recall", "Class 1 Recall", "Class 0 Precision", "Class 1 Precision"]
x_pos = np.arange(len(metrics_names))
bar_width = 0.35

ax.bar(x_pos - bar_width/2, [avg_results_dict[50][m] for m in metrics_names], width=bar_width, label="50 Epochs", color="royalblue")
ax.bar(x_pos + bar_width/2, [avg_results_dict[100][m] for m in metrics_names], width=bar_width, label="100 Epochs", color="darkorange")

ax.set_xticks(x_pos)
ax.set_xticklabels(metrics_names, rotation=15, ha="right", fontsize=10)
ax.set_ylabel("5-Fold Average Value", fontsize=11)
ax.set_title("Performance Comparison on Diabetes Dataset: 50 vs 100 Epochs", fontsize=12, fontweight="bold")
ax.set_ylim(0, 1.0)
ax.grid(axis="y", linestyle="--", alpha=0.6)
ax.legend()
plt.tight_layout()
plt.savefig(os.path.join(plots_dir, "q5_diabetes_metrics_barchart.png"), dpi=300)
plt.close()


# -------------------------------------------------------------
# Save Outputs to Excel and CSV
# -------------------------------------------------------------
out_excel = os.path.join(output_dir, "q5_mlp_diabetes_results.xlsx")
out_csv = os.path.join(output_dir, "q5_mlp_diabetes_comparison.csv")

with pd.ExcelWriter(out_excel, engine="openpyxl") as writer:
    comparison_df.to_excel(writer, sheet_name="Comparison", index=False)
    results_dict[50].to_excel(writer, sheet_name="50 Epochs Folds", index=False)
    avg_results_dict[50].to_frame(name="Average").to_excel(writer, sheet_name="50 Epochs Average")
    results_dict[100].to_excel(writer, sheet_name="100 Epochs Folds", index=False)
    avg_results_dict[100].to_frame(name="Average").to_excel(writer, sheet_name="100 Epochs Average")

comparison_df.to_csv(out_csv, index=False)

print(f"\nQ5 Outputs saved to:")
print(f"  - {out_excel}")
print(f"  - {out_csv}")
print(f"  - Plots saved in {plots_dir}")
