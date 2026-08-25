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
    plt.plot(x, y_set[idx], label=f"Line {idx + 1}")

plt.scatter(exp, sal, c='green', alpha=0.3)
plt.xlabel("Years of Experience")
plt.ylabel("Salary")
plt.title("Least Square Regression")
plt.legend()
plt.grid()
plt.tight_layout()
plt.savefig('./Assignment03/plots/fig_1d_i.png')
plt.show()

# 1-d-ii
for idx in range(0, 9):
    



