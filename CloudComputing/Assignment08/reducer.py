# Name: Ansik Singh Tomar
# Roll No: 2401037

import sys

current_word = None
current_count = 0

# Read sorted lines from standard input
for line in sys.stdin:
    line = line.strip()    # Remove leading and trailing whitespace
    if not line:
        continue    # Skip empty lines
    parts = line.split(',')    # Split input line at comma
    if len(parts) != 2:
        continue    # Skip lines that do not contain exactly two parts

    word, count = parts[0], int(parts[1])
    # If the word matches the current word, add its count
    if current_word == word:
        current_count += count
    else:
        # Print the total count of the previous word
        if current_word:
            print(f"{current_word},{current_count}")

        # Start counting the new word
        current_word = word
        current_count = count

# Print the total count of the last word
if current_word == word:
    print(f"{current_word},{current_count}")