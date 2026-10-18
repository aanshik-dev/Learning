# Name: Ansik Singh Tomar
# Roll No: 2401037

import sys

current_word = None
# Read input line by line from standard input
for line in sys.stdin:
    
    line = line.strip()    # Remove leading and trailing whitespace
    if not line:
        continue    # Skip empty line
    parts = line.split('\t')    # Split line using tab separator
    word = parts[0]    # Extract word from first part

    # Print the word only if it is different from the previous word
    if word != current_word:
        current_word = word
        print(current_word)