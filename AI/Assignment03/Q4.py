import pandas as pd

dirty = pd.DataFrame({"Name": ["Aanshik", "Abhi", "Veeru", "Aditya", "Virat", "Sachin", "Karan", "Rohit"],
  "Age": [21,18,16,22,25,20,19,17],
  "Salary": [98, 56, 88.9, -95, 33.6, 92, -47.5, 86]})

print(dirty)
print("")

df = dirty[(dirty["Age"] >= 18) & (dirty["Salary"] >= 0)]
print(df)