import pandas as pd
import os
import matplotlib.pyplot as plt
import numpy as np
# 1-a
df = pd.read_csv('./Salary_Data.csv')
df = df.dropna(subset=['Years of Experience', 'Salary'])

# 1-b
df = df.sample(frac=1, random_state=42).reset_index(drop=True)
os.makedirs('./Assignment03/dataset', exist_ok=True)
os.makedirs('./Assignment03/output', exist_ok=True)
os.makedirs('./Assignment03/plots', exist_ok=True)
i = 1
for x in range(10, 100, 10):
    y = 100 - x
    train_size = int(len(df) * x / 100)

    train = df.iloc[:train_size]
    test = df.iloc[train_size:]

    train.to_csv(f'./Assignment03/dataset/set{i}_{x}_train.csv', index=False)
    test.to_csv(f'./Assignment03/dataset/set{i}_{y}_test.csv', index=False)

    print(
        f'Split {x}:{y} -> '
        f'Train: set{i}_{x}_train.csv ({len(train)}), '
        f'Test: set{i}_{y}_test.csv ({len(test)})'
    )
    i += 1

# 1-c
params = []
for idx in range(1, 10):
    x = idx * 10
    y = 100 - x
    train = pd.read_csv(f'./Assignment03/dataset/set{idx}_{x}_train.csv')

    X = train['Years of Experience']
    Y = train['Salary']

    # w1 = cov(x,y) / var(x)
    w_1 = ((X - X.mean()) * (Y - Y.mean())).sum() / ((X - X.mean()) ** 2).sum()
    w_0 = Y.mean() - w_1 * X.mean()

    params.append({'Split': f'{x}:{y}', 'w_0': w_0, 'w_1': w_1})
params_df = pd.DataFrame(params)
params_df.to_csv('./Assignment03/output/params.csv', index=False)
print(params_df)

# 1-d-i
res = pd.read_csv('./Assignment03/output/params.csv')
w_0 = res['w_0']
w_1 = res['w_1']
x = np.linspace(0, 35, 35)
y_set = []

sample = pd.read_csv('./Salary_Data.csv')
exp = sample['Years of Experience']
sal = sample['Salary']

for idx in range(0, 9):
    y = w_0.iloc[idx] + w_1.iloc[idx] * x
    y_set.append(y)

for idx in range(len(y_set)):
    st = (idx+1)*10
    end = (9 - idx)*10
    plt.plot(x, y_set[idx], label=f"Line {st}")

    train_data = pd.read_csv(f'./Assignment03/dataset/set{idx+1}_{st}_train.csv')
    s_exp = train_data['Years of Experience']
    s_sal = train_data['Salary']
    plt.scatter(s_exp,s_sal, c='blue', alpha=0.4)
    
    test_data = pd.read_csv(f'./Assignment03/dataset/set{idx+1}_{end}_test.csv')
    s_exp = test_data['Years of Experience']
    s_sal = test_data['Salary']
    plt.scatter(s_exp,s_sal, c='red', alpha=0.4)
    
    plt.xlabel("Years of Experience")
    plt.ylabel("Salary")
    plt.title(f'Least Square regression: Split {st}|{end}')
    plt.legend()
    plt.tight_layout()
    plt.savefig(f'./Assignment03/plots/fig_{st}_{end}.png')
    plt.close()

for idx in range(len(y_set)):
    plt.plot(x, y_set[idx], label=f"Line {idx + 1}")

plt.scatter(exp, sal, c='green', alpha=0.3)
plt.xlabel("Years of Experience")
plt.ylabel("Salary")
plt.title("Least Square Regression")
plt.legend()
plt.grid()
plt.tight_layout()
plt.savefig('./Assignment03/plots/fig_1d_i.png')

# 1-d-ii
for idx in range(0, 9):
  st = (idx+1)*10
  end = (9 - idx)*10
  testSample = pd.read_csv(f'./Assignment03/dataset/set{idx+1}_{end}_test.csv')
  s_exp = testSample['Years of Experience']
  s_sal = testSample['Salary']
  pred = w_0.iloc[idx] + w_1.iloc[idx] * s_exp
  
  result = pd.DataFrame({
    'Years of Experience': s_exp,
    'Actual Salary': s_sal,
    'Predicted Salary': pred
  })
  result.to_excel(f'./Assignment03/output/predictions_{st}_{end}.xlsx',index=False)

  print(f'Saved predictions for split {st}:{end}')


# 1-d-iii
results = []
for idx in range(0, 9):
    st = (idx + 1) * 10
    end = 100 - st
    # Read test data
    testSample = pd.read_csv(
        f'./Assignment03/dataset/set{idx+1}_{end}_test.csv'
    )
    X_test = testSample['Years of Experience']
    Y_test = testSample['Salary']
    # Corresponding hypothesis
    w0 = w_0.iloc[idx]
    w1 = w_1.iloc[idx]

    # Prediction
    Y_pred = w0 + w1 * X_test
    # Residuals
    residuals = Y_test - Y_pred
    # RSS
    RSS = np.sum(residuals ** 2)
    # Mean RSS
    mean_RSS = RSS / len(Y_test)
    # TSS
    TSS = np.sum((Y_test - Y_test.mean()) ** 2)
    # R²
    R2 = 1 - (RSS / TSS)
    # Store result
    results.append({
        'Split': f'{st}:{end}',
        'R2': R2,
        'Mean-RSS': mean_RSS
    })

# Convert to DataFrame
results_df = pd.DataFrame(results)
# Store all results in ONE Excel file
results_df.to_excel(
    './Assignment03/output/results.xlsx',
    index=False
)
print(results_df)



# 1-d-iv
results_df = pd.read_excel('./Assignment03/output/results.xlsx')
# Extract training percentage from Split
training_percentage = results_df['Split'].apply(
    lambda x: int(str(x).split(':')[0])
)

mean_rss = results_df['Mean-RSS']
plt.figure(figsize=(8, 5))
plt.plot(
    training_percentage,
    mean_rss,
    marker='o'
)
plt.xlabel("Percentage of Training Samples")
plt.ylabel("Mean-RSS")
plt.title("Mean-RSS vs Percentage of Training Samples")
plt.grid(True)

plt.tight_layout()
plt.savefig('./Assignment03/plots/mean_RSS.png')
plt.close()



# 1-d-v
R2 = results_df['R2']
plt.figure(figsize=(8, 5))
plt.plot(
    training_percentage,
    R2,
    marker='o'
)

plt.xlabel("Percentage of Training Samples")
plt.ylabel("R² Score")
plt.title("R² vs Percentage of Training Samples")
plt.grid(True)

plt.tight_layout()
plt.savefig('./Assignment03/plots/R2.png')
plt.close()



# 1-d-vi
def gradient_descent(X, Y, theta0, theta1, learning_rate=0.001, epochs=10000):
    m = len(X)
    for _ in range(epochs):
        # Prediction
        Y_pred = theta0 + theta1 * X
        # Errors
        error = Y_pred - Y
        # Gradients
        dtheta0 = np.sum(error) / m
        dtheta1 = np.sum(error * X) / m
        # Update parameters
        theta0 = theta0 - learning_rate * dtheta0
        theta1 = theta1 - learning_rate * dtheta1
    return theta0, theta1

# Get best split
best_idx = results_df['R2'].idxmax()
best_split = results_df.loc[best_idx, 'Split']
train_percent = int(best_split.split(':')[0])
test_percent = 100 - train_percent

# Find the corresponding dataset number
set_number = train_percent // 10

# Read best training and testing data
train_data = pd.read_csv(
    f'./Assignment03/dataset/set{set_number}_{train_percent}_train.csv'
)

test_data = pd.read_csv(
    f'./Assignment03/dataset/set{set_number}_{test_percent}_test.csv'
)

X_train = train_data['Years of Experience'].values
Y_train = train_data['Salary'].values

X_test = test_data['Years of Experience'].values
Y_test = test_data['Salary'].values


# Different initializations
initializations = {
    'Zero': (0, 0),
    '[0,1]': (
        np.random.uniform(0, 1),
        np.random.uniform(0, 1)
    ),
    '[0,100]': (
        np.random.uniform(0, 100),
        np.random.uniform(0, 100)
    )
}
results_gd = []

for name, (theta0, theta1) in initializations.items():
    # Gradient descent
    theta0, theta1 = gradient_descent(
        X_train,
        Y_train,
        theta0,
        theta1
    )

    # Prediction on test data
    Y_pred = theta0 + theta1 * X_test
    # Residuals
    residuals = Y_test - Y_pred
    # RSS
    RSS = np.sum(residuals ** 2)
    # Mean-RSS
    mean_RSS = RSS / len(Y_test)
    # TSS
    TSS = np.sum((Y_test - Y_test.mean()) ** 2)
    # R²
    R2 = 1 - RSS / TSS

    results_gd.append({
        'Initialization': name,
        'Theta_0': theta0,
        'Theta_1': theta1,
        'R2': R2,
        'Mean-RSS': mean_RSS
    })


# Store results
gd_results_df = pd.DataFrame(results_gd)

gd_results_df.to_excel(
    './Assignment03/output/gradient_descent_results.xlsx',
    index=False
)

print("\nBest Split:", best_split)
print(gd_results_df)





