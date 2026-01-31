# Create a Pandas DataFrame named df with columns Std Name (string), Roll no (integer),
# and CPI (float). Write Python code to create a new DataFrame containing only the rows
# where the value in the CPI column is greater than 60. Also, calculate the overall mean,
# median, and standard deviation of the CPI column

import pandas as pd

df = pd.DataFrame({"Std Name": ["Aman", "Bobby", "Veeru", "Aanshik", "Aman", "Bobby", "Veeru", "Aanshik"],
  "Roll no": [37, 41, 56, 38, 37, 41, 56, 38],
  "CPI": [85, 92, 78, 95, 85, 92, 78, 95]})

df = df[df["CPI"] > 60]
print(df)

print(df["CPI"].mean())
print(df["CPI"].median())
print(df["CPI"].std())