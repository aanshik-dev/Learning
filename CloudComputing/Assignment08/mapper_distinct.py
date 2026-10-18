# Name: Ansik Singh Tomar
# Roll No: 2401037

import sys
import string

# Read input line by line from standard input
for line in sys.stdin:

    line = line.strip()    # Remove leading and trailing whitespace
    line = line.translate(str.maketrans('', '', string.punctuation))   # Remove punctuations
    line = line.lower()    # Convert all characters to lowercase
    words = line.split()    # Split the line into individual words

    # Emit each word with a count of 1
    for word in words:
        if word:
            print(f"{word}\t1")
