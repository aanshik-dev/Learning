file = open("./Learning/AI/0Lab/Assignment02/text.txt", "w+")
file.write("A girl is playing there badminton.\nThe scenery is beautiful.\nThe birds are flying in the sky.\nThe sky is cloudy.\nAlphabets consists of vowels and consonants.")

file.seek(0)
text = file.read()
strs = text.split("\n")

def count_lines_not_starting_with_T(strs):
  count = 0
  for i in strs:
    if i[0] != "T":
      count += 1
  return count

print(count_lines_not_starting_with_T(strs))

file.close()