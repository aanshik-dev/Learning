import sys

current_word = None

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    parts = line.split("\t", 1)
    word = parts[0]
    if current_word != word:
        if current_word is not None:
            print(current_word)
        current_word = word

if current_word is not None:
    print(current_word)
