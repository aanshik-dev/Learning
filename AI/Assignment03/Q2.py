import pandas as pd

df = pd.DataFrame({
  "Subjects": ["Physics", "Physics", "Chemistry", "Maths", "Biology","C", "English", "C"],
  "Book_Authors": ["HC Verma", "Cengage","ML Agarwal", "RD Sharma", "S Chandra", "Kanetkar", "Robinson", "RS Pindick"],
  "No_of_books": [5,3,8,10,6,12,4,8]})

print(df.groupby("Subjects")["No_of_books"].sum())