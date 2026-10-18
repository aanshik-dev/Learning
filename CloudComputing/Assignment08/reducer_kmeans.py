# Name: Ansik Singh Tomar
# Roll No: 2401037

import sys

current_cluster = None
sum_sl = 0.0
sum_sw = 0.0
count = 0

# Read input line by line from standard input
for line in sys.stdin:

    line = line.strip()    # Remove leading and trailing whitespace
    if not line:
        continue    # Skip empty lines
    cluster, coords = line.split('\t')    # cluster ID and coordinates
    sl, sw = map(float, coords.split(','))

    # If the point belongs to the current cluster, update its sums and count
    if current_cluster == cluster:
        sum_sl += sl
        sum_sw += sw
        count += 1

    else:
        # Print the average coordinates for the previous cluster
        if current_cluster:
            avg_sl = sum_sl / count
            avg_sw = sum_sw / count
            print(f"{current_cluster}\tUpdated Candidate Point: ({avg_sl:.2f}, {avg_sw:.2f})\tTotal Points Assigned: {count}")

        # Start processing the new cluster
        current_cluster = cluster
        sum_sl = sl
        sum_sw = sw
        count = 1

# Print the average coordinates for the last cluster
if current_cluster == cluster:
    avg_sl = sum_sl / count
    avg_sw = sum_sw / count
    print(f"{current_cluster}\tUpdated Candidate Point: ({avg_sl:.2f}, {avg_sw:.2f})\tTotal Points Assigned: {count}")