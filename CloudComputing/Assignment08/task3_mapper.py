import sys
import math

centers = [
    (0, 5.8, 4.0),
    (1, 6.1, 2.8),
    (2, 6.3, 2.7)
]

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    parts = line.split(",")
    if len(parts) < 2:
        continue
    try:
        sl = float(parts[0])
        sw = float(parts[1])
    except ValueError:
        continue

    min_dist = float("inf")
    best_cluster = None
    for cid, cx, cy in centers:
        dist = math.sqrt((sl - cx) ** 2 + (sw - cy) ** 2)
        if dist < min_dist:
            min_dist = dist
            best_cluster = cid

    print("%d\t%f,%f,1" % (best_cluster, sl, sw))
