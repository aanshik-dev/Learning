ls = [{
  "name": "Aanshik",
  "id": 37,
  "grades": [90, 80, 85]
},
{
  "name": "Aman",
  "id": 38,
  "grades": [95,88,60]
},
{
  "name": "Bobby",
  "id": 41,
  "grades": [89,82,75]
},
{
  "name": "Veeru",
  "id": 56,
  "grades": [85,90,75]
}]

def process_student_data(lsd):
  avg = {}
  for student in lsd:
    avg[student["id"]] = sum(student["grades"]) / len(student["grades"])
  return avg

print(process_student_data(ls))