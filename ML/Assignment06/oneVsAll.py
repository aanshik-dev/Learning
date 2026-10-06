import numpy as np
import pandas as pd

# Reading dataset
columns = [
    "SepalLengthCm",
    "SepalWidthCm",
    "PetalLengthCm",
    "PetalWidthCm",
    "Species"
]

df = pd.read_csv('./dataset_iris.csv', names=columns)
df = df.dropna(subset=columns)
print(df.describe())

# print("Dataset shape:", df.shape)
# print(df.head())



# class_names = [
#     "Iris-setosa",
#     "Iris-versicolor",
#     "Iris-virginica"
# ]

# class_to_number = {
#     "Iris-setosa": 0,
#     "Iris-versicolor": 1,
#     "Iris-virginica": 2
# }

# df["target"] = df["species"].map(class_to_number)

# X = df[
#     [
#         "sepal_length",
#         "sepal_width",
#         "petal_length",
#         "petal_width"
#     ]
# ].values.astype(float)

# y = df["target"].values.astype(int)


# def standardize_train_test(X_train, X_test):

#     mean = np.mean(X_train, axis=0)
#     std = np.std(X_train, axis=0)

#     std[std == 0] = 1

#     X_train_scaled = (X_train - mean) / std
#     X_test_scaled = (X_test - mean) / std

#     return X_train_scaled, X_test_scaled


# def sigmoid(z):

#     z = np.clip(z, -500, 500)

#     return 1 / (1 + np.exp(-z))


# # ============================================================
# # 5. BINARY LOGISTIC REGRESSION
# # ============================================================

# def train_binary_logistic(X, y, alpha, rho, epochs):

#     # Add bias
#     X_bias = np.c_[np.ones(X.shape[0]), X]

#     # Initialize parameters to zero
#     theta = np.zeros(X_bias.shape[1])

#     previous_error = float("inf")

#     for epoch in range(epochs):

#         # Hypothesis
#         z = X_bias @ theta
#         h = sigmoid(z)

#         # Avoid log(0)
#         h_safe = np.clip(h, 1e-15, 1 - 1e-15)

#         # Binary cross entropy
#         error = -np.mean(
#             y * np.log(h_safe)
#             + (1 - y) * np.log(1 - h_safe)
#         )

#         # Gradient
#         gradient = (X_bias.T @ (h - y)) / len(y)

#         # Batch gradient descent
#         theta = theta - alpha * gradient

#         # Stopping condition
#         if abs(previous_error - error) < rho:
#             break

#         previous_error = error

#     return theta


# # ============================================================
# # 6. ONE-VS-ALL TRAINING
# # ============================================================

# def train_ova(X, y, alpha, rho, epochs):

#     all_theta = []

#     number_of_classes = len(np.unique(y))

#     for current_class in range(number_of_classes):

#         # Current class = 1
#         # Other classes = 0

#         binary_y = (y == current_class).astype(int)

#         theta = train_binary_logistic(
#             X,
#             binary_y,
#             alpha,
#             rho,
#             epochs
#         )

#         all_theta.append(theta)

#     return np.array(all_theta)


# # ============================================================
# # 7. ONE-VS-ALL PREDICTION
# # ============================================================

# def predict_ova(X, all_theta):

#     X_bias = np.c_[np.ones(X.shape[0]), X]

#     probabilities = sigmoid(X_bias @ all_theta.T)

#     predictions = np.argmax(probabilities, axis=1)

#     return predictions, probabilities


# # ============================================================
# # 8. MANUAL K-FOLD SPLIT
# # ============================================================

# def create_k_folds(X, y, k=5, seed=42):

#     np.random.seed(seed)

#     indices = np.arange(len(X))

#     np.random.shuffle(indices)

#     fold_sizes = np.full(k, len(X) // k)

#     fold_sizes[:len(X) % k] += 1

#     folds = []

#     start = 0

#     for size in fold_sizes:

#         fold_indices = indices[start:start + size]

#         folds.append(fold_indices)

#         start += size

#     return folds


# # ============================================================
# # 9. TRAIN / VALIDATION SPLIT
# # ============================================================

# def validation_split(X, y, validation_percentage=0.10, seed=42):

#     np.random.seed(seed)

#     indices = np.arange(len(X))
#     np.random.shuffle(indices)

#     validation_size = int(
#         len(X) * validation_percentage
#     )

#     validation_indices = indices[:validation_size]
#     training_indices = indices[validation_size:]

#     return (
#         X[training_indices],
#         X[validation_indices],
#         y[training_indices],
#         y[validation_indices]
#     )


# # ============================================================
# # 10. CONFUSION MATRIX MANUALLY
# # ============================================================

# def confusion_matrix_manual(y_true, y_pred, number_of_classes=3):

#     matrix = np.zeros(
#         (number_of_classes, number_of_classes),
#         dtype=int
#     )

#     for actual, predicted in zip(y_true, y_pred):

#         matrix[actual][predicted] += 1

#     return matrix


# # ============================================================
# # 11. METRICS
# # ============================================================

# def calculate_metrics(cm):

#     number_of_classes = cm.shape[0]

#     total = np.sum(cm)

#     correct = np.trace(cm)

#     accuracy = correct / total

#     class_accuracy = []
#     precision = []
#     recall = []

#     for i in range(number_of_classes):

#         TP = cm[i][i]

#         FN = np.sum(cm[i, :]) - TP

#         FP = np.sum(cm[:, i]) - TP

#         TN = total - TP - FN - FP

#         class_total = TP + FN

#         if class_total != 0:
#             class_acc = TP / class_total
#         else:
#             class_acc = 0

#         if TP + FP != 0:
#             p = TP / (TP + FP)
#         else:
#             p = 0

#         if TP + FN != 0:
#             r = TP / (TP + FN)
#         else:
#             r = 0

#         class_accuracy.append(class_acc)
#         precision.append(p)
#         recall.append(r)

#     return {
#         "accuracy": accuracy,
#         "class_accuracy": class_accuracy,
#         "precision": precision,
#         "recall": recall
#     }


# # ============================================================
# # 12. HYPERPARAMETERS
# # ============================================================

# learning_rates = [0.0001, 0.1]
# rhos = [0.001, 0.01]
# epochs_list = [50, 100]

# hyperparameters = list(
#     product(
#         learning_rates,
#         rhos,
#         epochs_list
#     )
# )

# print("\nTotal hyperparameter combinations:",
#       len(hyperparameters))


# # ============================================================
# # 13. 5-FOLD CROSS VALIDATION
# # ============================================================

# folds = create_k_folds(X, y, k=5, seed=42)

# fold_results = []

# all_confusion_matrices = []

# for fold_number in range(5):

#     print("\n===================================")
#     print("FOLD", fold_number + 1)
#     print("===================================")

#     test_indices = folds[fold_number]

#     train_indices = np.concatenate(
#         [
#             folds[i]
#             for i in range(5)
#             if i != fold_number
#         ]
#     )

#     X_train_full = X[train_indices]
#     y_train_full = y[train_indices]

#     X_test = X[test_indices]
#     y_test = y[test_indices]

#     # 10% validation from training
#     (
#         X_train,
#         X_validation,
#         y_train,
#         y_validation
#     ) = validation_split(
#         X_train_full,
#         y_train_full,
#         validation_percentage=0.10,
#         seed=fold_number + 100
#     )

#     # Standardize using only actual training data
#     (
#         X_train_scaled,
#         X_validation_scaled
#     ) = standardize_train_test(
#         X_train,
#         X_validation
#     )

#     # Test is standardized using training statistics
#     mean = np.mean(X_train, axis=0)
#     std = np.std(X_train, axis=0)

#     std[std == 0] = 1

#     X_test_scaled = (X_test - mean) / std


#     # ============================================
#     # HYPERPARAMETER TUNING
#     # ============================================

#     best_validation_accuracy = -1
#     best_parameters = None

#     for alpha, rho, epochs in hyperparameters:

#         theta = train_ova(
#             X_train_scaled,
#             y_train,
#             alpha,
#             rho,
#             epochs
#         )

#         validation_prediction, _ = predict_ova(
#             X_validation_scaled,
#             theta
#         )

#         validation_accuracy = np.mean(
#             validation_prediction == y_validation
#         )

#         if validation_accuracy > best_validation_accuracy:

#             best_validation_accuracy = validation_accuracy

#             best_parameters = (
#                 alpha,
#                 rho,
#                 epochs
#             )

#     print(
#         "Best parameters:",
#         best_parameters
#     )

#     print(
#         "Validation accuracy:",
#         best_validation_accuracy
#     )


#     # ============================================
#     # FINAL TRAINING
#     # ============================================

#     # Train using the complete 90% training portion
#     # after selecting hyperparameters.

#     X_final_train, X_dummy = standardize_train_test(
#         X_train_full,
#         X_test
#     )

#     mean_final = np.mean(X_train_full, axis=0)
#     std_final = np.std(X_train_full, axis=0)

#     std_final[std_final == 0] = 1

#     X_final_test = (
#         X_test - mean_final
#     ) / std_final

#     alpha, rho, epochs = best_parameters

#     final_theta = train_ova(
#         X_final_train,
#         y_train_full,
#         alpha,
#         rho,
#         epochs
#     )

#     test_prediction, probabilities = predict_ova(
#         X_final_test,
#         final_theta
#     )


#     # ============================================
#     # CONFUSION MATRIX
#     # ============================================

#     cm = confusion_matrix_manual(
#         y_test,
#         test_prediction,
#         3
#     )

#     metrics = calculate_metrics(cm)

#     all_confusion_matrices.append(cm)

#     fold_results.append({
#         "Fold": fold_number + 1,
#         "Learning Rate": alpha,
#         "Rho": rho,
#         "Epochs": epochs,
#         "Validation Accuracy": best_validation_accuracy,
#         "Test Accuracy": metrics["accuracy"],
#         "Setosa Accuracy": metrics["class_accuracy"][0],
#         "Versicolor Accuracy": metrics["class_accuracy"][1],
#         "Virginica Accuracy": metrics["class_accuracy"][2],
#         "Setosa Precision": metrics["precision"][0],
#         "Versicolor Precision": metrics["precision"][1],
#         "Virginica Precision": metrics["precision"][2],
#         "Setosa Recall": metrics["recall"][0],
#         "Versicolor Recall": metrics["recall"][1],
#         "Virginica Recall": metrics["recall"][2]
#     })

#     print("\nConfusion Matrix:")
#     print(cm)

#     print(
#         "Test Accuracy:",
#         metrics["accuracy"]
#     )


# # ============================================================
# # 14. RESULTS DATAFRAME
# # ============================================================

# results_df = pd.DataFrame(fold_results)

# print("\n\nFOLD RESULTS")
# print(results_df)


# # ============================================================
# # 15. AVERAGE OF 5 FOLDS
# # ============================================================

# numeric_columns = [
#     "Validation Accuracy",
#     "Test Accuracy",
#     "Setosa Accuracy",
#     "Versicolor Accuracy",
#     "Virginica Accuracy",
#     "Setosa Precision",
#     "Versicolor Precision",
#     "Virginica Precision",
#     "Setosa Recall",
#     "Versicolor Recall",
#     "Virginica Recall"
# ]

# average_results = results_df[numeric_columns].mean()


# print("\nAVERAGE RESULTS")
# print(average_results)


# # ============================================================
# # 16. BEST FOLD
# # ============================================================

# best_fold_index = results_df[
#     "Test Accuracy"
# ].idxmax()

# best_fold = results_df.loc[
#     best_fold_index
# ]

# print("\nBEST FOLD")
# print(best_fold)


# # ============================================================
# # 17. VISUALIZE CONFUSION MATRICES
# # ============================================================

# for i, cm in enumerate(all_confusion_matrices):

#     plt.figure(figsize=(5, 4))

#     plt.imshow(cm)

#     plt.title(
#         "Confusion Matrix - Fold " + str(i + 1)
#     )

#     plt.xlabel("Predicted Class")
#     plt.ylabel("Actual Class")

#     plt.xticks(
#         [0, 1, 2],
#         ["Setosa", "Versicolor", "Virginica"]
#     )

#     plt.yticks(
#         [0, 1, 2],
#         ["Setosa", "Versicolor", "Virginica"]
#     )

#     for row in range(3):

#         for col in range(3):

#             plt.text(
#                 col,
#                 row,
#                 cm[row, col],
#                 ha="center",
#                 va="center"
#             )

#     plt.colorbar()

#     plt.tight_layout()

#     plt.savefig(
#         "confusion_matrix_fold_" +
#         str(i + 1) +
#         ".png"
#     )

#     plt.show()


# # ============================================================
# # 18. CREATE EXCEL REPORT
# # ============================================================

# output_file = "iris_logistic_regression_results.xlsx"

# with pd.ExcelWriter(
#     output_file,
#     engine="openpyxl"
# ) as writer:

#     # All folds
#     results_df.to_excel(
#         writer,
#         sheet_name="Fold Results",
#         index=False
#     )

#     # Average results
#     average_df = average_results.to_frame(
#         name="Average"
#     )

#     average_df.to_excel(
#         writer,
#         sheet_name="Average Results"
#     )

#     # Best fold
#     best_fold.to_frame(
#         name="Best Fold"
#     ).to_excel(
#         writer,
#         sheet_name="Best Fold"
#     )

#     # Confusion matrices
#     for i, cm in enumerate(
#         all_confusion_matrices
#     ):

#         cm_df = pd.DataFrame(
#             cm,
#             index=[
#                 "Actual Setosa",
#                 "Actual Versicolor",
#                 "Actual Virginica"
#             ],
#             columns=[
#                 "Predicted Setosa",
#                 "Predicted Versicolor",
#                 "Predicted Virginica"
#             ]
#         )

#         cm_df.to_excel(
#             writer,
#             sheet_name="CM Fold " + str(i + 1)
#         )


# print(
#     "\nExcel file created:",
#     output_file
# )