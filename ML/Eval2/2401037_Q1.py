import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Create target directories
os.makedirs('./Eval2/dataset', exist_ok=True)
os.makedirs('./Eval2/plots', exist_ok=True)
os.makedirs('./Eval2/output', exist_ok=True)

# Load dataset
df = pd.read_csv('./Eval2/dataset/clustering_dataset.csv')
print("Dataset Summary:")
print(f"Number of samples: {df.shape[0]}")
print(f"Number of features: {df.shape[1]}")
print(df.describe())

X = df.values

# Simple K-Means implementation without classes
def runKMeans(data, k, maxIter=300, tol=1e-4, seed=42):
    np.random.seed(seed)
    numSamples, numFeats = data.shape

    # Initial random centroids
    randIdxs = np.random.choice(numSamples, k, replace=False)
    centers = data[randIdxs].copy()
    labels = np.zeros(numSamples, dtype=int)

    for iterNum in range(maxIter):
        # Calculate distances to centroids
        distMatrix = np.linalg.norm(
            data[:, np.newaxis, :] - centers[np.newaxis, :, :], axis=2
        )
        labels = np.argmin(distMatrix, axis=1)

        # Update centroids
        newCenters = np.zeros((k, numFeats))
        for clusterIdx in range(k):
            pts = data[labels == clusterIdx]
            if len(pts) > 0:
                newCenters[clusterIdx] = np.mean(pts, axis=0)
            else:
                newCenters[clusterIdx] = data[np.random.choice(numSamples)]

        # Check convergence
        shift = np.linalg.norm(newCenters - centers)
        centers = newCenters
        if shift < tol:
            break

    # Calculate SSD / Inertia
    ssd = 0.0
    for clusterIdx in range(k):
        pts = data[labels == clusterIdx]
        if len(pts) > 0:
            ssd += np.sum((pts - centers[clusterIdx]) ** 2)

    return centers, labels, ssd


# Compute silhouette scores per sample
def getSilSamples(data, labels):
    numSamples = data.shape[0]
    uniqueLabels = np.unique(labels)

    if len(uniqueLabels) <= 1 or len(uniqueLabels) >= numSamples:
        return np.zeros(numSamples)

    # Pairwise distances
    diff = data[:, np.newaxis, :] - data[np.newaxis, :, :]
    distMatrix = np.sqrt(np.sum(diff**2, axis=2))
    silScores = np.zeros(numSamples)

    for i in range(numSamples):
        ownCluster = labels[i]
        ownMask = labels == ownCluster

        # Intra-cluster mean distance a
        aDist = (
            np.sum(distMatrix[i, ownMask]) / (np.sum(ownMask) - 1)
            if np.sum(ownMask) > 1
            else 0.0
        )

        # Inter-cluster min mean distance b
        bDist = np.inf
        for otherCluster in uniqueLabels:
            if otherCluster == ownCluster:
                continue
            otherMask = labels == otherCluster
            if np.sum(otherMask) > 0:
                avgDist = np.mean(distMatrix[i, otherMask])
                if avgDist < bDist:
                    bDist = avgDist

        maxDist = max(aDist, bDist)
        silScores[i] = (bDist - aDist) / maxDist if maxDist > 0 else 0.0

    return silScores


def getAvgSil(data, labels):
    return float(np.mean(getSilSamples(data, labels)))


# Evaluate K-Means range
def evalKRange(data, prefix="raw", seed=42):
    kValues = list(range(2, 11))
    metricsList = []

    for k in kValues:
        centers, labels, ssd = runKMeans(data, k, seed=seed)
        sil = getAvgSil(data, labels)
        metricsList.append({"K": k, "SSD": ssd, "Average_Silhouette": sil})

    metricsDf = pd.DataFrame(metricsList)
    metricsDf.to_csv(
        f"./Eval2/output/{prefix}_kmeans_metrics.csv", index=False
    )
    print(f"\n[{prefix.upper()}] K-Means Metrics:")
    print(metricsDf.to_string(index=False))

    # Plot Elbow (SSD)
    plt.figure(figsize=(8, 5))
    plt.plot(
        kValues, metricsDf["SSD"], marker="o", color="blue", linewidth=2
    )
    plt.xlabel("Number of Clusters (K)")
    plt.ylabel("Sum of Squared Distances (SSD)")
    plt.title(f"[{prefix.upper()}] Elbow Method: SSD vs K")
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"./Eval2/plots/{prefix}_elbow_plot.png")
    plt.close()

    # Plot Silhouette
    plt.figure(figsize=(8, 5))
    plt.plot(
        kValues,
        metricsDf["Average_Silhouette"],
        marker="s",
        color="green",
        linewidth=2,
    )
    plt.xlabel("Number of Clusters (K)")
    plt.ylabel("Average Silhouette Score")
    plt.title(f"[{prefix.upper()}] Silhouette Score vs K")
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"./Eval2/plots/{prefix}_silhouette_plot.png")
    plt.close()

    return metricsDf


# A & B: Run on raw data
rawMetricsDf = evalKRange(X, prefix="raw", seed=42)
bestIdx = rawMetricsDf["Average_Silhouette"].idxmax()
chosenK = int(rawMetricsDf.loc[bestIdx, "K"])
print(f"\nChosen K based on evaluation: {chosenK}")

# C: Visualization on raw data
rawCenters, rawLabels, rawSsd = runKMeans(X, chosenK, seed=42)
featIdx1, featIdx2 = 0, 1
feat1Name = df.columns[featIdx1]
feat2Name = df.columns[featIdx2]

totVar = np.sum(np.var(X, axis=0))
var1 = np.var(X[:, featIdx1])
var2 = np.var(X[:, featIdx2])
pctVar1 = (var1 / totVar) * 100
pctVar2 = (var2 / totVar) * 100

print("\nVariance Analysis for 2D Visualization:")
print(f"Total variance across all features: {totVar:.4f}")
print(f"{feat1Name} variance: {var1:.4f} ({pctVar1:.2f}% of total)")
print(f"{feat2Name} variance: {var2:.4f} ({pctVar2:.2f}% of total)")
print(
    f"Combined variance explained by chosen 2 features: {(pctVar1 + pctVar2):.2f}%"
)

plt.figure(figsize=(8, 6))
plt.scatter(
    X[:, featIdx1],
    X[:, featIdx2],
    c=rawLabels,
    cmap="tab10",
    alpha=0.7,
    edgecolors="k",
    s=45,
)
plt.scatter(
    rawCenters[:, featIdx1],
    rawCenters[:, featIdx2],
    c="red",
    marker="X",
    s=180,
    label="Centroids",
    edgecolors="black",
    linewidths=1.5,
)
plt.xlabel(f"{feat1Name} ({pctVar1:.2f}% variance)")
plt.ylabel(f"{feat2Name} ({pctVar2:.2f}% variance)")
plt.title(f"Cluster Visualization (K={chosenK}) on Raw Data")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("./Eval2/plots/raw_clusters_visualization.png")
plt.close()

# D: Report table for raw data
rawSilSamples = getSilSamples(X, rawLabels)
clusterDetails = []

for k in range(chosenK):
    mask = rawLabels == k
    pts = X[mask]
    size = int(np.sum(mask))
    clusterSsd = (
        float(np.sum((pts - rawCenters[k]) ** 2)) if size > 0 else 0.0
    )
    avgSil = float(np.mean(rawSilSamples[mask])) if size > 0 else 0.0

    info = {
        "Cluster": k,
        "Size": size,
        "Cluster_SSD": clusterSsd,
        "Avg_Silhouette": avgSil,
    }
    for colIdx, colName in enumerate(df.columns):
        info[f"Centroid_{colName}"] = rawCenters[k, colIdx]
    clusterDetails.append(info)

clusterDetailsDf = pd.DataFrame(clusterDetails)
clusterDetailsDf.to_csv(
    f"./Eval2/output/raw_final_clustering_k{chosenK}.csv", index=False
)

print(f"\nFinal Clustering Summary Table (Raw Data, K={chosenK}):")
print(clusterDetailsDf.to_string(index=False))
print(f"Total SSD : {rawSsd:.4f}")
print(f"Overall Average Silhouette Score: {np.mean(rawSilSamples):.4f}")

# E: Scaled Data Evaluation
xMean = np.mean(X, axis=0)
xStd = np.std(X, axis=0)
xStd[xStd == 0] = 1.0
xScaled = (X - xMean) / xStd

scaledMetricsDf = evalKRange(xScaled, prefix="scaled", seed=42)
scaledBestIdx = scaledMetricsDf["Average_Silhouette"].idxmax()
scaledChosenK = int(scaledMetricsDf.loc[scaledBestIdx, "K"])

scaledCenters, scaledLabels, scaledSsd = runKMeans(
    xScaled, scaledChosenK, seed=42
)

totVarScaled = np.sum(np.var(xScaled, axis=0))
varScaled1 = np.var(xScaled[:, featIdx1])
varScaled2 = np.var(xScaled[:, featIdx2])
pctVarScaled1 = (varScaled1 / totVarScaled) * 100
pctVarScaled2 = (varScaled2 / totVarScaled) * 100

plt.figure(figsize=(8, 6))
plt.scatter(
    xScaled[:, featIdx1],
    xScaled[:, featIdx2],
    c=scaledLabels,
    cmap="tab10",
    alpha=0.7,
    edgecolors="k",
    s=45,
)
plt.scatter(
    scaledCenters[:, featIdx1],
    scaledCenters[:, featIdx2],
    c="red",
    marker="X",
    s=180,
    label="Centroids",
    edgecolors="black",
    linewidths=1.5,
)
plt.xlabel(f"{feat1Name} (Scaled, {pctVarScaled1:.2f}% variance)")
plt.ylabel(f"{feat2Name} (Scaled, {pctVarScaled2:.2f}% variance)")
plt.title(f"Cluster Visualization (K={scaledChosenK}) on Scaled Data")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("./Eval2/plots/scaled_clusters_visualization.png")
plt.close()

scaledSilSamples = getSilSamples(xScaled, scaledLabels)
scaledDetails = []

for k in range(scaledChosenK):
    mask = scaledLabels == k
    pts = xScaled[mask]
    size = int(np.sum(mask))
    cSSD = float(np.sum((pts - scaledCenters[k]) ** 2)) if size > 0 else 0.0
    aSil = float(np.mean(scaledSilSamples[mask])) if size > 0 else 0.0

    info = {
        "Cluster": k,
        "Size": size,
        "Cluster_SSD": cSSD,
        "Avg_Silhouette": aSil,
    }
    for colIdx, colName in enumerate(df.columns):
        info[f"Centroid_{colName}"] = scaledCenters[k, colIdx]
    scaledDetails.append(info)

scaledDetailsDf = pd.DataFrame(scaledDetails)
scaledDetailsDf.to_csv(
    f"./Eval2/output/scaled_final_clustering_k{scaledChosenK}.csv",
    index=False,
)

print(f"\nFinal Clustering Summary Table (Scaled Data, K={scaledChosenK}):")
print(scaledDetailsDf.to_string(index=False))
print(f"Scaled Total SSD : {scaledSsd:.4f}")
print(f"Scaled Overall Average Silhouette Score: {np.mean(scaledSilSamples):.4f}")

# Side-by-side comparison plots
fig, axs = plt.subplots(1, 2, figsize=(14, 5))
axs[0].plot(
    rawMetricsDf["K"],
    rawMetricsDf["SSD"],
    marker="o",
    label="Raw Data",
    color="blue",
)
axs[0].plot(
    scaledMetricsDf["K"],
    scaledMetricsDf["SSD"],
    marker="s",
    label="Scaled Data",
    color="purple",
)
axs[0].set_xlabel("Number of Clusters (K)")
axs[0].set_ylabel("SSD")
axs[0].set_title("Elbow Comparison: Raw vs Scaled")
axs[0].legend()
axs[0].grid(True)

axs[1].plot(
    rawMetricsDf["K"],
    rawMetricsDf["Average_Silhouette"],
    marker="o",
    label="Raw Data",
    color="green",
)
axs[1].plot(
    scaledMetricsDf["K"],
    scaledMetricsDf["Average_Silhouette"],
    marker="s",
    label="Scaled Data",
    color="orange",
)
axs[1].set_xlabel("Number of Clusters (K)")
axs[1].set_ylabel("Average Silhouette Score")
axs[1].set_title("Silhouette Score Comparison: Raw vs Scaled")
axs[1].legend()
axs[1].grid(True)

plt.tight_layout()
plt.savefig("./Eval2/plots/raw_vs_scaled_comparison_plots.png")
plt.close()

compDf = pd.DataFrame(
    {
        "K": rawMetricsDf["K"],
        "Raw_SSD": rawMetricsDf["SSD"],
        "Scaled_SSD": scaledMetricsDf["SSD"],
        "Raw_Silhouette": rawMetricsDf["Average_Silhouette"],
        "Scaled_Silhouette": scaledMetricsDf["Average_Silhouette"],
    }
)
compDf.to_csv("./Eval2/output/raw_vs_scaled_comparison.csv", index=False)
print("\nRaw vs Scaled Metrics Comparison:")
print(compDf.to_string(index=False))

# F: Sensitivity Analysis
seedList = [0, 10, 42, 100, 150]
sensList = []

for s in seedList:
    c, l, sSsd = runKMeans(X, chosenK, seed=s)
    sSil = getAvgSil(X, l)
    sensList.append({"Random_State": s, "SSD": sSsd, "Average_Silhouette": sSil})

sensDf = pd.DataFrame(sensList)
sensDf.to_csv("./Eval2/output/sensitivity_analysis.csv", index=False)
print("\nSensitivity Analysis across 5 random initializations:")
print(sensDf.to_string(index=False))
print(
    f"SSD Range: [{sensDf['SSD'].min():.4f}, {sensDf['SSD'].max():.4f}] (Std: {sensDf['SSD'].std():.4f})"
)
print(
    f"Silhouette Range: [{sensDf['Average_Silhouette'].min():.4f}, {sensDf['Average_Silhouette'].max():.4f}] (Std: {sensDf['Average_Silhouette'].std():.4f})"
)