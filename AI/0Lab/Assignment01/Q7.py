person = {
  'firstname': 'John',
  'lastname': 'Doe',
  'age': 25,
  'favourite_color': ['blue', 'green'],
  'active': True
}
print(person)
print(list(person.keys()))
print(list(person.values()))
print(list(person.items()))

keys_list = list(person.keys())
second_key = keys_list[1]
print(person[second_key])