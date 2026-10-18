# Name: Ansik Singh Tomar
# Roll No: 2401037

import sys
import math

# cluster centroids
CANDIDATES = {
    "C1": (5.8, 4.0),
    "C2": (6.1, 2.8),
    "C3": (6.3, 2.7)
}

# Euclidean distance between two points
def euclidean_distance(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

# Read input data line by line from standard input
for line in sys.stdin:

    line = line.strip()    # Remove leading and trailing whitespace
    if not line:  
        continue    # Skip empty lines
    parts = line.split(',')    # Split the line at comma

    # Process the line only if it contains at least two values
    if len(parts) >= 2:
        try:
            # Convert the first two values into floating-point numbers
            sl = float(parts[0])
            sw = float(parts[1])
            point = (sl, sw)

            # Initialize the minimum distance and assigned cluster
            min_dist = float('inf')
            assigned_cluster = None

            # Calculate the distance from the point to each candidate centroid
            for cluster_id, coords in CANDIDATES.items():
                dist = euclidean_distance(point, coords)

                # Update the nearest cluster if a smaller distance is found
                if dist < min_dist:
                    min_dist = dist
                    assigned_cluster = cluster_id

            # Output the cluster ID and the original data point, separated by a tab
            print(f"{assigned_cluster}\t{sl},{sw}")

        except ValueError:
            continue