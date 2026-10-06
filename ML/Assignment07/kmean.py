import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans
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
# Remove empty rows if present
df = df.dropna()

print("Dataset:")
print(df.head())

print("\nDataset shape:", df.shape)


# 2. Remove class label
# We do NOT use the class column for clustering
X = df.iloc[:, :-1].values

print("\nFeatures used for clustering:")
print(df.iloc[:, :-1].head())


# 3. Standardize the features
# Standardization makes all features comparable
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


# 4. Custom K-Means implementation
def euclidean_distance(point1, point2):
    return np.sqrt(np.sum((point1 - point2) ** 2))


def custom_kmeans(X, k, max_iterations=100):

    # Select k random points as initial centroids
    random_indices = np.random.choice(len(X), k, replace=False)
    centroids = X[random_indices]

    for iteration in range(max_iterations):

        clusters = []

        # Assign every point to the nearest centroid
        for point in X:

            distances = []

            for centroid in centroids:
                distances.append(euclidean_distance(point, centroid))

            cluster = np.argmin(distances)
            clusters.append(cluster)

        clusters = np.array(clusters)

        # Calculate new centroids
        new_centroids = []

        for i in range(k):

            points = X[clusters == i]

            # Avoid empty cluster
            if len(points) == 0:
                new_centroids.append(centroids[i])
            else:
                new_centroids.append(np.mean(points, axis=0))

        new_centroids = np.array(new_centroids)

        # Stop if centroids do not change
        if np.allclose(centroids, new_centroids):
            break

        centroids = new_centroids

    return clusters, centroids


# ---------------------------------------------------------
# 5. Calculate WCSS for custom K-Means
# ---------------------------------------------------------

def calculate_wcss(X, clusters, centroids):

    wcss = 0

    for i in range(len(centroids)):

        points = X[clusters == i]

        for point in points:
            distance = euclidean_distance(point, centroids[i])
            wcss += distance ** 2

    return wcss


# ---------------------------------------------------------
# 6. Run custom K-Means for K = 2 to 8
# ---------------------------------------------------------

k_values = range(2, 9)

custom_wcss = []
custom_silhouette = []
custom_clusters = {}

np.random.seed(42)

for k in k_values:

    clusters, centroids = custom_kmeans(X_scaled, k)

    wcss = calculate_wcss(X_scaled, clusters, centroids)

    score = silhouette_score(X_scaled, clusters)

    custom_wcss.append(wcss)
    custom_silhouette.append(score)

    custom_clusters[k] = clusters

    print("\nCustom K-Means")
    print("K =", k)
    print("WCSS =", round(wcss, 4))
    print("Silhouette Score =", round(score, 4))


# ---------------------------------------------------------
# 7. Elbow graph for custom K-Means
# ---------------------------------------------------------

plt.figure(figsize=(8, 5))

plt.plot(k_values, custom_wcss, marker="o")

plt.xlabel("Number of Clusters (K)")
plt.ylabel("WCSS")
plt.title("Elbow Method - Custom K-Means")

plt.xticks(list(k_values))
plt.grid(True)

plt.show()


# ---------------------------------------------------------
# 8. Silhouette graph for custom K-Means
# ---------------------------------------------------------

plt.figure(figsize=(8, 5))

plt.plot(k_values, custom_silhouette, marker="o")

plt.xlabel("Number of Clusters (K)")
plt.ylabel("Silhouette Score")
plt.title("Silhouette Score - Custom K-Means")

plt.xticks(list(k_values))
plt.grid(True)

plt.show()


# ---------------------------------------------------------
# 9. PCA for visualizing clusters
# ---------------------------------------------------------

# Convert 4 features into 2 dimensions for visualization
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)


# ---------------------------------------------------------
# 10. Visualize custom K-Means clusters
# ---------------------------------------------------------

fig, axes = plt.subplots(2, 4, figsize=(16, 8))

for index, k in enumerate(k_values):

    row = index // 4
    col = index % 4

    axes[row, col].scatter(
        X_pca[:, 0],
        X_pca[:, 1],
        c=custom_clusters[k],
        cmap="viridis",
        s=40
    )

    axes[row, col].set_title(
        "Custom K-Means, K = " + str(k)
    )

    axes[row, col].set_xlabel("PCA 1")
    axes[row, col].set_ylabel("PCA 2")

# Hide unused subplot
axes[1, 3].axis("off")

plt.tight_layout()
plt.show()


# ---------------------------------------------------------
# 11. K-Means using sklearn
# ---------------------------------------------------------

library_wcss = []
library_silhouette = []
library_clusters = {}

for k in k_values:

    model = KMeans(
        n_clusters=k,
        random_state=42,
        n_init=10
    )

    clusters = model.fit_predict(X_scaled)

    wcss = model.inertia_

    score = silhouette_score(X_scaled, clusters)

    library_wcss.append(wcss)
    library_silhouette.append(score)

    library_clusters[k] = clusters

    print("\nSklearn K-Means")
    print("K =", k)
    print("WCSS =", round(wcss, 4))
    print("Silhouette Score =", round(score, 4))


# ---------------------------------------------------------
# 12. Compare WCSS
# ---------------------------------------------------------

plt.figure(figsize=(8, 5))

plt.plot(
    k_values,
    custom_wcss,
    marker="o",
    label="Custom K-Means"
)

plt.plot(
    k_values,
    library_wcss,
    marker="s",
    label="Sklearn K-Means"
)

plt.xlabel("Number of Clusters (K)")
plt.ylabel("WCSS")
plt.title("Elbow Method Comparison")

plt.xticks(list(k_values))
plt.legend()
plt.grid(True)

plt.show()


# ---------------------------------------------------------
# 13. Compare Silhouette Scores
# ---------------------------------------------------------

plt.figure(figsize=(8, 5))

plt.plot(
    k_values,
    custom_silhouette,
    marker="o",
    label="Custom K-Means"
)

plt.plot(
    k_values,
    library_silhouette,
    marker="s",
    label="Sklearn K-Means"
)

plt.xlabel("Number of Clusters (K)")
plt.ylabel("Silhouette Score")
plt.title("Silhouette Score Comparison")

plt.xticks(list(k_values))
plt.legend()
plt.grid(True)

plt.show()


# ---------------------------------------------------------
# 14. Display final results in a table
# ---------------------------------------------------------

results = pd.DataFrame({
    "K": list(k_values),

    "Custom WCSS": custom_wcss,
    "Custom Silhouette": custom_silhouette,

    "Sklearn WCSS": library_wcss,
    "Sklearn Silhouette": library_silhouette
})

print("\nFinal Results:")
print(results.round(4))


# ---------------------------------------------------------
# 15. Find K having maximum silhouette score
# ---------------------------------------------------------

best_k_custom = list(k_values)[
    np.argmax(custom_silhouette)
]

best_k_library = list(k_values)[
    np.argmax(library_silhouette)
]

print("\nBest K according to Custom K-Means Silhouette Score:",
      best_k_custom)

print("Best K according to Sklearn K-Means Silhouette Score:",
      best_k_library)


# ---------------------------------------------------------
# 16. Final clustering using selected K
# ---------------------------------------------------------

final_k = best_k_library

final_model = KMeans(
    n_clusters=final_k,
    random_state=42,
    n_init=10
)

final_clusters = final_model.fit_predict(X_scaled)

plt.figure(figsize=(8, 6))

plt.scatter(
    X_pca[:, 0],
    X_pca[:, 1],
    c=final_clusters,
    cmap="viridis",
    s=50
)

plt.xlabel("PCA 1")
plt.ylabel("PCA 2")

plt.title(
    "Final K-Means Clustering (K = " + str(final_k) + ")"
)

plt.grid(True)

plt.show()