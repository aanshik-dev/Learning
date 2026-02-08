import pandas as pd

df = pd.DataFrame({"Std Name": ["Aanshik", "Abhi", "Veeru", "Aditya", "Virat", "Sachin", "Karan", "Rohit"],
  "Roll no": [37, 41, 56, 38, 37, 41, 56, 38],
  "CPI": [98, 56, 88, 95, 33, 92, 47, 86]})

print(df)


mask = df[df["CPI"] > 60]
print(mask)

print(df["CPI"].mean())
print(df["CPI"].median())
print(df["CPI"].std())