inventory = {
  'pens': 15,
  'notebooks': 25,
  'pencils': 40,
  'markers': 30,
  'highlighters': 35
}

print(list(inventory.items()))
print(list(inventory.values()))

if("pens" in inventory):
  print("Found")
else:
  print("Not Found")