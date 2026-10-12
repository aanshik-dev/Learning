# Hadoop Docker & MapReduce Complete Lab Guide

---

## 1. Quick Installation & Setup

Your Hadoop cluster configuration files are already set up in this folder:
- [config](file:///d:/Coding/Learning/CloudComputing/Assignment08/config)
- [docker-compose.yaml](file:///d:/Coding/Learning/CloudComputing/Assignment08/docker-compose.yaml)
- [test.sh](file:///d:/Coding/Learning/CloudComputing/Assignment08/test.sh)

### Step 1: Start the Cluster
Open PowerShell in this directory (`d:\Coding\Learning\CloudComputing\Assignment08`) and run:
```powershell
docker compose up -d
```

### Step 2: Verify All 4 Containers are Running
Run:
```powershell
docker ps
```
You will see 4 running containers:
- `assignment08-namenode-1` (Port `9870`)
- `assignment08-datanode-1`
- `assignment08-resourcemanager-1` (Port `8088`)
- `assignment08-nodemanager-1`

### Step 3: Stop the Cluster (When Finished)
```powershell
docker compose down
```

---

## 2. Docker Desktop UI Guide (Buttons & Controls)

If you prefer using the Docker Desktop graphical application:

1. **Left Sidebar -> Containers Tab**:
   - Lists all container stacks. Look for the group titled `assignment08`.
   - Click the arrow `>` next to `assignment08` to expand all 4 services.

2. **Action Icons (Right side of each container row)**:
   - **Play Icon (▶)**: Starts the container if it is stopped.
   - **Square Icon (■)**: Stops the running container.
   - **Circular Arrow Icon (↻)**: Restarts the container.
   - **Trash Icon (🗑)**: Deletes the container.

3. **Terminal / CLI Button (`>_` icon)**:
   - On the row for `assignment08-namenode-1`, click the `>_` icon.
   - This opens a terminal inside Hadoop's master node.

4. **Port Hyperlinks (Direct Browser Access)**:
   - Under the **Port(s)** column for `assignment08-namenode-1`, click `9870:9870` to view the HDFS Web UI in your browser (`http://localhost:9870`).
   - Under `assignment08-resourcemanager-1`, click `8088:8088` to view the YARN Job tracking UI (`http://localhost:8088`).

5. **Container Details Tabs**:
   - Click on the container name `assignment08-namenode-1`:
     - **Logs**: View live daemon messages and errors.
     - **Inspect**: View environment variables, IP addresses, and mounts.
     - **Terminal**: Direct interactive terminal inside the container.
     - **Files**: Inspect directories and files in the container filesystem.

---

## 3. Entering the Hadoop Namenode Terminal

From PowerShell:
```powershell
docker exec -it assignment08-namenode-1 /bin/bash
```

Inside the container, your assignment folder is mapped to `/workspace`:
```bash
cd /workspace
```

---

## 4. Useful HDFS Commands Quick Reference

Run these inside the Namenode terminal:
```bash
hdfs dfs -mkdir -p /sim_input
hdfs dfs -put -f /workspace/input_sim.txt /sim_input/
hdfs dfs -ls /
hdfs dfs -cat /sim_output/part-00000
hdfs dfs -rm -r -f /sim_output
```

Streaming Jar location:
```bash
/opt/hadoop/share/hadoop/tools/lib/hadoop-streaming-3.3.6.jar
```

---

## 5. Lab Section 2: MapReduce Simulation (Word Count)

### Test Input: `input_sim.txt`
```text
hello world
testing testing
hello
```

### Mapper: `mapper_sim.py`
```python
import sys

for line in sys.stdin:
    line = line.strip()
    words = line.split()
    for word in words:
        print("%s\t%s" % (word, 1))
```

### Reducer: `reducer_sim.py`
```python
import sys

current_word = None
current_count = 0

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    word, count = line.split("\t", 1)
    count = int(count)
    if current_word == word:
        current_count += count
    else:
        if current_word:
            print("%s\t%s" % (current_word, current_count))
        current_word = word
        current_count = count

if current_word:
    print("%s\t%s" % (current_word, current_count))
```

### Run Simulation via UNIX Pipe (Inside `/workspace`)
```bash
cat input_sim.txt | python mapper_sim.py | sort | python reducer_sim.py
```

### Run on Hadoop Cluster
```bash
hdfs dfs -mkdir -p /sim_input
hdfs dfs -put -f /workspace/input_sim.txt /sim_input/
hdfs dfs -rm -r -f /sim_output

hadoop jar /opt/hadoop/share/hadoop/tools/lib/hadoop-streaming-3.3.6.jar \
  -files /workspace/mapper_sim.py,/workspace/reducer_sim.py \
  -input /sim_input/input_sim.txt \
  -output /sim_output \
  -mapper "python mapper_sim.py" \
  -reducer "python reducer_sim.py"

hdfs dfs -cat /sim_output/part-00000
```

---

## 6. Assignment Task 1: Distinct Words with Data Cleaning

### Problem Requirements
- Find all distinct words in the input.
- Mapper removes all punctuation and converts all words to lowercase.

### Mapper: `task1_mapper.py`
```python
import sys
import re

for line in sys.stdin:
    line = re.sub(r'[^\w\s]', ' ', line)
    line = line.lower().strip()
    words = line.split()
    for word in words:
        if word:
            print("%s\t1" % word)
```

### Reducer: `task1_reducer.py`
```python
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
```

### Run Task 1 Simulation
```bash
cat input_sim.txt | python task1_mapper.py | sort | python task1_reducer.py
```

### Run Task 1 on Hadoop
```bash
hdfs dfs -rm -r -f /task1_output

hadoop jar /opt/hadoop/share/hadoop/tools/lib/hadoop-streaming-3.3.6.jar \
  -files /workspace/task1_mapper.py,/workspace/task1_reducer.py \
  -input /sim_input/input_sim.txt \
  -output /task1_output \
  -mapper "python task1_mapper.py" \
  -reducer "python task1_reducer.py"

hdfs dfs -cat /task1_output/part-00000
```

---

## 7. Assignment Task 2: Word Count with Combiner

### Problem Requirements
- Extend word count using a combiner script with the `-combiner combiner.py` parameter.

### Mapper: `task2_mapper.py`
```python
import sys

for line in sys.stdin:
    line = line.strip()
    words = line.split()
    for word in words:
        print("%s\t1" % word)
```

### Combiner: `task2_combiner.py`
```python
import sys

current_word = None
current_count = 0

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    word, count = line.split("\t", 1)
    count = int(count)
    if current_word == word:
        current_count += count
    else:
        if current_word:
            print("%s\t%s" % (current_word, current_count))
        current_word = word
        current_count = count

if current_word:
    print("%s\t%s" % (current_word, current_count))
```

### Reducer: `task2_reducer.py`
```python
import sys

current_word = None
current_count = 0

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    word, count = line.split("\t", 1)
    count = int(count)
    if current_word == word:
        current_count += count
    else:
        if current_word:
            print("%s\t%s" % (current_word, current_count))
        current_word = word
        current_count = count

if current_word:
    print("%s\t%s" % (current_word, current_count))
```

### Run Task 2 Simulation
```bash
cat input_sim.txt | python task2_mapper.py | sort | python task2_combiner.py | sort | python task2_reducer.py
```

### Run Task 2 on Hadoop
```bash
hdfs dfs -rm -r -f /task2_output

hadoop jar /opt/hadoop/share/hadoop/tools/lib/hadoop-streaming-3.3.6.jar \
  -files /workspace/task2_mapper.py,/workspace/task2_combiner.py,/workspace/task2_reducer.py \
  -input /sim_input/input_sim.txt \
  -output /task2_output \
  -mapper "python task2_mapper.py" \
  -combiner "python task2_combiner.py" \
  -reducer "python task2_reducer.py"

hdfs dfs -cat /task2_output/part-00000
```

---

## 8. Assignment Task 3: K-Means Nearest Candidate Point on Iris Dataset

### Candidate Points
- Point 0: `(5.8, 4.0)`
- Point 1: `(6.1, 2.8)`
- Point 2: `(6.3, 2.7)`

### Mapper: `task3_mapper.py`
```python
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
```

### Reducer: `task3_reducer.py`
```python
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
```

### Run Task 3 Simulation
```bash
cat iris.data | python task3_mapper.py | sort | python task3_reducer.py
```

### Run Task 3 on Hadoop
```bash
hdfs dfs -mkdir -p /iris_input
hdfs dfs -put -f /workspace/iris.data /iris_input/
hdfs dfs -rm -r -f /task3_output

hadoop jar /opt/hadoop/share/hadoop/tools/lib/hadoop-streaming-3.3.6.jar \
  -files /workspace/task3_mapper.py,/workspace/task3_reducer.py \
  -input /iris_input/iris.data \
  -output /task3_output \
  -mapper "python task3_mapper.py" \
  -reducer "python task3_reducer.py"

hdfs dfs -cat /task3_output/part-00000
```
