import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.cluster.hierarchy import dendrogram

os.makedirs('Assignment08/plots', exist_ok=True)
os.makedirs('Assignment08/output', exist_ok=True)

# 2(a) Read dataset
data_path = 'Assignment08/Mall_Customers.csv'
df = pd.read_csv(data_path)

print("Dataset Loaded Successfully:")
print(f"Total Customers: {df.shape[0]}")

X = df[['Annual Income (k$)', 'Spending Score (1-100)']].values

# Custom Hierarchical Clustering Implementation
def custom_hierarchical(X, method='single'):
    n = len(X)
    clusters = {i: [i] for i in range(n)}
    active = list(range(n))
    centroids = {i: X[i].astype(float) for i in range(n)}

    dist_matrix = np.linalg.norm(X[:, None, :] - X[None, :, :], axis=-1)
    Z = []
    next_id = n

    D = np.full((2 * n, 2 * n), np.inf)
    D[:n, :n] = dist_matrix
    np.fill_diagonal(D, np.inf)

    for step in range(n - 1):
        act = np.array(active)
        sub_D = D[np.ix_(act, act)]
        min_idx = np.argmin(sub_D)
        i_sub, j_sub = np.unravel_index(min_idx, sub_D.shape)

        c1 = act[i_sub]
        c2 = act[j_sub]
        if c1 > c2:
            c1, c2 = c2, c1

        min_dist = D[c1, c2]
        new_pts = clusters[c1] + clusters[c2]
        clusters[next_id] = new_pts
        Z.append([float(c1), float(c2), float(min_dist), float(len(new_pts))])

        if method == 'single':
            for c in active:
                if c != c1 and c != c2:
                    d = min(D[c1, c], D[c2, c])
                    D[next_id, c] = d
                    D[c, next_id] = d
        elif method == 'complete':
            for c in active:
                if c != c1 and c != c2:
                    d = max(D[c1, c], D[c2, c])
                    D[next_id, c] = d
                    D[c, next_id] = d
        elif method == 'centroid':
            c_new = np.mean(X[new_pts], axis=0)
            centroids[next_id] = c_new
            for c in active:
                if c != c1 and c != c2:
                    d = np.linalg.norm(c_new - centroids[c])
                    D[next_id, c] = d
                    D[c, next_id] = d

        active.remove(c1)
        active.remove(c2)
        active.append(next_id)
        next_id += 1

    return np.array(Z)

# Extract cluster labels for k clusters
def get_cluster_labels(Z, n_samples, n_clusters):
    clusters = {i: [i] for i in range(n_samples)}
    next_id = n_samples
    n_merges = n_samples - n_clusters

    for step in range(n_merges):
        c1 = int(Z[step, 0])
        c2 = int(Z[step, 1])
        clusters[next_id] = clusters[c1] + clusters[c2]
        del clusters[c1]
        del clusters[c2]
        next_id += 1

    labels = np.zeros(n_samples, dtype=int)
    for cluster_label, (cid, members) in enumerate(clusters.items()):
        for idx in members:
            labels[idx] = cluster_label

    return labels

# Custom Silhouette Score calculation
def calculate_silhouette(X, labels):
    unique_clusters = np.unique(labels)
    if len(unique_clusters) < 2:
        return -1.0

    n = len(X)
    D = np.linalg.norm(X[:, None, :] - X[None, :, :], axis=-1)
    scores = []

    for i in range(n):
        ci = labels[i]
        same_cluster_idx = np.where(labels == ci)[0]

        if len(same_cluster_idx) <= 1:
            a_i = 0.0
        else:
            a_i = np.sum(D[i, same_cluster_idx]) / (len(same_cluster_idx) - 1)

        b_i = np.inf
        for other_c in unique_clusters:
            if other_c == ci:
                continue
            other_cluster_idx = np.where(labels == other_c)[0]
            dist_other = np.mean(D[i, other_cluster_idx])
            if dist_other < b_i:
                b_i = dist_other

        denom = max(a_i, b_i)
        if denom == 0:
            scores.append(0.0)
        else:
            scores.append((b_i - a_i) / denom)

    return float(np.mean(scores))

# Run for Single, Complete, Centroid linkage
strategies = ['single', 'complete', 'centroid']
target_k = 5
results = {}

print("\n--- 2(a) Hierarchical Clustering Execution ---")
for strat in strategies:
    print(f"Running {strat.capitalize()} Linkage...")
    Z = custom_hierarchical(X, method=strat)
    labels = get_cluster_labels(Z, len(X), target_k)
    sil = calculate_silhouette(X, labels)
    counts = np.bincount(labels)

    results[strat] = {
        'Z': Z,
        'labels': labels,
        'silhouette': sil,
        'counts': counts
    }
    print(f"  {strat.capitalize()} Linkage (k={target_k}) -> Silhouette: {sil:.4f}, Sizes: {counts}")

# 2(b) Visualize Dendrograms
plt.figure(figsize=(18, 5))

for idx, strat in enumerate(strategies):
    plt.subplot(1, 3, idx + 1)
    dendrogram(results[strat]['Z'], truncate_mode='lastp', p=25, show_leaf_counts=True)
    plt.title(f'{strat.capitalize()} Linkage Dendrogram')
    plt.xlabel('Cluster / Sample Index')
    plt.ylabel('Distance')
    plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('Assignment08/plots/hierarchical_dendrograms.png')
plt.close()

# Visualize Final Clusters
plt.figure(figsize=(18, 5))
colors = plt.cm.tab10(np.linspace(0, 1, target_k))

for idx, strat in enumerate(strategies):
    plt.subplot(1, 3, idx + 1)
    labels = results[strat]['labels']
    for k_val in range(target_k):
        pts = X[labels == k_val]
        plt.scatter(pts[:, 0], pts[:, 1], color=colors[k_val], label=f'Cluster {k_val}', s=45)

    plt.title(f'{strat.capitalize()} Linkage (k={target_k})\nSilhouette: {results[strat]["silhouette"]:.4f}')
    plt.xlabel('Annual Income (k$)')
    plt.ylabel('Spending Score (1-100)')
    plt.legend(loc='best', fontsize=8)
    plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('Assignment08/plots/hierarchical_clusters_comparison.png')
plt.close()

# Result Analysis
single_counts = [int(c) for c in results['single']['counts']]
complete_counts = [int(c) for c in results['complete']['counts']]
centroid_counts = [int(c) for c in results['centroid']['counts']]

analysis_text = f"""
======================================================================
RESULT ANALYSIS FOR QUESTION 2 (HIERARCHICAL CLUSTERING STRATEGIES)
======================================================================
Target Clusters: {target_k}

1. Single Linkage:
   - Silhouette Score: {results['single']['silhouette']:.4f}
   - Cluster Size Distribution: {single_counts}
   - Analysis: Single linkage measures the minimum pairwise distance between clusters. Consequently, it is vulnerable to the 'chaining effect' where a chain of closely spaced points bridges distant groups. As observed, one dominant cluster absorbs {max(single_counts)} out of {len(X)} customers, while the remaining clusters contain isolated singletons. It performs poorly for market segmentation.

2. Complete Linkage:
   - Silhouette Score: {results['complete']['silhouette']:.4f}
   - Cluster Size Distribution: {complete_counts}
   - Analysis: Complete linkage measures the maximum pairwise distance between clusters. This prevents chaining and forces clusters to remain compact and spherical. The cluster sizes are well balanced ({complete_counts}), neatly identifying standard customer segments:
     * High Income, High Spending (Prime Target)
     * High Income, Low Spending (Careful Spenders)
     * Low Income, High Spending (Careless Spenders)
     * Low Income, Low Spending (Sensible Spenders)
     * Moderate Income, Moderate Spending (Average Customers)
   - It achieves the best silhouette score ({results['complete']['silhouette']:.4f}).

3. Centroid Linkage:
   - Silhouette Score: {results['centroid']['silhouette']:.4f}
   - Cluster Size Distribution: {centroid_counts}
   - Analysis: Centroid linkage computes distances between the geometric means of clusters. It provides a compromise between single and complete linkage, forming reasonable clusters ({centroid_counts}), but can suffer from non-monotonic distance merges (inversions) in dendrograms. Complete linkage remains the most robust strategy for this dataset.
======================================================================
"""
print(analysis_text)

with open('Assignment08/output/q2_analysis.txt', 'w') as f:
    f.write(analysis_text)
