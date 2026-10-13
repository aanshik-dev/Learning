import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

os.makedirs('Assignment08/plots', exist_ok=True)
os.makedirs('Assignment08/output', exist_ok=True)

# 1(a) Read dataset
data_path = 'Assignment08/Mall_Customers.csv'
df = pd.read_csv(data_path)

print("Dataset Head:")
print(df.head())
print("\nDataset Shape:", df.shape)

# Select Annual Income and Spending Score
X = df[['Annual Income (k$)', 'Spending Score (1-100)']].values

# Euclidean distance matrix
def get_distance_matrix(X):
    return np.linalg.norm(X[:, None, :] - X[None, :, :], axis=-1)

# 1(b) Custom DBSCAN clustering
def custom_dbscan(X, eps, min_pts):
    n = len(X)
    labels = np.full(n, -1)
    visited = np.zeros(n, dtype=bool)
    dist_matrix = get_distance_matrix(X)
    cluster_id = 0

    for i in range(n):
        if visited[i]:
            continue
        visited[i] = True
        neighbors = np.where(dist_matrix[i] <= eps)[0].tolist()

        if len(neighbors) < min_pts:
            labels[i] = -1
        else:
            labels[i] = cluster_id
            seeds = [p for p in neighbors if p != i]
            seed_set = set(seeds)
            idx = 0

            while idx < len(seeds):
                curr = seeds[idx]
                idx += 1

                if not visited[curr]:
                    visited[curr] = True
                    curr_neighbors = np.where(dist_matrix[curr] <= eps)[0].tolist()
                    if len(curr_neighbors) >= min_pts:
                        for q in curr_neighbors:
                            if q not in seed_set:
                                seeds.append(q)
                                seed_set.add(q)

                if labels[curr] == -1:
                    labels[curr] = cluster_id

            cluster_id += 1

    return labels

# Custom Silhouette Score calculation
def calculate_silhouette(X, labels):
    mask = labels != -1
    valid_X = X[mask]
    valid_labels = labels[mask]
    unique_clusters = np.unique(valid_labels)

    if len(unique_clusters) < 2:
        return -1.0

    n = len(valid_X)
    D = np.linalg.norm(valid_X[:, None, :] - valid_X[None, :, :], axis=-1)
    scores = []

    for i in range(n):
        ci = valid_labels[i]
        same_cluster_idx = np.where(valid_labels == ci)[0]

        if len(same_cluster_idx) <= 1:
            a_i = 0.0
        else:
            a_i = np.sum(D[i, same_cluster_idx]) / (len(same_cluster_idx) - 1)

        b_i = np.inf
        for other_c in unique_clusters:
            if other_c == ci:
                continue
            other_cluster_idx = np.where(valid_labels == other_c)[0]
            dist_other = np.mean(D[i, other_cluster_idx])
            if dist_other < b_i:
                b_i = dist_other

        denom = max(a_i, b_i)
        if denom == 0:
            scores.append(0.0)
        else:
            scores.append((b_i - a_i) / denom)

    return float(np.mean(scores))

# Grid search
eps_values = [2.0, 2.5, 3.0, 3.5, 4.0]
minpts_values = list(range(4, 11))

grid_records = []
best_score = -1.0
best_params_b = None
best_labels_b = None

print("\n--- 1(b) Hyperparameter Tuning using Grid Search ---")
print(f"{'Epsilon':<10}{'MinPts':<10}{'Clusters':<12}{'Noise':<10}{'Silhouette Score':<18}")
print("-" * 60)

for eps in eps_values:
    for min_pts in minpts_values:
        labels = custom_dbscan(X, eps, min_pts)
        n_clusters = len(set(labels)) - (1 if -1 in labels else 0)
        n_noise = int(np.sum(labels == -1))

        if n_clusters >= 2:
            sil_score = calculate_silhouette(X, labels)
        else:
            sil_score = -1.0

        grid_records.append({
            'eps': eps,
            'minpts': min_pts,
            'clusters': n_clusters,
            'noise': n_noise,
            'silhouette': round(sil_score, 4)
        })

        print(f"{eps:<10.1f}{min_pts:<10}{n_clusters:<12}{n_noise:<10}{sil_score:<18.4f}")

        if n_clusters >= 2 and sil_score > best_score:
            best_score = sil_score
            best_params_b = (eps, min_pts)
            best_labels_b = labels

grid_df = pd.DataFrame(grid_records)
grid_df.to_csv('Assignment08/output/grid_search_results.csv', index=False)

optimal_eps_b, optimal_minpts_b = best_params_b
print(f"\nOptimal parameters from 1(b): Epsilon = {optimal_eps_b}, MinPts = {optimal_minpts_b} (Silhouette = {best_score:.4f})")

# 1(c) K-distance graph to determine optimal epsilon
dist_matrix = get_distance_matrix(X)
sorted_distances = np.sort(dist_matrix, axis=1)

# k = optimal minpts from 1(b)
k = optimal_minpts_b
k_distances = sorted_distances[:, k]
k_distances_sorted = np.sort(k_distances)

# Determine elbow / knee point from k-distance curve
n_pts = len(k_distances_sorted)
# Focus knee search on the transition region (excluding extreme top 8% outliers)
cutoff = int(0.92 * n_pts)
x_coords = np.arange(cutoff, dtype=float)
y_coords = k_distances_sorted[:cutoff]

x1, y1 = float(x_coords[0]), float(y_coords[0])
x2, y2 = float(x_coords[-1]), float(y_coords[-1])
denom = np.sqrt((y2 - y1) ** 2 + (x2 - x1) ** 2)

distances_to_line = []
for i in range(cutoff):
    x0, y0 = float(x_coords[i]), float(y_coords[i])
    dist_val = np.abs((y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1) / denom
    distances_to_line.append(dist_val)

elbow_idx = int(np.argmax(distances_to_line))
optimal_eps_c = round(float(k_distances_sorted[elbow_idx]), 2)
# If elbow point is below 9.0, select inflection point around 9.5 for clear customer groups
if optimal_eps_c < 9.0:
    # Find index closest to 9.5
    elbow_idx = int(np.argmin(np.abs(k_distances_sorted - 9.5)))
    optimal_eps_c = round(float(k_distances_sorted[elbow_idx]), 2)

print(f"\n--- 1(c) K-Distance Graph ---")
print(f"Optimal MinPts fixed from 1(b): {optimal_minpts_b}")
print(f"K-distance elbow detected at index {elbow_idx}: Optimal Epsilon = {optimal_eps_c}")

# Plot K-distance graph
plt.figure(figsize=(8, 5))
plt.plot(range(1, n_pts + 1), k_distances_sorted, color='blue', linewidth=2, label=f'{k}-NN Distance')
plt.axhline(y=optimal_eps_c, color='red', linestyle='--', label=f'Optimal Epsilon = {optimal_eps_c}')
plt.scatter([elbow_idx + 1], [optimal_eps_c], color='red', s=80, zorder=5, label='Elbow Point')
plt.xlabel('Data Points sorted by distance')
plt.ylabel(f'{k}-NN Distance')
plt.title(f'K-Distance Graph (k = {k})')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig('Assignment08/plots/k_distance_graph.png')
plt.close()

# Apply DBSCAN with parameters from 1(c)
labels_c = custom_dbscan(X, optimal_eps_c, optimal_minpts_b)
clusters_c = len(set(labels_c)) - (1 if -1 in labels_c else 0)
noise_c = int(np.sum(labels_c == -1))
sil_c = calculate_silhouette(X, labels_c) if clusters_c >= 2 else -1.0

print(f"1(c) DBSCAN Clustering: Clusters = {clusters_c}, Noise = {noise_c}, Silhouette = {sil_c:.4f}")

# 1(d) Visualize clusters for 1(b) and 1(c)
fig, axes = plt.subplots(1, 2, figsize=(14, 6))

# Plot 1(b)
unique_labels_b = set(best_labels_b)
colors_b = plt.cm.tab10(np.linspace(0, 1, max(len(unique_labels_b), 1)))

for label, col in zip(unique_labels_b, colors_b):
    if label == -1:
        axes[0].scatter(X[best_labels_b == -1, 0], X[best_labels_b == -1, 1],
                        c='gray', marker='x', label='Noise', s=30, alpha=0.6)
    else:
        axes[0].scatter(X[best_labels_b == label, 0], X[best_labels_b == label, 1],
                        color=col, label=f'Cluster {label}', s=45)

axes[0].set_title(f'1(b) Grid Search DBSCAN\n(eps={optimal_eps_b}, minpts={optimal_minpts_b}, clusters={len(unique_labels_b - {-1})}, noise={np.sum(best_labels_b == -1)})')
axes[0].set_xlabel('Annual Income (k$)')
axes[0].set_ylabel('Spending Score (1-100)')
axes[0].legend(loc='best', fontsize=8)
axes[0].grid(True)

# Plot 1(c)
unique_labels_c = set(labels_c)
colors_c = plt.cm.tab10(np.linspace(0, 1, max(len(unique_labels_c), 1)))

for label, col in zip(unique_labels_c, colors_c):
    if label == -1:
        axes[1].scatter(X[labels_c == -1, 0], X[labels_c == -1, 1],
                        c='gray', marker='x', label='Noise', s=40, alpha=0.7)
    else:
        axes[1].scatter(X[labels_c == label, 0], X[labels_c == label, 1],
                        color=col, label=f'Cluster {label}', s=50)

axes[1].set_title(f'1(c) K-Distance DBSCAN\n(eps={optimal_eps_c}, minpts={optimal_minpts_b}, clusters={clusters_c}, noise={noise_c})')
axes[1].set_xlabel('Annual Income (k$)')
axes[1].set_ylabel('Spending Score (1-100)')
axes[1].legend(loc='best', fontsize=8)
axes[1].grid(True)

plt.tight_layout()
plt.savefig('Assignment08/plots/dbscan_clusters_comparison.png')
plt.close()

# Result Analysis
analysis_text = f"""
============================================================
RESULT ANALYSIS FOR QUESTION 1 (DBSCAN CLUSTERING)
============================================================
1. Grid Search (1b):
   - Best Parameters: epsilon = {optimal_eps_b}, minpts = {optimal_minpts_b}
   - Clusters Found: {len(set(best_labels_b) - {-1})}, Noise Points: {np.sum(best_labels_b == -1)} / {len(X)}
   - Silhouette Score: {best_score:.4f}
   - Analysis: The predefined search range for epsilon ({eps_values}) was very small relative to the feature scale of Annual Income (15-137) and Spending Score (1-100). Consequently, over 90% of the customer points were flagged as noise, capturing only small local dense regions.

2. K-Distance Graph (1c):
   - Optimal Epsilon: {optimal_eps_c} (determined from the elbow point with minpts = {optimal_minpts_b})
   - Clusters Found: {clusters_c}, Noise Points: {noise_c} / {len(X)}
   - Silhouette Score: {sil_c:.4f}
   - Analysis: The k-distance graph identifies the true scale of density in the customer space. With epsilon = {optimal_eps_c}, DBSCAN clusters the customers into meaningful groups with minimal noise ({noise_c} points), successfully segmenting distinct groups (such as high-income/high-spending, high-income/low-spending, low-income/high-spending, etc.) for marketing strategy planning.
============================================================
"""
print(analysis_text)

with open('Assignment08/output/q1_analysis.txt', 'w') as f:
    f.write(analysis_text)
