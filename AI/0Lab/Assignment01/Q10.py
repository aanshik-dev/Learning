def unique(list1):
  unique_list = []
  for x in list1:
    if x not in unique_list:
      unique_list.append(x)
  return unique_list

list1 = [10, 20, 30, 20, 20, 30, 40, 50, -20, 60, 60, -20, -20]
print(unique(list1))