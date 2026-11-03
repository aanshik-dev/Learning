import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.metrics import precision_score, recall_score, f1_score, silhouette_score

os.makedirs("./Eval3/plots", exist_ok=True)
os.makedirs("./Eval3/output", exist_ok=True)

# A)
df = pd.read_csv("./Eval3/dataset/creditcard.csv")
print("DATASET EXPLORATION")
print(f"Dataset Dimensions: {df.shape[0]} rows, {df.shape[1]} columns")
print(f"Attribute Names: {df.columns.tolist()}")
missing_vals = df.isnull().sum().sum()
print(f"\nTotal Missing Values: {missing_vals}")

desc_stats = df.describe()
desc_stats.to_csv("./Eval3/output/descriptive_statistics.csv")
print("\nDescriptive statistics saved !!")

class_counts = df["Class"].value_counts()
class_pct = df["Class"].value_counts(normalize=True) * 100
print("\nClass Distribution:")
print(f"  Legitimate (0): {class_counts[0]} ({class_pct[0]:.4f}%)")
print(f"  Fraudulent (1): {class_counts[1]} ({class_pct[1]:.4f}%)")

# B)
feature_cols = [f"V{i}" for i in range(1, 29)] + ["Amount"]
X = df[feature_cols].values
y = df["Class"].values

# Z-score standardization: (X - mean) / std
x_mean = np.mean(X, axis=0)
x_std = np.std(X, axis=0)
x_std[x_std == 0] = 1.0
X_scaled = (X - x_mean) / x_std

# C): Manual K-Means implementation
def run_kmeans(X, k, max_iter=40, tol=1e-4, seed=42):
    np.random.seed(seed)
    n, d = X.shape
    # Randomly initialize centroids from data points
    centroids = X[np.random.choice(n, k, replace=False)].copy()
    x_sq = np.sum(X ** 2, axis=1, keepdims=True)

    for it in range(max_iter):
        c_sq = np.sum(centroids ** 2, axis=1, keepdims=True).T
        dot = np.dot(X, centroids.T)
        dists_sq = np.maximum(x_sq - 2 * dot + c_sq, 0)
        labels = np.argmin(dists_sq, axis=1)

        # Update centroids
        new_centroids = np.zeros((k, 2))
        for j in range(k):
            cluster_pts = X[labels == j]
            if len(cluster_pts) > 0:
                new_centroids[j] = cluster_pts.mean(axis=0)
            else:
                new_centroids[j] = X[np.random.randint(n)]

        shift = np.linalg.norm(new_centroids - centroids)
        centroids = new_centroids
        if shift < tol:
            break

    c_sq = np.sum(centroids ** 2, axis=1, keepdims=True).T
    dot = np.dot(X, centroids.T)
    dists_sq = np.maximum(x_sq - 2 * dot + c_sq, 0)
    labels = np.argmin(dists_sq, axis=1)
    min_distances = np.sqrt(np.min(dists_sq, axis=1))

    return centroids, labels, min_distances

configs = [2, 3, 4, 5, 6]
results = []

for k in configs:
    centroids, labels, distances = run_kmeans(X_scaled, k, seed=42)

    # Unusual observations based on the 95th percentile distance threshold
    threshold = np.percentile(distances, 95)
    unusual = (distances > threshold).astype(int)

    n_unusual = int(np.sum(unusual))
    unusual_pct = (n_unusual / len(df)) * 100

    # F): Compare unusual observations with actual Class labels
    precision = precision_score(y, unusual, zero_division=0)
    recall = recall_score(y, unusual, zero_division=0)
    f1 = f1_score(y, unusual, zero_division=0)

    # G): Compute Silhouette Score excluding identified noise points
    clean_mask = (unusual == 0)
    clean_X = X_scaled[clean_mask]
    clean_labels = labels[clean_mask]
    clean_clusters = np.unique(clean_labels)

    if len(clean_clusters) >= 2:
        try:
            score = silhouette_score(clean_X, clean_labels, sample_size=10000, random_state=42)
            score_str = f"{score:.4f}"
            sil_val = round(score, 4)
        except Exception:
            score_str = "-"
            sil_val = np.nan
    else:
        score_str = "-"
        sil_val = np.nan

    results.append({
        "K": k,
        "Clusters": len(np.unique(labels)),
        "Distance_Threshold": round(float(threshold), 4),
        "Unusual_Count": n_unusual,
        "Unusual_Percentage": round(unusual_pct, 4),
        "Precision": round(precision, 4),
        "Recall": round(recall, 4),
        "F1_Score": round(f1, 4),
        "Silhouette_Score": sil_val
    })

    print(f"\nConfiguration K={k}:")
    print(f"  Clusters Formed: {len(np.unique(labels))}")
    print(f"  Anomaly Distance Threshold: {threshold:.4f}")
    print(f"  Unusual Observations: {n_unusual} ({unusual_pct:.2f}%)")
    print(f"  Precision: {precision:.4f} | Recall: {recall:.4f} | F1-Score: {f1:.4f}")
    print(f"  Silhouette Score (Noise Excluded): {score_str}")

    # E): Visualize clusters and unusual observations (V1 vs V2)
    plt.figure(figsize=(8, 6))
    plt.scatter(df["V1"], df["V2"], c=labels, cmap="viridis", s=2, alpha=0.4, rasterized=True)
    plt.xlabel("V1")
    plt.ylabel("V2")
    plt.title(f"K-Means Clustering (K={k})")
    plt.tight_layout()
    plt.savefig(f"./Eval3/plots/kmeans_k_{k}.png", dpi=150)
    plt.close()

    plt.figure(figsize=(8, 6))
    plt.scatter(df.loc[unusual == 0, "V1"], df.loc[unusual == 0, "V2"],
                c="blue", s=2, alpha=0.3, label="Normal", rasterized=True)
    plt.scatter(df.loc[unusual == 1, "V1"], df.loc[unusual == 1, "V2"],
                c="red", marker="x", s=8, alpha=0.7, label="Unusual", rasterized=True)
    plt.xlabel("V1")
    plt.ylabel("V2")
    plt.title(f"Unusual Observations Detection (K={k})")
    plt.legend(loc="upper right")
    plt.tight_layout()
    plt.savefig(f"./Eval3/plots/unusual_k_{k}.png", dpi=150)
    plt.close()

# Visualize actual legitimate and fraudulent transactions
plt.figure(figsize=(8, 6))
plt.scatter(df.loc[y == 0, "V1"], df.loc[y == 0, "V2"],
            c="royalblue", s=2, alpha=0.3, label="Legitimate", rasterized=True)
plt.scatter(df.loc[y == 1, "V1"], df.loc[y == 1, "V2"],
            c="crimson", marker="x", s=12, alpha=0.9, label="Fraudulent", rasterized=True)
plt.xlabel("V1")
plt.ylabel("V2")
plt.title("Actual Classes (Legitimate vs Fraudulent)")
plt.legend(loc="upper right")
plt.tight_layout()
plt.savefig("./Eval3/plots/actual_classes.png", dpi=150)
plt.close()

# Save summary results
results_df = pd.DataFrame(results)
results_df.to_csv("./Eval3/output/clustering_results.csv", index=False)

print("\nCOMPARISON OF CONFIGURATIONS")
print(results_df.to_string(index=False))
