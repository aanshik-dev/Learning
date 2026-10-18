# Name: Ansik Singh Tomar
# Roll No: 2401037

import sys

current_word = None
current_count = 0

# Read input line by line from standard input
for line in sys.stdin:

    line = line.strip()    # Remove leading and trailing whitespace
    if not line:
        continue    # Skip empty lines
    word, count = line.split('\t')    # Split line into words at tab
    count = int(count)    # string to integer

    # If the word matches the current word, add its count
    if current_word == word:
        current_count += count
    else:
        # Print the total count of the previous word
        if current_word:
            print(f"{current_word}\t{current_count}")

        # Start counting the new word
        current_word = word
        current_count = count

# Print the total count of the last word
if current_word == word:
    print(f"{current_word}\t{current_count}")