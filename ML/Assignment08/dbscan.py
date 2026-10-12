import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from sklearn.preprocessing import StandardScaler
from sklearn.cluster import DBSCAN
from sklearn.metrics import silhouette_score
from sklearn.decomposition import PCA


# 1. Read the dataset
url = "https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data"

columns = [
    "sepal_length",
    "sepal_width",
    "petal_length",
    "petal_width",
    "class"
]

df = pd.read_csv(url, names=columns)
df = df.dropna()

print("Dataset:")
print(df.head())
print("\nDataset shape:", df.shape)


# 2. Remove class label (unsupervised)
X = df.iloc[:, :-1].values

print("\nFeatures used for clustering:")
print(df.iloc[:, :-1].head())


# 3. Standardize the features
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


# 4. Euclidean distance
def euclidean_distance(p1, p2):
    return np.sqrt(np.sum((p1 - p2) ** 2))


# 5. Custom DBSCAN implementation
def custom_dbscan(X, eps, min_pts):
    n = len(X)
    labels = np.full(n, -1)
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
            continue  # noise point

        # Start new cluster
        labels[i] = cluster_id
        seeds = [nb for nb in neighbors if nb != i]

        while seeds:
            q = seeds.pop(0)

            if not visited[q]:
                visited[q] = True
                q_neighbors = list(np.where(dist_matrix[q] <= eps)[0])

                if len(q_neighbors) >= min_pts:
                    seeds.extend([nb for nb in q_neighbors if labels[nb] == -1])

            if labels[q] == -1:
                labels[q] = cluster_id

        cluster_id += 1

    return labels


# 6. Run custom DBSCAN with different parameters
eps_values = [0.3, 0.5, 0.7, 0.9, 1.1]
min_pts_values = [3, 5, 7]

custom_results = []

for eps in eps_values:
    for min_pts in min_pts_values:
        labels = custom_dbscan(X_scaled, eps, min_pts)

        n_clusters = len(set(labels)) - (1 if -1 in labels else 0)
        n_noise = list(labels).count(-1)

        if n_clusters >= 2:
            non_noise = labels != -1
            if np.sum(non_noise) > 1 and len(set(labels[non_noise])) >= 2:
                score = silhouette_score(X_scaled[non_noise], labels[non_noise])
            else:
                score = -1
        else:
            score = -1

        custom_results.append({
            'eps': eps,
            'min_pts': min_pts,
            'n_clusters': n_clusters,
            'n_noise': n_noise,
            'silhouette': round(score, 4)
        })

        print(f"Custom DBSCAN eps={eps}, min_pts={min_pts} -> "
              f"Clusters={n_clusters}, Noise={n_noise}, Silhouette={score:.4f}")

custom_df = pd.DataFrame(custom_results)
print("\nCustom DBSCAN Results:")
print(custom_df)


# 7. PCA for visualization
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)


# 8. Visualize custom DBSCAN clusters
# Pick top results with different cluster counts
best_custom = custom_df[custom_df['n_clusters'] >= 2].sort_values(
    'silhouette', ascending=False
).head(6)

fig, axes = plt.subplots(2, 3, figsize=(15, 8))
plot_idx = 0

for _, row in best_custom.iterrows():
    eps = row['eps']
    min_pts = int(row['min_pts'])

    labels = custom_dbscan(X_scaled, eps, min_pts)

    r = plot_idx // 3
    c = plot_idx % 3

    scatter = axes[r, c].scatter(
        X_pca[:, 0], X_pca[:, 1],
        c=labels, cmap="viridis", s=40
    )
    axes[r, c].set_title(f"eps={eps}, min_pts={min_pts}")
    axes[r, c].set_xlabel("PCA 1")
    axes[r, c].set_ylabel("PCA 2")

    plot_idx += 1

# Hide unused subplots
for i in range(plot_idx, 6):
    axes[i // 3, i % 3].axis("off")

plt.suptitle("Custom DBSCAN Clustering")
plt.tight_layout()
plt.savefig("Assignment08/custom_dbscan_clusters.png")
plt.show()


# 9. Sklearn DBSCAN
sklearn_results = []

for eps in eps_values:
    for min_pts in min_pts_values:
        model = DBSCAN(eps=eps, min_samples=min_pts)
        labels = model.fit_predict(X_scaled)

        n_clusters = len(set(labels)) - (1 if -1 in labels else 0)
        n_noise = list(labels).count(-1)

        if n_clusters >= 2:
            non_noise = labels != -1
            if np.sum(non_noise) > 1 and len(set(labels[non_noise])) >= 2:
                score = silhouette_score(X_scaled[non_noise], labels[non_noise])
            else:
                score = -1
        else:
            score = -1

        sklearn_results.append({
            'eps': eps,
            'min_pts': min_pts,
            'n_clusters': n_clusters,
            'n_noise': n_noise,
            'silhouette': round(score, 4)
        })

        print(f"Sklearn DBSCAN eps={eps}, min_pts={min_pts} -> "
              f"Clusters={n_clusters}, Noise={n_noise}, Silhouette={score:.4f}")

sklearn_df = pd.DataFrame(sklearn_results)
print("\nSklearn DBSCAN Results:")
print(sklearn_df)


# 10. Visualize sklearn DBSCAN clusters
best_sklearn = sklearn_df[sklearn_df['n_clusters'] >= 2].sort_values(
    'silhouette', ascending=False
).head(6)

fig, axes = plt.subplots(2, 3, figsize=(15, 8))
plot_idx = 0

for _, row in best_sklearn.iterrows():
    eps = row['eps']
    min_pts = int(row['min_pts'])

    model = DBSCAN(eps=eps, min_samples=min_pts)
    labels = model.fit_predict(X_scaled)

    r = plot_idx // 3
    c = plot_idx % 3

    axes[r, c].scatter(
        X_pca[:, 0], X_pca[:, 1],
        c=labels, cmap="viridis", s=40
    )
    axes[r, c].set_title(f"eps={eps}, min_pts={min_pts}")
    axes[r, c].set_xlabel("PCA 1")
    axes[r, c].set_ylabel("PCA 2")

    plot_idx += 1

for i in range(plot_idx, 6):
    axes[i // 3, i % 3].axis("off")

plt.suptitle("Sklearn DBSCAN Clustering")
plt.tight_layout()
plt.savefig("Assignment08/sklearn_dbscan_clusters.png")
plt.show()


# 11. Comparison table
print("\n--- Comparison: Custom vs Sklearn DBSCAN ---")

comparison = pd.merge(
    custom_df, sklearn_df,
    on=['eps', 'min_pts'],
    suffixes=('_custom', '_sklearn')
)

print(comparison[[
    'eps', 'min_pts',
    'n_clusters_custom', 'n_clusters_sklearn',
    'n_noise_custom', 'n_noise_sklearn',
    'silhouette_custom', 'silhouette_sklearn'
]])


# 12. Best parameters
best_custom_row = custom_df[custom_df['silhouette'] > 0].sort_values(
    'silhouette', ascending=False
).head(1)

best_sklearn_row = sklearn_df[sklearn_df['silhouette'] > 0].sort_values(
    'silhouette', ascending=False
).head(1)

print("\nBest Custom DBSCAN:")
print(best_custom_row)

print("\nBest Sklearn DBSCAN:")
print(best_sklearn_row)


# 13. Final clustering with best parameters
if len(best_sklearn_row) > 0:
    final_eps = best_sklearn_row.iloc[0]['eps']
    final_min_pts = int(best_sklearn_row.iloc[0]['min_pts'])

    final_model = DBSCAN(eps=final_eps, min_samples=final_min_pts)
    final_labels = final_model.fit_predict(X_scaled)

    plt.figure(figsize=(8, 6))
    plt.scatter(
        X_pca[:, 0], X_pca[:, 1],
        c=final_labels, cmap="viridis", s=50
    )
    plt.xlabel("PCA 1")
    plt.ylabel("PCA 2")
    plt.title(f"Final DBSCAN (eps={final_eps}, min_pts={final_min_pts})")
    plt.grid(True)
    plt.savefig("Assignment08/final_dbscan.png")
    plt.show()

    n_clusters = len(set(final_labels)) - (1 if -1 in final_labels else 0)
    n_noise = list(final_labels).count(-1)
    print(f"\nFinal: Clusters={n_clusters}, Noise={n_noise}")
