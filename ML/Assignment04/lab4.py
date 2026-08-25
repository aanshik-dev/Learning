import pandas as pd
import os
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv("Assignment04/salary_data.csv")
df = df.dropna(subset=['YearsExperience', 'Salary'])

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

with pd.ExcelWriter(
    './Assignment04/output/results.xlsx'
) as writer:

    predictions_df.to_excel(
        writer,
        sheet_name='Predictions',
        index=False
    )

    results_df.to_excel(
        writer,
        sheet_name='R2_MeanRSS',
        index=False
    )

print("Predictions and R2/Mean-RSS results saved.")