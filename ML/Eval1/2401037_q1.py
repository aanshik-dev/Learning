import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Reading the Dataset file
df = pd.read_csv('./Eval1/Salary_Data.csv')
df = df.dropna(subset=['Years of Experience', 'Salary'])
print(df.describe())

os.makedirs('./Eval1/dataset', exist_ok=True)
os.makedirs('./Eval1/plots', exist_ok=True)
os.makedirs('./Eval1/output', exist_ok=True)

df = df.sample(frac=1, random_state=42).reset_index(drop=True)

# Splitting the dataset into 9 sets
for x in range(1, 10, 1):
    y = 10 - x
    trainSize = int(len(df) * (x / 10))
    train = df.iloc[:trainSize]
    test = df.iloc[trainSize:]
    train.to_csv(f'./Eval1/dataset/set_{x}-{y}_train.csv', index=False)
    test.to_csv(f'./Eval1/dataset/set_{x}-{y}_test.csv', index=False)

print('\nSplitted the dataset in 9 sets of different ratios !!\n')

# Ordianry Linear Regression
params = []
for x in range(1, 10):
    y = 10 - x
    train = pd.read_csv(f'./Eval1/dataset/set_{x}-{y}_train.csv')

    X = train['Years of Experience']
    Y = train['Salary']

    # w1 = cov(x,y) / var(x)
    w_1 = ((X - X.mean()) * (Y - Y.mean())).sum() / ((X - X.mean()) ** 2).sum()
    w_0 = Y.mean() - w_1 * X.mean()
    params.append({'Split': f'{x}:{y}','w_0': w_0,'w_1': w_1})
params_df = pd.DataFrame(params)
params_df.to_csv('./Eval1/output/params.csv', index=False)
print('--- Ordinary Linear Regression ---')
print(params_df)

res = pd.read_csv('./Eval1/output/params.csv')
w_0 = res['w_0']
w_1 = res['w_1']
x_plot = np.linspace(0, 35, 100)

for idx in range(len(res)):
    x = idx + 1
    y = 10 - x
    y_line = w_0.iloc[idx] + w_1.iloc[idx] * x_plot

    train_data = pd.read_csv(f'./Eval1/dataset/set_{x}-{y}_train.csv')
    test_data = pd.read_csv(f'./Eval1/dataset/set_{x}-{y}_test.csv')

    # Individual Scatters
    plt.scatter(train_data['Years of Experience'], train_data['Salary'], c='blue', alpha=0.4, label='Train')
    plt.scatter(test_data['Years of Experience'], test_data['Salary'], c='red', alpha=0.4, label='Test')
    plt.plot(x_plot, y_line, label=f'OLS {x}:{y}')
    plt.xlabel('Years of Experience')
    plt.ylabel('Salary')
    plt.title(f'OLS Regression: Split {x}:{y}')
    plt.legend()
    plt.tight_layout()
    plt.savefig(f'./Eval1/plots/ols_{x}_{y}.png')
    plt.close()

for idx in range(len(res)):
    x = idx + 1
    y_line = w_0.iloc[idx] + w_1.iloc[idx] * x_plot
    plt.plot(x_plot, y_line, label=f'Split {x}:{10 - x}')

plt.scatter(df['Years of Experience'], df['Salary'], c='green', alpha=0.3, label='Data')
plt.xlabel('Years of Experience')
plt.ylabel('Salary')
plt.title('OLS Regression: All Splits')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('./Eval1/plots/ols_all.png')
plt.close()

# Finding the predicted and the actual salary and saving in outut
ols_results = []
for idx in range(len(res)):
    x = idx + 1
    y = 10 - x
    test_data = pd.read_csv(f'./Eval1/dataset/set_{x}-{y}_test.csv')

    X_test = test_data['Years of Experience']
    Y_test = test_data['Salary']

    Y_pred = w_0.iloc[idx] + w_1.iloc[idx] * X_test

    predictions = pd.DataFrame({
        'Years of Experience': X_test,
        'Actual Salary': Y_test,
        'Predicted Salary': Y_pred
    })
    predictions.to_csv(f'./Eval1/output/ols_predictions_{x}_{y}.csv', index=False)

    residuals = Y_test - Y_pred
    RSS = np.sum(residuals ** 2)
    mean_RSS = RSS / len(Y_test)
    TSS = np.sum((Y_test - Y_test.mean()) ** 2)
    R2 = 1 - (RSS / TSS)

    ols_results.append({
        'Split': f'{x}:{y}',
        'R2': R2,
        'Mean-RSS': mean_RSS
    })

ols_results_df = pd.DataFrame(ols_results)
ols_results_df.to_csv('./Eval1/output/ols_results.csv', index=False)


training_pct = [k * 10 for k in range(1, 10)]

plt.figure(figsize=(8, 5))
plt.plot(training_pct, ols_results_df['Mean-RSS'], marker='o')
plt.xlabel('Percentage of Training Samples')
plt.ylabel('Mean-RSS')
plt.title('OLS: Mean-RSS vs Training Percentage')
plt.grid(True)
plt.tight_layout()
plt.savefig('./Eval1/plots/ols_mean_rss.png')
plt.close()

plt.figure(figsize=(8, 5))
plt.plot(training_pct, ols_results_df['R2'], marker='o')
plt.xlabel('Percentage of Training Samples')
plt.ylabel('R² Score')
plt.title('OLS: R² vs Training Percentage')
plt.grid(True)
plt.tight_layout()
plt.savefig('./Eval1/plots/ols_r2.png')
plt.close()

# Gradient Descent Method
def gradient_descent(X, Y, alpha=0.001, epochs=10000):
    w0, w1 = 0.0, 0.0
    m = len(X)
    for _ in range(epochs):
        Y_pred = w0 + w1 * X
        error = Y_pred - Y
        dw0 = np.sum(error) / m
        dw1 = np.sum(error * X) / m
        
        new_w0 = w0 - alpha * dw0
        new_w1 = w1 - alpha * dw1
        
        if np.isnan(new_w0) or np.isinf(new_w0) or np.isnan(new_w1) or np.isinf(new_w1):
            break
            
        w0, w1 = new_w0, new_w1
    return w0, w1


best_idx = ols_results_df['R2'].idxmax()
best_split = ols_results_df.loc[best_idx, 'Split']
train_pct = int(best_split.split(':')[0])
test_pct = int(best_split.split(':')[1])

best_train = pd.read_csv(f'./Eval1/dataset/set_{train_pct}-{test_pct}_train.csv')
best_test = pd.read_csv(f'./Eval1/dataset/set_{train_pct}-{test_pct}_test.csv')

X_train_best = best_train['Years of Experience'].values
Y_train_best = best_train['Salary'].values
X_test_best = best_test['Years of Experience'].values
Y_test_best = best_test['Salary'].values

learning_rates = [0.0001, 0.001, 0.01]

gd_results = []
for lr in learning_rates:
    w0, w1 = gradient_descent(X_train_best, Y_train_best, alpha=lr)

    Y_pred = w0 + w1 * X_test_best
    residuals = Y_test_best - Y_pred
    RSS = np.sum(residuals ** 2)
    mean_RSS = RSS / len(Y_test_best)
    TSS = np.sum((Y_test_best - np.mean(Y_test_best)) ** 2)
    R2 = 1 - (RSS / TSS) if TSS != 0 else 0

    gd_results.append({
        'Learning_Rate': lr,
        'Final_w0': w0,
        'Final_w1': w1,
        'R2': R2,
        'Mean-RSS': mean_RSS
    })

gd_df = pd.DataFrame(gd_results)
gd_df.to_csv('./Eval1/output/gd_results.csv', index=False)
print(f'\nBest Split (from OLS): {best_split}\n')
print('--- Gradient Descent: Hyperparameter Tuning ---')
print(gd_df)

best_lr = gd_df.loc[gd_df['R2'].idxmax(), 'Learning_Rate']

gd_split_results = []
for x in range(1, 10):
    y = 10 - x
    train_data = pd.read_csv(f'./Eval1/dataset/set_{x}-{y}_train.csv')
    test_data = pd.read_csv(f'./Eval1/dataset/set_{x}-{y}_test.csv')

    X_tr = train_data['Years of Experience'].values
    Y_tr = train_data['Salary'].values
    X_te = test_data['Years of Experience'].values
    Y_te = test_data['Salary'].values

    w0, w1 = gradient_descent(X_tr, Y_tr, alpha=best_lr)

    Y_pred = w0 + w1 * X_te

    predictions = pd.DataFrame({
        'Years of Experience': X_te,
        'Actual Salary': Y_te,
        'Predicted Salary': Y_pred
    })
    predictions.to_csv(f'./Eval1/output/gd_predictions_{x}_{y}.csv', index=False)

    residuals = Y_te - Y_pred
    RSS = np.sum(residuals ** 2)
    mean_RSS = RSS / len(Y_te)
    TSS = np.sum((Y_te - np.mean(Y_te)) ** 2)
    R2 = 1 - (RSS / TSS) if TSS != 0 else 0

    gd_split_results.append({
        'Split': f'{x}:{y}',
        'w_0': w0,
        'w_1': w1,
        'R2': R2,
        'Mean-RSS': mean_RSS
    })

gd_split_df = pd.DataFrame(gd_split_results)
gd_split_df.to_csv('./Eval1/output/gd_split_results.csv', index=False)
print('\n--- Gradient Descent Parameters ---')
print(gd_split_df[['Split', 'w_0', 'w_1']])

for x in range(1, 10):
    y = 10 - x
    train_data = pd.read_csv(f'./Eval1/dataset/set_{x}-{y}_train.csv')
    test_data = pd.read_csv(f'./Eval1/dataset/set_{x}-{y}_test.csv')

    X_tr = train_data['Years of Experience'].values
    Y_tr = train_data['Salary'].values

    w0, w1 = gradient_descent(X_tr, Y_tr, alpha=best_lr)
    y_line = w0 + w1 * x_plot

    plt.scatter(train_data['Years of Experience'], train_data['Salary'], c='blue', alpha=0.4, label='Train')
    plt.scatter(test_data['Years of Experience'], test_data['Salary'], c='red', alpha=0.4, label='Test')
    plt.plot(x_plot, y_line, label=f'GD {x}:{y}')
    plt.xlabel('Years of Experience')
    plt.ylabel('Salary')
    plt.title(f'GD Regression: Split {x}:{y}')
    plt.legend()
    plt.tight_layout()
    plt.savefig(f'./Eval1/plots/gd_{x}_{y}.png')
    plt.close()

for x in range(1, 10):
    y = 10 - x
    train_data = pd.read_csv(f'./Eval1/dataset/set_{x}-{y}_train.csv')
    X_tr = train_data['Years of Experience'].values
    Y_tr = train_data['Salary'].values
    w0, w1 = gradient_descent(X_tr, Y_tr, alpha=best_lr)
    plt.plot(x_plot, w0 + w1 * x_plot, label=f'Split {x}:{10 - x}')

plt.scatter(df['Years of Experience'], df['Salary'], c='green', alpha=0.3, label='Data')
plt.xlabel('Years of Experience')
plt.ylabel('Salary')
plt.title('GD Regression: All Splits')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('./Eval1/plots/gd_all.png')
plt.close()

comparison = []
for idx in range(len(ols_results_df)):
    comparison.append({
        'Split': ols_results_df.loc[idx, 'Split'],
        'OLS_R2': ols_results_df.loc[idx, 'R2'],
        'OLS_Mean-RSS': ols_results_df.loc[idx, 'Mean-RSS'],
        'GD_R2': gd_split_df.loc[idx, 'R2'],
        'GD_Mean-RSS': gd_split_df.loc[idx, 'Mean-RSS']
    })

comparison_df = pd.DataFrame(comparison)
comparison_df.to_csv('./Eval1/output/comparison.csv', index=False)
print('\n--- OLS vs Gradient Descent ---')
print(comparison_df)

plt.figure(figsize=(9, 5))
plt.plot(training_pct, comparison_df['OLS_R2'], marker='o', label='OLS R²')
plt.plot(training_pct, comparison_df['GD_R2'], marker='s', label='GD R²')
plt.xlabel('Percentage of Training Samples')
plt.ylabel('R² Score')
plt.title('Comparison: OLS vs GD R² Score')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('./Eval1/plots/comparison_r2.png')
plt.close()

plt.figure(figsize=(9, 5))
plt.plot(training_pct, comparison_df['OLS_Mean-RSS'], marker='o', label='OLS Mean-RSS')
plt.plot(training_pct, comparison_df['GD_Mean-RSS'], marker='s', label='GD Mean-RSS')
plt.xlabel('Percentage of Training Samples')
plt.ylabel('Mean-RSS')
plt.title('Comparison: OLS vs GD Mean-RSS')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('./Eval1/plots/comparison_mean_rss.png')
plt.close()
