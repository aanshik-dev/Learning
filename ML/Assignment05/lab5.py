import numpy as np
import pandas as pd
import os
import matplotlib.pyplot as plt
from sklearn.linear_model import SGDRegressor
import warnings
warnings.filterwarnings('ignore')


# 1a - Create synthetic dataset of 100 patterns
np.random.seed(42)
n = 100

mileage = np.random.uniform(5000, 150000, n)
year_of_manufacture = np.random.randint(2005, 2025, n)
age = 2026 - year_of_manufacture

# price = w0 + w1*mileage + w2*age + noise
price = 500000 - 1.5 * mileage - 15000 * age + np.random.normal(0, 20000, n)

df = pd.DataFrame({
    'mileage': mileage,
    'age': age,
    'price': price
})

os.makedirs('Assignment05/dataset', exist_ok=True)
os.makedirs('Assignment05/output', exist_ok=True)
os.makedirs('Assignment05/plots', exist_ok=True)

df.to_csv('Assignment05/dataset/car_data.csv', index=False)
print("Synthetic dataset created:", df.shape)
print(df.head())


# 1b - Split into training:testing sets
df = df.sample(frac=1, random_state=42).reset_index(drop=True)

for x in range(20, 100, 20):
    y = 100 - x
    train_size = int(len(df) * x / 100)

    train = df.iloc[:train_size]
    test = df.iloc[train_size:]

    train.to_csv(f'Assignment05/dataset/set_{x}_train.csv', index=False)
    test.to_csv(f'Assignment05/dataset/set_{y}_test.csv', index=False)

    print(f'Split {x}:{y} -> Train: {len(train)}, Test: {len(test)}')


# 1c - Train multiple linear regression using Batch GD (without packages)
def batch_gd_multiple(X, Y, alpha=0.01, epochs=5000):
    m = len(X)
    # Add bias column
    X_b = np.c_[np.ones(m), X]
    w = np.zeros(X_b.shape[1])

    for _ in range(epochs):
        Y_pred = X_b @ w
        error = Y_pred - Y
        gradient = (X_b.T @ error) / m
        w = w - alpha * gradient

    return w


params_list = []

for x in range(20, 100, 20):
    y = 100 - x

    train = pd.read_csv(f'Assignment05/dataset/set_{x}_train.csv')
    X_train = train[['mileage', 'age']].values
    Y_train = train['price'].values

    # Normalize features for stable GD
    x_mean = np.mean(X_train, axis=0)
    x_std = np.std(X_train, axis=0)
    x_std[x_std == 0] = 1
    X_train_norm = (X_train - x_mean) / x_std

    w = batch_gd_multiple(X_train_norm, Y_train, alpha=0.01, epochs=5000)

    params_list.append({
        'Split': f'{x}:{y}',
        'w0': w[0],
        'w1': w[1],
        'w2': w[2],
        'x_mean_0': x_mean[0],
        'x_mean_1': x_mean[1],
        'x_std_0': x_std[0],
        'x_std_1': x_std[1]
    })

    with open(f'Assignment05/output/params_{x}_{y}.txt', 'w') as f:
        f.write(f'w0 = {w[0]}\n')
        f.write(f'w1 = {w[1]}\n')
        f.write(f'w2 = {w[2]}\n')

    print(f'Split {x}:{y} -> w0={w[0]:.2f}, w1={w[1]:.2f}, w2={w[2]:.2f}')

params_df = pd.DataFrame(params_list)
params_df.to_csv('Assignment05/output/all_params.csv', index=False)


# 1d - Visualize best-fit-line for different hypotheses
for idx, row in params_df.iterrows():
    split = row['Split']
    x_pct = int(split.split(':')[0])
    y_pct = int(split.split(':')[1])

    train = pd.read_csv(f'Assignment05/dataset/set_{x_pct}_train.csv')
    test = pd.read_csv(f'Assignment05/dataset/set_{y_pct}_test.csv')

    X_train = train[['mileage', 'age']].values
    Y_train = train['price'].values

    x_mean = np.array([row['x_mean_0'], row['x_mean_1']])
    x_std = np.array([row['x_std_0'], row['x_std_1']])
    X_train_norm = (X_train - x_mean) / x_std

    Y_pred_train = row['w0'] + X_train_norm @ np.array([row['w1'], row['w2']])

    # Plot predicted vs actual for mileage
    plt.figure(figsize=(8, 5))
    plt.scatter(train['mileage'], Y_train, c='blue', alpha=0.5, label='Actual')
    plt.scatter(train['mileage'], Y_pred_train, c='red', alpha=0.5, label='Predicted')
    plt.xlabel("Mileage")
    plt.ylabel("Price")
    plt.title(f"Split {split} - Predicted vs Actual")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f'Assignment05/plots/fit_{x_pct}_{y_pct}.png')
    plt.close()

print("Plots saved.")


# 1e - Calculate house price for testing patterns
predictions_list = []

for idx, row in params_df.iterrows():
    split = row['Split']
    x_pct = int(split.split(':')[0])
    y_pct = int(split.split(':')[1])

    test = pd.read_csv(f'Assignment05/dataset/set_{y_pct}_test.csv')
    X_test = test[['mileage', 'age']].values
    Y_test = test['price'].values

    x_mean = np.array([row['x_mean_0'], row['x_mean_1']])
    x_std = np.array([row['x_std_0'], row['x_std_1']])
    X_test_norm = (X_test - x_mean) / x_std

    Y_pred = row['w0'] + X_test_norm @ np.array([row['w1'], row['w2']])

    for i in range(len(X_test)):
        predictions_list.append({
            'Split': split,
            'Mileage': X_test[i][0],
            'Age': X_test[i][1],
            'Actual_Price': Y_test[i],
            'Predicted_Price': Y_pred[i]
        })

pred_df = pd.DataFrame(predictions_list)
pred_df.to_csv('Assignment05/output/predictions.csv', index=False)
print("Predictions saved.")


# 1f - Calculate MSE and R2 for different test splits
results = []

for idx, row in params_df.iterrows():
    split = row['Split']
    x_pct = int(split.split(':')[0])
    y_pct = int(split.split(':')[1])

    test = pd.read_csv(f'Assignment05/dataset/set_{y_pct}_test.csv')
    X_test = test[['mileage', 'age']].values
    Y_test = test['price'].values

    x_mean = np.array([row['x_mean_0'], row['x_mean_1']])
    x_std = np.array([row['x_std_0'], row['x_std_1']])
    X_test_norm = (X_test - x_mean) / x_std

    Y_pred = row['w0'] + X_test_norm @ np.array([row['w1'], row['w2']])

    residuals = Y_test - Y_pred
    RSS = np.sum(residuals ** 2)
    MSE = RSS / len(Y_test)
    TSS = np.sum((Y_test - np.mean(Y_test)) ** 2)
    R2 = 1 - (RSS / TSS) if TSS != 0 else 0

    results.append({
        'Split': split,
        'MSE': MSE,
        'R2': R2
    })

    print(f'Split {split} -> MSE={MSE:.2f}, R2={R2:.4f}')

results_df = pd.DataFrame(results)
results_df.to_csv('Assignment05/output/results.csv', index=False)


# 1g - Best split, then try different w-initializations and learning rates
best_idx = results_df['MSE'].idxmin()
best_split = results_df.loc[best_idx, 'Split']
best_x = int(best_split.split(':')[0])
best_y = int(best_split.split(':')[1])

print(f"\nBest split (lowest MSE): {best_split}")

best_train = pd.read_csv(f'Assignment05/dataset/set_{best_x}_train.csv')
best_test = pd.read_csv(f'Assignment05/dataset/set_{best_y}_test.csv')

X_train_best = best_train[['mileage', 'age']].values
Y_train_best = best_train['price'].values
X_test_best = best_test[['mileage', 'age']].values
Y_test_best = best_test['price'].values

# Normalize
x_mean_best = np.mean(X_train_best, axis=0)
x_std_best = np.std(X_train_best, axis=0)
x_std_best[x_std_best == 0] = 1
X_train_best_norm = (X_train_best - x_mean_best) / x_std_best
X_test_best_norm = (X_test_best - x_mean_best) / x_std_best

# Different initializations and learning rates
np.random.seed(42)
initializations = {
    'Zero': np.zeros(3),
    'Random [0,1]': np.random.uniform(0, 1, 3)
}

learning_rates = [0.0001, 0.05, 0.1, 1]

combo_results = []

for init_name, w_init in initializations.items():
    for lr in learning_rates:
        m = len(X_train_best_norm)
        X_b = np.c_[np.ones(m), X_train_best_norm]
        w = w_init.copy()

        for _ in range(5000):
            Y_pred = X_b @ w
            error = Y_pred - Y_train_best
            gradient = (X_b.T @ error) / m

            if np.any(np.isnan(gradient)) or np.any(np.abs(gradient) > 1e10):
                w = np.full(3, np.nan)
                break

            w = w - lr * gradient

            if np.any(np.isnan(w)) or np.any(np.abs(w) > 1e10):
                w = np.full(3, np.nan)
                break

        if np.any(np.isnan(w)):
            R2 = np.nan
            MSE = np.nan
        else:
            X_test_b = np.c_[np.ones(len(X_test_best_norm)), X_test_best_norm]
            Y_pred_test = X_test_b @ w
            residuals = Y_test_best - Y_pred_test
            RSS = np.sum(residuals ** 2)
            MSE = RSS / len(Y_test_best)
            TSS = np.sum((Y_test_best - np.mean(Y_test_best)) ** 2)
            R2 = 1 - (RSS / TSS) if TSS != 0 else 0

        combo_results.append({
            'Initialization': init_name,
            'Learning_Rate': lr,
            'w0': w[0],
            'w1': w[1],
            'w2': w[2],
            'MSE': MSE,
            'R2': R2
        })

combo_df = pd.DataFrame(combo_results)
combo_df.to_csv('Assignment05/output/gd_combinations.csv', index=False)
print("\nGD combinations results:")
print(combo_df)


# 1h - Report
report_lines = []
report_lines.append("Assignment 05 - Multiple Linear Regression Report")
report_lines.append("=" * 50)

report_lines.append("\n1c - Model Parameters (Batch GD)")
for _, row in params_df.iterrows():
    report_lines.append(f"  Split {row['Split']}: w0={row['w0']:.4f}, w1={row['w1']:.4f}, w2={row['w2']:.4f}")

report_lines.append("\n1f - MSE and R2 for test splits")
for _, row in results_df.iterrows():
    report_lines.append(f"  Split {row['Split']}: MSE={row['MSE']:.2f}, R2={row['R2']:.4f}")

report_lines.append(f"\n1g - Best split: {best_split}")
report_lines.append("\nGD combinations (w-init x learning rate):")
for _, row in combo_df.iterrows():
    report_lines.append(
        f"  Init={row['Initialization']}, LR={row['Learning_Rate']}: "
        f"MSE={row['MSE']}, R2={row['R2']}"
    )

with open('Assignment05/output/report.txt', 'w') as f:
    f.write('\n'.join(report_lines))

print("\nReport saved to Assignment05/output/report.txt")


# 2 - Using sklearn SGDRegressor
print("\n--- Sklearn SGDRegressor ---")

sklearn_results = []

for x in range(20, 100, 20):
    y = 100 - x

    train = pd.read_csv(f'Assignment05/dataset/set_{x}_train.csv')
    test = pd.read_csv(f'Assignment05/dataset/set_{y}_test.csv')

    X_tr = train[['mileage', 'age']].values
    Y_tr = train['price'].values
    X_te = test[['mileage', 'age']].values
    Y_te = test['price'].values

    sgd = SGDRegressor(
        loss='squared_error',
        max_iter=50000,
        tol=1e-3,
        random_state=42
    )
    sgd.fit(X_tr, Y_tr)

    Y_pred = sgd.predict(X_te)

    residuals = Y_te - Y_pred
    RSS = np.sum(residuals ** 2)
    MSE = RSS / len(Y_te)
    TSS = np.sum((Y_te - np.mean(Y_te)) ** 2)
    R2 = 1 - (RSS / TSS) if TSS != 0 else 0

    sklearn_results.append({
        'Split': f'{x}:{y}',
        'Intercept': sgd.intercept_[0],
        'Coef_mileage': sgd.coef_[0],
        'Coef_age': sgd.coef_[1],
        'MSE': MSE,
        'R2': R2
    })

    print(f'Split {x}:{y} -> MSE={MSE:.2f}, R2={R2:.4f}')

sklearn_df = pd.DataFrame(sklearn_results)
sklearn_df.to_csv('Assignment05/output/sklearn_results.csv', index=False)
print(sklearn_df)
