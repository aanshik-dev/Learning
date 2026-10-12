import sys

current_cluster = None
total_sl = 0.0
total_sw = 0.0
total_points = 0

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    cluster_id_str, val_str = line.split("\t", 1)
    cluster_id = int(cluster_id_str)
    sl_str, sw_str, count_str = val_str.split(",")
    sl = float(sl_str)
    sw = float(sw_str)
    count = int(count_str)

    if current_cluster == cluster_id:
        total_sl += sl
        total_sw += sw
        total_points += count
    else:
        if current_cluster is not None and total_points > 0:
            avg_sl = total_sl / total_points
            avg_sw = total_sw / total_points
            print("Cluster_%d\tnew_centroid=(%.4f, %.4f)\tassigned_points=%d" % (current_cluster, avg_sl, avg_sw, total_points))
        current_cluster = cluster_id
        total_sl = sl
        total_sw = sw
        total_points = count

if current_cluster is not None and total_points > 0:
    avg_sl = total_sl / total_points
    avg_sw = total_sw / total_points
    print("Cluster_%d\tnew_centroid=(%.4f, %.4f)\tassigned_points=%d" % (current_cluster, avg_sl, avg_sw, total_points))
