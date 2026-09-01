import pandas as pd
import os
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import SGDRegressor
from sklearn.exceptions import ConvergenceWarning
import warnings
warnings.filterwarnings('ignore', category=ConvergenceWarning)


# 1A
df = pd.read_csv("Assignment04/salary_data.csv")
df = df.dropna(subset=['YearsExperience', 'Salary'])

# 1B
df = df.sample(frac=1, random_state=42).reset_index(drop=True)
os.makedirs('Assignment04/dataset', exist_ok=True)
os.makedirs('Assignment04/output', exist_ok=True)
os.makedirs('Assignment04/plots', exist_ok=True)

for x in range(1, 10, 1):
  y = 10 - x
  train_size = int(len(df)* x/10)
  
  train = df.iloc[:train_size]
  test = df.iloc[train_size:]
  
  train.to_csv(f'./Assignment04/dataset/set{x}_{x*10}_train.csv', index=False)
  test.to_csv(f'./Assignment04/dataset/set{x}_{y*10}_test.csv', index=False)
  print(
        f'Split {x}:{y} -> '
        f'Train: set{x}_{x*10}_train.csv ({len(train)}), '
        f'Test: set{x}_{y*10}_test.csv ({len(test)})'
  )

# 1C
for k in range(1, 10, 1):
  train = pd.read_csv(f'./Assignment04/dataset/set{k}_{k*10}_train.csv')

  X = train['YearsExperience'].values
  Y = train['Salary'].values

  w1 = 0
  w2 = 0
  alpha = 0.001

  for _ in range(1000):
    delta1 = 0
    delta2 = 0
    for j in range(len(X)):
      yCap = w1 + w2*X[j]
      delta1 += yCap - Y[j]
      delta2 += (yCap - Y[j])*X[j]
    
    w1 = w1 - alpha* (delta1/len(X))
    w2 = w2 - alpha* (delta2/len(X))
  
  with open(f'./Assignment04/output/set{k}_params.txt', 'w') as file:
    file.write(f'w1 = {w1}\n')
    file.write(f'w2 = {w2}\n')
  print(f'Split > {k*10} | {(10-k)*10} > w1 = {w1} : w2 = {w2}')

X_plot = np.linspace(0, 10.5, 22)
plt.figure()
plt.scatter(
    df['YearsExperience'],
    df['Salary'],
    label='Data'
)
# 1D-i
for k in range(1, 10):
    with open(f'./Assignment04/output/set{k}_params.txt', 'r') as file:
        w1 = float(file.readline().split(' = ')[1])
        w2 = float(file.readline().split(' = ')[1])

    Y_plot = w1 + w2 * X_plot

    plt.plot(
        X_plot,
        Y_plot,
        label=f'Set {k} ({k*10}:{(10-k)*10})'
    )
plt.xlabel("Years of Experience")
plt.ylabel("Salary")
plt.title("GD Hypotheses for Different Training Splits")
plt.legend()

plt.savefig('./Assignment04/plots/Figure.png')
plt.close()


# 1D-ii & iii
predictions = []
results = []
for k in range(1, 10):

    test = pd.read_csv(
        f'./Assignment04/dataset/set{k}_{(10-k)*10}_test.csv'
    )

    X_test = test['YearsExperience'].values
    Y_test = test['Salary'].values

    with open(f'./Assignment04/output/set{k}_params.txt', 'r') as file:
        w1 = float(file.readline().split(' = ')[1])
        w2 = float(file.readline().split(' = ')[1])

    Y_pred = w1 + w2 * X_test

    for i in range(len(X_test)):
        predictions.append({
            'Split': f'{k*10}:{(10-k)*10}',
            'YearsExperience': X_test[i],
            'ActualSalary': Y_test[i],
            'PredictedSalary': Y_pred[i]
        })

    residuals = Y_test - Y_pred
    RSS = np.sum(residuals ** 2)

    mean_RSS = RSS / len(Y_test)

    total = np.sum(
        (Y_test - np.mean(Y_test)) ** 2
    )
    R2 = 1 - (RSS / total)

    results.append({
        'Split': f'{k*10}:{(10-k)*10}',
        'R2': R2,
        'Mean-RSS': mean_RSS
    })

predictions_df = pd.DataFrame(predictions)
results_df = pd.DataFrame(results)

predictions_df.to_csv(
    './Assignment04/output/predictions.csv',
    index=False
)
results_df.to_csv(
    './Assignment04/output/results.csv',
    index=False
)
predictions_df.to_excel(
    './Assignment04/output/predictions.xlsx',
    index=False
)
results_df.to_excel(
    './Assignment04/output/results.xlsx',
    index=False
)

print("Predictions and R2/Mean-RSS results saved.")


# 1-d-iv
train_mean_rss_list = []
test_mean_rss_list = []
training_percentage = []

for k in range(1, 10):
    st = k * 10
    end = (10 - k) * 10
    training_percentage.append(st)

    with open(f'./Assignment04/output/set{k}_params.txt', 'r') as file:
        w1 = float(file.readline().split(' = ')[1])
        w2 = float(file.readline().split(' = ')[1])

    train = pd.read_csv(f'./Assignment04/dataset/set{k}_{st}_train.csv')
    X_train = train['YearsExperience'].values
    Y_train = train['Salary'].values
    Y_pred_train = w1 + w2 * X_train
    mean_rss_train = np.mean((Y_train - Y_pred_train) ** 2)
    train_mean_rss_list.append(mean_rss_train)

    test = pd.read_csv(f'./Assignment04/dataset/set{k}_{end}_test.csv')
    X_test = test['YearsExperience'].values
    Y_test = test['Salary'].values
    Y_pred_test = w1 + w2 * X_test
    mean_rss_test = np.mean((Y_test - Y_pred_test) ** 2)
    test_mean_rss_list.append(mean_rss_test)

plt.figure(figsize=(8, 5))
plt.plot(training_percentage, train_mean_rss_list, marker='o', label='Train Mean-RSS')
plt.plot(training_percentage, test_mean_rss_list, marker='s', label='Test Mean-RSS')
plt.xlabel("Percentage of Training Samples")
plt.ylabel("Mean-RSS")
plt.title("Mean-RSS vs Percentage of Training Samples (Train vs Test)")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('./Assignment04/plots/mean_RSS.png')
plt.close()


# 1-d-v
train_r2_list = []
test_r2_list = []

for k in range(1, 10):
    st = k * 10
    end = (10 - k) * 10

    with open(f'./Assignment04/output/set{k}_params.txt', 'r') as file:
        w1 = float(file.readline().split(' = ')[1])
        w2 = float(file.readline().split(' = ')[1])

    train = pd.read_csv(f'./Assignment04/dataset/set{k}_{st}_train.csv')
    X_train = train['YearsExperience'].values
    Y_train = train['Salary'].values
    Y_pred_train = w1 + w2 * X_train
    rss_train = np.sum((Y_train - Y_pred_train) ** 2)
    tss_train = np.sum((Y_train - np.mean(Y_train)) ** 2)
    r2_train = 1 - (rss_train / tss_train) if tss_train != 0 else 0
    train_r2_list.append(r2_train)

    test = pd.read_csv(f'./Assignment04/dataset/set{k}_{end}_test.csv')
    X_test = test['YearsExperience'].values
    Y_test = test['Salary'].values
    Y_pred_test = w1 + w2 * X_test
    rss_test = np.sum((Y_test - Y_pred_test) ** 2)
    tss_test = np.sum((Y_test - np.mean(Y_test)) ** 2)
    r2_test = 1 - (rss_test / tss_test) if tss_test != 0 else 0
    test_r2_list.append(r2_test)

plt.figure(figsize=(8, 5))
plt.plot(training_percentage, train_r2_list, marker='o', label='Train R²')
plt.plot(training_percentage, test_r2_list, marker='s', label='Test R²')
plt.xlabel("Percentage of Training Samples")
plt.ylabel("R² Score")
plt.title("R² Score vs Percentage of Training Samples (Train vs Test)")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('./Assignment04/plots/R2.png')
plt.close()


# 1-d-vi
def run_gradient_descent(X, Y, w1_init, w2_init, alpha=0.001, epochs=1000):
    w1 = float(w1_init)
    w2 = float(w2_init)
    m = len(X)
    for _ in range(epochs):
        delta1 = 0.0
        delta2 = 0.0
        for j in range(m):
            yCap = w1 + w2 * X[j]
            delta1 += yCap - Y[j]
            delta2 += (yCap - Y[j]) * X[j]
        
        if np.isnan(delta1) or np.isinf(delta1) or np.isnan(delta2) or np.isinf(delta2) or abs(delta1) > 1e10 or abs(delta2) > 1e10:
            return np.nan, np.nan

        w1_new = w1 - alpha * (delta1 / m)
        w2_new = w2 - alpha * (delta2 / m)
        
        if np.isnan(w1_new) or np.isinf(w1_new) or np.isnan(w2_new) or np.isinf(w2_new) or abs(w1_new) > 1e10 or abs(w2_new) > 1e10:
            return np.nan, np.nan

        w1 = w1_new
        w2 = w2_new
    return w1, w2



best_idx = results_df['R2'].idxmax()
best_split = results_df.loc[best_idx, 'Split']
train_percent = int(best_split.split(':')[0])
test_percent = int(best_split.split(':')[1])
best_set = train_percent // 10

best_train = pd.read_csv(f'./Assignment04/dataset/set{best_set}_{train_percent}_train.csv')
best_test = pd.read_csv(f'./Assignment04/dataset/set{best_set}_{test_percent}_test.csv')

X_train_best = best_train['YearsExperience'].values
Y_train_best = best_train['Salary'].values
X_test_best = best_test['YearsExperience'].values
Y_test_best = best_test['Salary'].values

np.random.seed(42)
initializations = {
    'Zero': (0.0, 0.0),
    'Random [0,1]': (np.random.uniform(0, 1), np.random.uniform(0, 1)),
    'Random [0,100]': (np.random.uniform(0, 100), np.random.uniform(0, 100))
}

results_init = []
for name, (w1_0, w2_0) in initializations.items():
    w1, w2 = run_gradient_descent(X_train_best, Y_train_best, w1_0, w2_0, alpha=0.001, epochs=1000)
    
    Y_pred = w1 + w2 * X_test_best
    residuals = Y_test_best - Y_pred
    RSS = np.sum(residuals ** 2)
    mean_RSS = RSS / len(Y_test_best)
    total = np.sum((Y_test_best - np.mean(Y_test_best)) ** 2)
    R2 = 1 - (RSS / total) if total != 0 else 0

    results_init.append({
        'Initialization': name,
        'Initial_w1': w1_0,
        'Initial_w2': w2_0,
        'Final_w1': w1,
        'Final_w2': w2,
        'R2': R2,
        'Mean-RSS': mean_RSS
    })

df_init = pd.DataFrame(results_init)
df_init.to_csv('./Assignment04/output/gd_init.csv', index=False)
print(f"\nBest Split selected: {best_split}")
print("Gradient Descent with different initializations :")
print(df_init)


# 1-d-vii
learning_rates = [0.0001, 0.05, 0.1, 1, 10, 100, 1000]
results_combinations = []

for init_name, (w1_0, w2_0) in initializations.items():
    for lr in learning_rates:
        w1, w2 = run_gradient_descent(X_train_best, Y_train_best, w1_0, w2_0, alpha=lr, epochs=1000)
        
        if np.isnan(w1) or np.isinf(w1) or np.isnan(w2) or np.isinf(w2):
            R2 = np.nan
            mean_RSS = np.nan
        else:
            Y_pred = w1 + w2 * X_test_best
            residuals = Y_test_best - Y_pred
            RSS = np.sum(residuals ** 2)
            mean_RSS = RSS / len(Y_test_best)
            total = np.sum((Y_test_best - np.mean(Y_test_best)) ** 2)
            R2 = 1 - (RSS / total) if total != 0 else 0

        results_combinations.append({
            'Initialization': init_name,
            'Learning_Rate': lr,
            'Final_w1': w1,
            'Final_w2': w2,
            'R2': R2,
            'Mean-RSS': mean_RSS
        })

df_comb = pd.DataFrame(results_combinations)
df_comb.to_csv('./Assignment04/output/gd_lr_init.csv', index=False)
print("\nGD for combinations of initializations & learning rates: ")
print(df_comb)

sklearn_gd_results = []
sklearn_gd_predictions = []

for k in range(1, 10):
    st = k * 10
    end = (10 - k) * 10
    
    train = pd.read_csv(f'./Assignment04/dataset/set{k}_{st}_train.csv')
    test = pd.read_csv(f'./Assignment04/dataset/set{k}_{end}_test.csv')

    X_tr = train[['YearsExperience']].values
    Y_tr = train['Salary'].values
    X_te = test[['YearsExperience']].values
    Y_te = test['Salary'].values

    sgd = SGDRegressor(loss='squared_error', max_iter=50000, tol=1e-3, random_state=42)
    sgd.fit(X_tr, Y_tr)

    w1_sgd = sgd.intercept_[0]
    w2_sgd = sgd.coef_[0]

    Y_pred_sgd = sgd.predict(X_te)

    for i in range(len(X_te)):
        sklearn_gd_predictions.append({
            'Split': f'{st}:{end}',
            'YearsExperience': X_te[i][0],
            'ActualSalary': Y_te[i],
            'PredictedSalary': Y_pred_sgd[i]
        })

    residuals = Y_te - Y_pred_sgd
    RSS = np.sum(residuals ** 2)
    mean_RSS = RSS / len(Y_te)
    total = np.sum((Y_te - np.mean(Y_te)) ** 2)
    R2 = 1 - (RSS / total) if total != 0 else 0

    sklearn_gd_results.append({
        'Split': f'{st}:{end}',
        'w1_Intercept': w1_sgd,
        'w2_Slope': w2_sgd,
        'R2': R2,
        'Mean-RSS': mean_RSS
    })

df_sgd_res = pd.DataFrame(sklearn_gd_results)
df_sgd_pred = pd.DataFrame(sklearn_gd_predictions)

df_sgd_res.to_csv('./Assignment04/output/sgd_results.csv', index=False)
df_sgd_pred.to_csv('./Assignment04/output/sgd_predictions.csv', index=False)

print("\nSklearn SGDRegressor Results:")
print(df_sgd_res)


# 3. Ordinary Least Squares (OLS) and Comparison
from sklearn.linear_model import LinearRegression

ols_results = []
comparison_list = []

for k in range(1, 10):
    st = k * 10
    end = (10 - k) * 10
    
    train = pd.read_csv(f'./Assignment04/dataset/set{k}_{st}_train.csv')
    test = pd.read_csv(f'./Assignment04/dataset/set{k}_{end}_test.csv')

    X_tr = train[['YearsExperience']].values
    Y_tr = train['Salary'].values
    X_te = test[['YearsExperience']].values
    Y_te = test['Salary'].values

    ols = LinearRegression()
    ols.fit(X_tr, Y_tr)

    w1_ols = ols.intercept_
    w2_ols = ols.coef_[0]

    Y_pred_ols = ols.predict(X_te)
    residuals_ols = Y_te - Y_pred_ols
    RSS_ols = np.sum(residuals_ols ** 2)
    mean_RSS_ols = RSS_ols / len(Y_te)
    total = np.sum((Y_te - np.mean(Y_te)) ** 2)
    R2_ols = 1 - (RSS_ols / total) if total != 0 else 0

    ols_results.append({
        'Split': f'{st}:{end}',
        'w1_Intercept': w1_ols,
        'w2_Slope': w2_ols,
        'R2': R2_ols,
        'Mean-RSS': mean_RSS_ols
    })

    manual_r2 = results_df.loc[k-1, 'R2']
    manual_mean_rss = results_df.loc[k-1, 'Mean-RSS']
    sgd_r2 = df_sgd_res.loc[k-1, 'R2']
    sgd_mean_rss = df_sgd_res.loc[k-1, 'Mean-RSS']

    comparison_list.append({
        'Split': f'{st}:{end}',
        'Manual_GD_R2': manual_r2,
        'Manual_GD_MeanRSS': manual_mean_rss,
        'Sklearn_SGD_R2': sgd_r2,
        'Sklearn_SGD_MeanRSS': sgd_mean_rss,
        'OLS_R2': R2_ols,
        'OLS_MeanRSS': mean_RSS_ols
    })

df_ols = pd.DataFrame(ols_results)
df_ols.to_csv('./Assignment04/output/ols_results.csv', index=False)

df_comparison = pd.DataFrame(comparison_list)
df_comparison.to_csv('./Assignment04/output/comparison_summary.csv', index=False)

print("\n=== OLS Results ===")
print(df_ols)
print("\n=== Model Comparison Summary (Manual GD vs Sklearn SGD vs OLS) ===")
print(df_comparison)

# Comparison Plots
splits_x = [k * 10 for k in range(1, 10)]

plt.figure(figsize=(9, 5))
plt.plot(splits_x, df_comparison['Manual_GD_R2'], marker='o', label='Manual GD R²')
plt.plot(splits_x, df_comparison['Sklearn_SGD_R2'], marker='s', label='Sklearn SGD R²')
plt.plot(splits_x, df_comparison['OLS_R2'], marker='^', label='OLS R²')
plt.xlabel("Percentage of Training Samples")
plt.ylabel("R² Score")
plt.title("Comparison of R² Scores: Manual GD vs Sklearn SGD vs OLS")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('./Assignment04/plots/comparison_R2.png')
plt.close()

plt.figure(figsize=(9, 5))
plt.plot(splits_x, df_comparison['Manual_GD_MeanRSS'], marker='o', label='Manual GD Mean-RSS')
plt.plot(splits_x, df_comparison['Sklearn_SGD_MeanRSS'], marker='s', label='Sklearn SGD Mean-RSS')
plt.plot(splits_x, df_comparison['OLS_MeanRSS'], marker='^', label='OLS Mean-RSS')
plt.xlabel("Percentage of Training Samples")
plt.ylabel("Mean-RSS")
plt.title("Comparison of Mean-RSS: Manual GD vs Sklearn SGD vs OLS")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('./Assignment04/plots/comparison_mean_RSS.png')
plt.close()

