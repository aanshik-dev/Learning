student_grade = {
  "Abhi": 85,
  "Bobby": 92,
  "Veeru": 78,
  "Aman": 95,
  "Aanshik": 100
}

print(student_grade["Aanshik"])
student_grade["Ram"] = 100
student_grade["Veeru"] = 98

for key, value in student_grade.items():
  if(value > 90):
    print(key, value)

print(student_grade)