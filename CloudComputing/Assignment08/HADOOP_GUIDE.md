# CS351 - Cloud Computing: Lab Assignment 8 Step-by-Step Manual Guide
**Hadoop MapReduce with Hadoop Streaming API (Python) using Docker Desktop**

---

## Table of Contents
1. [Overview & Assignment Guidelines](#1-overview--assignment-guidelines)
2. [Prerequisites & First-Time Docker Desktop Setup](#2-prerequisites--first-time-docker-desktop-setup)
3. [Setting Up the Multi-Container Hadoop Cluster](#3-setting-up-the-multi-container-hadoop-cluster)
4. [HDFS Core Commands Cheat Sheet](#4-hdfs-core-commands-cheat-sheet)
5. [Understanding Hadoop Streaming with Python](#5-understanding-hadoop-streaming-with-python)
6. [Section 2: Word Count Simulation (Practice Walkthrough)](#6-section-2-word-count-simulation-practice-walkthrough)
7. [Task 1: Distinct Words with Data Cleaning (Graded)](#7-task-1-distinct-words-with-data-cleaning-graded)
8. [Task 2: Word Count with Combiner (Graded)](#8-task-2-word-count-with-combiner-graded)
9. [Task 3: K-Means Clustering on Iris Dataset (Graded)](#9-task-3-k-means-clustering-on-iris-dataset-graded)
10. [Shutting Down & Docker Housekeeping](#10-shutting-down--docker-housekeeping)
11. [Troubleshooting & Common Pitfalls](#11-troubleshooting--common-pitfalls)
12. [Final Submission Checklist](#12-final-submission-checklist)

---

## 1. Overview & Assignment Guidelines

### Objective
In this assignment, you will implement distributed MapReduce algorithms using **Hadoop Streaming API** and **Python**:
1. **Local Simulation**: Test mappers and reducers using standard UNIX pipes (`cat | mapper | sort | reducer`).
2. **Task 1 (Graded)**: Extract all **distinct words** from text, cleaning punctuation and lowercasing.
3. **Task 2 (Graded)**: Implement Word Count with an intermediate **Combiner** (`-combiner`).
4. **Task 3 (Graded)**: Perform **1-iteration of K-Means clustering** on the Iris dataset (Sepal Length & Sepal Width) using 3 predefined candidate points.

### Mandatory Submission Rules
- **Header format**: Every Python source file must begin with:
  ```python
  # Name: <Your Name>
  # Roll No: <Your Roll No>
  ```
- **Comments**: Include clear comments explaining each code block, function inputs/outputs, and operational logic.
- **Variable/Function naming**: Use descriptive, readable names (e.g., `calculate_euclidean_distance`, `nearest_candidate_index`).
- **Screenshots**:
  - Take clear, legible screenshots showing the commands, running jobs, and output results.
  - Resize/compress images if necessary.
  - Upload raw image files directly to Google Classroom (**Do NOT upload a `.zip` file**).

---

## 2. Prerequisites & First-Time Docker Desktop Setup

If this is your first time using Docker Desktop, follow these setup steps:

### 2.1 Verify Docker Desktop is Running
1. Open **Docker Desktop** from the Windows Start menu.
2. Look at the bottom-left corner of the Docker Desktop window:
   - Ensure the icon is **Green** (indicating the Docker engine is running).
3. Open **PowerShell** or **Command Prompt** and verify the installation:
   ```powershell
   docker --version
   docker compose version
   ```
   Both commands should output their installed versions without errors.

### 2.2 Important Windows Gotcha: Line Endings (`LF` vs `CRLF`)
Windows text editors save files with Carriage Return + Line Feed (`\r\n` / CRLF). Linux containers expect Line Feed only (`\n` / LF).
- If your Python scripts have CRLF endings, Linux will throw errors like `/usr/bin/env: 'python3\r': no such file or directory`.
- **Fix in VS Code**: At the bottom-right status bar of VS Code, click on **CRLF** and change it to **LF** before saving your `.py` and `.sh` files.

---

## 3. Setting Up the Multi-Container Hadoop Cluster

We will deploy a 4-service Hadoop cluster using the official Apache Hadoop 3 Docker image:
- **`namenode`**: Master node managing HDFS metadata (Web UI: `http://localhost:9870`).
- **`datanode`**: Worker node storing actual data blocks.
- **`resourcemanager`**: Master node for YARN distributed processing (Web UI: `http://localhost:8088`).
- **`nodemanager`**: Worker node executing compute tasks.

### Step 3.1: Create Configuration Files in `Assignment08`

Navigate to `d:\Coding\Learning\CloudComputing\Assignment08`.

#### 1. Create `config`
Create a file named `config` (no file extension) and paste the exact Hadoop configuration:

```ini
CORE-SITE.XML_fs.default.name=hdfs://namenode
CORE-SITE.XML_fs.defaultFS=hdfs://namenode
HDFS-SITE.XML_dfs.namenode.rpc-address=namenode:8020
HDFS-SITE.XML_dfs.replication=1
MAPRED-SITE.XML_mapreduce.framework.name=yarn
MAPRED-SITE.XML_yarn.app.mapreduce.am.env=HADOOP_MAPRED_HOME=$HADOOP_HOME
MAPRED-SITE.XML_mapreduce.map.env=HADOOP_MAPRED_HOME=$HADOOP_HOME
MAPRED-SITE.XML_mapreduce.reduce.env=HADOOP_MAPRED_HOME=$HADOOP_HOME
YARN-SITE.XML_yarn.resourcemanager.hostname=resourcemanager
YARN-SITE.XML_yarn.nodemanager.pmem-check-enabled=false
YARN-SITE.XML_yarn.nodemanager.delete.debug-delay-sec=600
YARN-SITE.XML_yarn.nodemanager.vmem-check-enabled=false
YARN-SITE.XML_yarn.nodemanager.aux-services=mapreduce_shuffle
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.maximum-applications=10000
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.maximum-am-resource-percent=0.1
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.resource-calculator=org.apache.hadoop.yarn.util.resource.DefaultResourceCalculator
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.root.queues=default
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.root.default.capacity=100
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.root.default.user-limit-factor=1
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.root.default.maximum-capacity=100
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.root.default.state=RUNNING
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.root.default.acl_submit_applications=*
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.root.default.acl_administer_queue=*
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.node-locality-delay=40
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.queue-mappings=
CAPACITY-SCHEDULER.XML_yarn.scheduler.capacity.queue-mappings-override.enable=false
```

#### 2. Create `test.sh`
Create a helper script `test.sh` (make sure line endings are **LF**):
```bash
#!/bin/bash
echo "Hadoop test script initialized"
```

#### 3. Create `docker-compose.yaml`
Create `docker-compose.yaml`:

```yaml
version: "2"
services:
  namenode:
    image: apache/hadoop:3
    hostname: namenode
    container_name: namenode
    command: ["hdfs", "namenode"]
    ports:
      - "9870:9870"
    env_file:
      - ./config
    environment:
      ENSURE_NAMENODE_DIR: "/tmp/hadoop-root/dfs/name"
  datanode:
    image: apache/hadoop:3
    container_name: datanode
    command: ["hdfs", "datanode"]
    env_file:
      - ./config
  resourcemanager:
    image: apache/hadoop:3
    hostname: resourcemanager
    container_name: resourcemanager
    command: ["yarn", "resourcemanager"]
    ports:
      - "8088:8088"
    env_file:
      - ./config
    volumes:
      - ./test.sh:/opt/test.sh
  nodemanager:
    image: apache/hadoop:3
    container_name: nodemanager
    command: ["yarn", "nodemanager"]
    env_file:
      - ./config
```

---

### Step 3.2: Pull and Start Containers

In PowerShell, inside `d:\Coding\Learning\CloudComputing\Assignment08`:

```powershell
# 1. Pull the official Hadoop 3 image
docker pull apache/hadoop:3

# 2. Launch cluster in the background
docker compose up -d

# 3. Check status of all 4 containers (all should say 'Up')
docker compose ps
```

### Step 3.3: Verify Hadoop Web Dashboards
Open your browser and navigate to:
- **HDFS NameNode UI**: [http://localhost:9870](http://localhost:9870)
  - You will see cluster overview, live datanodes, storage capacity.
- **YARN ResourceManager UI**: [http://localhost:8088](http://localhost:8088)
  - You will see scheduler, active nodes, and job execution logs.
*(Take a screenshot of `http://localhost:9870` showing 1 Live Node for your lab record).*

---

### Step 3.4: Log into the NameNode Container
All commands, HDFS operations, and MapReduce jobs will be run inside the `namenode` container.

Run in PowerShell:
```powershell
docker exec -it namenode bash
```
You are now inside the Linux shell of the Hadoop NameNode (`[hadoop@namenode ~]$` or root).

Inside the container, check Python availability:
```bash
python3 --version
```

> [!IMPORTANT]
> ### Why `python3` installation fails by default in `apache/hadoop:3`:
> 1. **Permission Denied**: The container defaults to the non-root user `hadoop`. You must execute commands as root (`-u 0`).
> 2. **CentOS 7 EOL Mirrors**: `apache/hadoop:3` is based on **CentOS 7**, which reached End-of-Life on June 30, 2024. Official mirror URLs are offline and will throw `Cannot find a valid baseurl` or `Could not resolve host: mirrorlist.centos.org`.
>
> ### Working Solution (Run from your Windows PowerShell):
> Run these one-liners in PowerShell to install Python 3 on both `namenode` and `nodemanager` (worker nodes need Python 3 to run map/reduce tasks):
>
> ```powershell
> # 1. Install Python 3 on NameNode (as root with vault mirrors):
> docker exec -u 0 namenode bash -c "sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-* && yum install -y python3"
>
> # 2. Install Python 3 on NodeManager (Worker node where tasks run):
> docker exec -u 0 nodemanager bash -c "sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* && sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-* && yum install -y python3"
> ```
>
> After running these, verify inside the container:
> ```bash
> python3 --version
> # Output: Python 3.6.8
> ```

---

## 4. HDFS Core Commands Cheat Sheet

HDFS (Hadoop Distributed File System) has its own virtual filesystem separate from the Linux container's local disk.

| Action | HDFS Command | Description |
| :--- | :--- | :--- |
| **Make Directory** | `hdfs dfs -mkdir -p /user/root/input` | Creates nested directory inside HDFS |
| **List Directory** | `hdfs dfs -ls /user/root/input` | Lists files stored in HDFS |
| **Upload File** | `hdfs dfs -put <local_path> <hdfs_path>` | Copies file from container to HDFS |
| **Read File Content** | `hdfs dfs -cat <hdfs_path>` | Prints file contents from HDFS to stdout |
| **Download File** | `hdfs dfs -get <hdfs_path> <local_path>` | Copies file from HDFS to container disk |
| **Delete Directory** | `hdfs dfs -rm -r -skipTrash <hdfs_path>` | Recursively deletes HDFS folder |

> [!IMPORTANT]
> **CRITICAL HADOOP RULE**: Hadoop will **FAIL** with an `Output directory already exists` error if your output folder already exists in HDFS.
> **Always delete previous output before re-running a job**:
> ```bash
> hdfs dfs -rm -r -skipTrash /user/root/output
> ```

---

## 5. Understanding Hadoop Streaming with Python

### How it works
1. **Mapper**: Reads line-by-line from standard input (`sys.stdin`), transforms data, and prints key-value pairs separated by tabs or commas to standard output (`print(f"{key}\t{value}")`).
2. **Shuffle & Sort**: Hadoop automatically partitions, transmits, and sorts all mapper outputs alphabetically by key.
3. **Reducer**: Reads sorted key-value pairs from `sys.stdin`. Because identical keys arrive consecutively, it aggregates values per key and outputs final results.

### Locating the Hadoop Streaming Jar
To run streaming jobs, locate the streaming jar inside the container:
```bash
# Locate the jar and save it to an environment variable
STREAMING_JAR=$(find / -name "hadoop-streaming*.jar" 2>/dev/null | head -n 1)

# Verify the path
echo $STREAMING_JAR
# Common path in apache/hadoop:3: /opt/hadoop/share/hadoop/tools/lib/hadoop-streaming-3.3.6.jar
```

---

## 6. Section 2: Word Count Simulation (Practice Walkthrough)

Before running on the Hadoop cluster, simulate the MapReduce cycle locally using UNIX pipes as instructed in Section 2 of the assignment.

### 6.1 Sample Files Creation

Create a working directory inside the container or on your host:
```bash
mkdir -p /tmp/wordcount_demo
cd /tmp/wordcount_demo
```

Create a small sample input file `sample.txt`:
```text
hello world
testing testing
hello
```

### 6.2 Word Count Mapper Script: `mapper_sim.py`
```python
#!/usr/bin/env python3
# Name: <Your Name>
# Roll No: <Your Roll No>

"""
Word Count Mapper:
Reads text from standard input, tokenizes words, and spits out 'word,1'.
"""
import sys

def main():
    # Read each line from standard input
    for line in sys.stdin:
        # Strip trailing newlines and whitespace
        clean_line = line.strip()
        if not clean_line:
            continue
        # Split line into individual words
        words = clean_line.split()
        for word in words:
            # Emit key-value pair formatted as 'word,1'
            print(f"{word},1")

if __name__ == "__main__":
    main()
```

**Test the Mapper**:
```bash
chmod +x mapper_sim.py
cat sample.txt | python3 mapper_sim.py
```
**Expected Output**:
```text
hello,1
world,1
testing,1
testing,1
hello,1
```

---

### 6.3 Word Count Reducer Script: `reducer_sim.py`
```python
#!/usr/bin/env python3
# Name: <Your Name>
# Roll No: <Your Roll No>

"""
Word Count Reducer:
Reads sorted 'word,count' pairs from standard input and aggregates total counts.
"""
import sys

def main():
    current_word = None
    current_count = 0

    # Read each line from standard input
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        
        # Split on comma as defined in Section 2 Table 2
        try:
            word, count_str = line.split(",", 1)
            count = int(count_str)
        except ValueError:
            continue

        # If we encounter the same word, accumulate count
        if current_word == word:
            current_count += count
        else:
            # If word changes, emit aggregate for previous word
            if current_word is not None:
                print(f"{current_word},{current_count}")
            current_word = word
            current_count = count

    # Emit the last word
    if current_word is not None:
        print(f"{current_word},{current_count}")

if __name__ == "__main__":
    main()
```

**Simulate MapReduce using UNIX pipes**:
```bash
chmod +x reducer_sim.py
cat sample.txt | python3 mapper_sim.py | sort -t ',' -k1 | python3 reducer_sim.py
```
**Expected Output**:
```text
hello,2
testing,2
world,1
```
*(Take a screenshot of this terminal output).*

---

### 6.4 Run the Simulation on Hadoop Streaming
Now run the same job through the actual Hadoop cluster:

1. **Upload input to HDFS**:
   ```bash
   hdfs dfs -mkdir -p /demo/input
   hdfs dfs -put sample.txt /demo/input/
   ```

2. **Execute Hadoop Streaming Job**:
   ```bash
   # Remove output dir if it exists
   hdfs dfs -rm -r -skipTrash /demo/output

   hadoop jar $STREAMING_JAR \
     -input /demo/input/sample.txt \
     -output /demo/output \
     -mapper "python3 /tmp/wordcount_demo/mapper_sim.py" \
     -reducer "python3 /tmp/wordcount_demo/reducer_sim.py"
   ```

3. **Inspect Output**:
   ```bash
   hdfs dfs -cat /demo/output/part-00000
   ```
*(Take a screenshot of the completed job terminal and the output).*

---

## 7. Task 1: Distinct Words with Data Cleaning (Graded)

### 7.1 Problem Statement
- **Objective**: Implement a MapReduce program to find all **distinct words** in the input file.
- **Data Cleaning Requirement**: In the mapper, remove all punctuation and convert all words to lowercase.
- **Example**:
  - Input:
    ```text
    Hello World!
    Apache hadoop.
    apache spark.
    ```
  - Expected Output:
    ```text
    apache
    hadoop
    hello
    spark
    world
    ```

---

### 7.2 Source Code

#### File 1: `distinct_mapper.py`
```python
#!/usr/bin/env python3
# Name: <Your Name>
# Roll No: <Your Roll No>

"""
Task 1: Distinct Words Mapper
- Cleans data: strips all punctuation and converts characters to lowercase.
- Emits each cleaned word as key with dummy value '1'.
"""
import sys
import string

def clean_and_tokenize(text_line):
    """
    Removes punctuation using str.maketrans and converts to lowercase.
    Returns a list of clean word tokens.
    """
    # Create translation table to remove punctuation
    translator = str.maketrans('', '', string.punctuation)
    clean_text = text_line.translate(translator).lower()
    return clean_text.split()

def main():
    # Process line-by-line from stdin
    for line in sys.stdin:
        words = clean_and_tokenize(line)
        for word in words:
            # Emit key and value separated by tab
            print(f"{word}\t1")

if __name__ == "__main__":
    main()
```

#### File 2: `distinct_reducer.py`
```python
#!/usr/bin/env python3
# Name: <Your Name>
# Roll No: <Your Roll No>

"""
Task 1: Distinct Words Reducer
- Receives sorted (word, 1) pairs.
- Deduplicates words so each distinct word is emitted exactly once.
"""
import sys

def main():
    previous_word = None

    # Read sorted words from stdin
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        
        parts = line.split("\t")
        word = parts[0]

        # Only emit word the first time it is encountered
        if word != previous_word:
            print(word)
            previous_word = word

if __name__ == "__main__":
    main()
```

---

### 7.3 Step-by-Step Execution Guide

#### Step 1: Copy Scripts and Input to Container
If you wrote the files on your Windows machine in `Assignment08`:
1. In Windows PowerShell:
   ```powershell
   cd d:\Coding\Learning\CloudComputing\Assignment08
   docker cp distinct_mapper.py namenode:/tmp/
   docker cp distinct_reducer.py namenode:/tmp/
   ```

2. Create a test input file `distinct_input.txt` on Windows or inside the container:
   ```text
   Hello World!
   Apache hadoop.
   apache spark.
   ```
   Copy it to the container:
   ```powershell
   docker cp distinct_input.txt namenode:/tmp/
   ```

#### Step 2: Test Locally Inside Container (Simulation)
In NameNode container shell (`docker exec -it namenode bash`):
```bash
cd /tmp
chmod +x distinct_mapper.py distinct_reducer.py

# Verify with UNIX pipe
cat distinct_input.txt | python3 distinct_mapper.py | sort | python3 distinct_reducer.py
```
**Verify Output**:
```text
apache
hadoop
hello
spark
world
```

#### Step 3: Run on Hadoop Cluster
```bash
# 1. Create HDFS input folder and upload file
hdfs dfs -mkdir -p /task1/input
hdfs dfs -put -f /tmp/distinct_input.txt /task1/input/

# 2. Remove existing output folder
hdfs dfs -rm -r -skipTrash /task1/output

# 3. Submit Hadoop Streaming Job
hadoop jar $STREAMING_JAR \
  -input /task1/input/distinct_input.txt \
  -output /task1/output \
  -file /tmp/distinct_mapper.py \
  -file /tmp/distinct_reducer.py \
  -mapper "python3 distinct_mapper.py" \
  -reducer "python3 distinct_reducer.py"

# 4. View HDFS Output
hdfs dfs -cat /task1/output/part-00000
```

> [!TIP]
> Notice the `-file` flag! Using `-file /tmp/distinct_mapper.py` packages the script with the Hadoop job and distributes it to all worker nodes in the cluster.

📸 **Screenshots to Take**:
1. Terminal showing the `hadoop jar` execution and completion (`Map 100% Reduce 100%`).
2. Terminal showing `hdfs dfs -cat /task1/output/part-00000` with the distinct words list.

---

## 8. Task 2: Word Count with Combiner (Graded)

### 8.1 Problem Statement & Combiner Concept
- **What is a Combiner?**
  A Combiner is a "mini-reducer" that runs on the mapper node right after the map phase, **before** data is sent over the network to the Reducer.
- **Why use it?**
  It aggregates intermediate results locally (e.g., combining ten `('the', 1)` pairs into one `('the', 10)`), drastically reducing network traffic and disk I/O.
- **Hadoop Streaming Flag**: `-combiner <script>`

---

### 8.2 Source Code

#### File 1: `wc_mapper.py`
```python
#!/usr/bin/env python3
# Name: <Your Name>
# Roll No: <Your Roll No>

"""
Task 2: Word Count Mapper
Reads text lines, cleans punctuation, converts to lowercase, and emits (word, 1).
"""
import sys
import string

def main():
    translator = str.maketrans('', '', string.punctuation)
    for line in sys.stdin:
        clean_line = line.translate(translator).lower().strip()
        if not clean_line:
            continue
        for word in clean_line.split():
            print(f"{word}\t1")

if __name__ == "__main__":
    main()
```

#### File 2: `wc_combiner.py`
```python
#!/usr/bin/env python3
# Name: <Your Name>
# Roll No: <Your Roll No>

"""
Task 2: Word Count Combiner
Runs locally on mapper node. Aggregates intermediate (word, count) pairs 
to reduce network transfer volume.
"""
import sys

def main():
    current_word = None
    current_count = 0

    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        
        parts = line.split("\t")
        if len(parts) != 2:
            continue
            
        word, count_str = parts[0], parts[1]
        try:
            count = int(count_str)
        except ValueError:
            continue

        if current_word == word:
            current_count += count
        else:
            if current_word is not None:
                # Emit intermediate aggregated count
                print(f"{current_word}\t{current_count}")
            current_word = word
            current_count = count

    if current_word is not None:
        print(f"{current_word}\t{current_count}")

if __name__ == "__main__":
    main()
```

#### File 3: `wc_reducer.py`
```python
#!/usr/bin/env python3
# Name: <Your Name>
# Roll No: <Your Roll No>

"""
Task 2: Word Count Reducer
Receives aggregated intermediate counts from all combiners/mappers and 
computes the global total for each word.
"""
import sys

def main():
    current_word = None
    current_count = 0

    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        
        parts = line.split("\t")
        if len(parts) != 2:
            continue

        word, count_str = parts[0], parts[1]
        try:
            count = int(count_str)
        except ValueError:
            continue

        if current_word == word:
            current_count += count
        else:
            if current_word is not None:
                print(f"{current_word}\t{current_count}")
            current_word = word
            current_count = count

    if current_word is not None:
        print(f"{current_word}\t{current_count}")

if __name__ == "__main__":
    main()
```

---

### 8.3 Step-by-Step Execution Guide

#### Step 1: Copy Scripts and Dataset
You can use `big.txt` (from `https://norvig.com/big.txt`) or any sample text file.
In container shell:
```bash
cd /tmp
# Download norvig big.txt directly inside container:
curl -sO https://norvig.com/big.txt
```
Copy your python scripts into the container:
```powershell
# From Windows PowerShell:
docker cp wc_mapper.py namenode:/tmp/
docker cp wc_combiner.py namenode:/tmp/
docker cp wc_reducer.py namenode:/tmp/
```

#### Step 2: Upload Input to HDFS
```bash
hdfs dfs -mkdir -p /task2/input
hdfs dfs -put -f /tmp/big.txt /task2/input/
```

#### Step 3: Run Hadoop Streaming Job with Combiner
```bash
# Clean previous output
hdfs dfs -rm -r -skipTrash /task2/output

# Execute MapReduce with -combiner
hadoop jar $STREAMING_JAR \
  -input /task2/input/big.txt \
  -output /task2/output \
  -file /tmp/wc_mapper.py \
  -file /tmp/wc_combiner.py \
  -file /tmp/wc_reducer.py \
  -mapper "python3 wc_mapper.py" \
  -combiner "python3 wc_combiner.py" \
  -reducer "python3 wc_reducer.py"
```

#### Step 4: Check Results
```bash
# View first 20 word counts
hdfs dfs -cat /task2/output/part-00000 | head -n 20
```

📸 **Screenshots to Take**:
1. Terminal showing `-combiner` in the execution command and job completion.
2. The Hadoop job output counters (note `Combine input records` and `Combine output records` in the job statistics!).
3. First 20 lines of the output file.

---

## 9. Task 3: K-Means Clustering on Iris Dataset (Graded)

### 9.1 Mathematical Formulation & Problem Statement
- **Dataset**: `iris.csv` (150 observations).
  - Format: `sepallength, sepalwidth, petallength, petalwidth, class`
  - Instruction: **Consider only Sepal Length ($x$) and Sepal Width ($y$)**; discard petal dimensions and class.
- **Initial Candidate Points (Centroids)** from Table 4:
  - **Centroid 0**: $(c_{0,x}, c_{0,y}) = (5.8, 4.0)$  *(from 5.8,4.0,1.2,0.2,Iris-setosa)*
  - **Centroid 1**: $(c_{1,x}, c_{1,y}) = (6.1, 2.8)$  *(from 6.1,2.8,4.0,1.3,Iris-versicolor)*
  - **Centroid 2**: $(c_{2,x}, c_{2,y}) = (6.3, 2.7)$  *(from 6.3,2.7,4.9,1.8,Iris-virginica)*

### MapReduce Logic:
1. **Mapper**:
   - For every point $(x, y)$ in `iris.csv`, calculate Euclidean distance to each of the 3 candidate points:
     $$d_i = \sqrt{(x - c_{i,x})^2 + (y - c_{i,y})^2}$$
   - Find cluster $k$ with the minimum distance:
     $$k = \arg\min_i d_i$$
   - Emit: `cluster_id \t x \t y \t 1`
2. **Reducer**:
   - For all points assigned to cluster $k$, calculate the new center by averaging their coordinates:
     $$\text{New } x = \frac{\sum x}{N_k}, \quad \text{New } y = \frac{\sum y}{N_k}$$
   - Output: `Cluster <k> \t Updated Center: (new_x, new_y) \t Assigned Points: <N_k>`

---

### 9.2 Source Code

#### File 1: `kmeans_mapper.py`
```python
#!/usr/bin/env python3
# Name: <Your Name>
# Roll No: <Your Roll No>

"""
Task 3: K-Means Clustering Mapper (Iris Dataset)
- Defines 3 initial candidate centroids for (sepal_length, sepal_width).
- Reads each iris record, extracts sepal_length and sepal_width.
- Finds nearest candidate point using Euclidean distance.
- Emits (cluster_id, sepal_length, sepal_width, 1).
"""
import sys
import math

# Candidate Points defined in Table 4 of Assignment (Sepal Length, Sepal Width)
CANDIDATE_CENTROIDS = [
    (5.8, 4.0),  # Centroid 0: Iris-setosa
    (6.1, 2.8),  # Centroid 1: Iris-versicolor
    (6.3, 2.7)   # Centroid 2: Iris-virginica
]

def euclidean_distance(point_a, point_b):
    """Calculates 2D Euclidean distance between two points."""
    return math.sqrt((point_a[0] - point_b[0])**2 + (point_a[1] - point_b[1])**2)

def find_nearest_centroid(point):
    """Returns index of the nearest centroid from CANDIDATE_CENTROIDS."""
    best_index = 0
    min_dist = float('inf')
    
    for idx, centroid in enumerate(CANDIDATE_CENTROIDS):
        dist = euclidean_distance(point, centroid)
        if dist < min_dist:
            min_dist = dist
            best_index = idx
            
    return best_index

def main():
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
            
        columns = line.split(",")
        # Ensure row has required attributes
        if len(columns) < 2:
            continue

        try:
            # Consider only sepal length and sepal width as specified
            sepal_length = float(columns[0].strip())
            sepal_width = float(columns[1].strip())
        except ValueError:
            # Skips header row if present
            continue

        current_point = (sepal_length, sepal_width)
        nearest_cluster_id = find_nearest_centroid(current_point)

        # Output format: cluster_id \t sepal_length \t sepal_width \t 1
        print(f"{nearest_cluster_id}\t{sepal_length}\t{sepal_width}\t1")

if __name__ == "__main__":
    main()
```

#### File 2: `kmeans_reducer.py`
```python
#!/usr/bin/env python3
# Name: <Your Name>
# Roll No: <Your Roll No>

"""
Task 3: K-Means Clustering Reducer (Iris Dataset)
- Groups all points assigned to each candidate cluster.
- Computes new centroid coordinates by averaging sepal_length and sepal_width.
- Outputs updated candidate points.
"""
import sys

# Initial candidate points for before-and-after comparison
INITIAL_CANDIDATES = {
    0: (5.8, 4.0),
    1: (6.1, 2.8),
    2: (6.3, 2.7)
}

def main():
    current_cluster = None
    sum_length = 0.0
    sum_width = 0.0
    total_count = 0

    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue

        parts = line.split("\t")
        if len(parts) != 4:
            continue

        cluster_id = int(parts[0])
        sl = float(parts[1])
        sw = float(parts[2])
        count = int(parts[3])

        if current_cluster == cluster_id:
            sum_length += sl
            sum_width += sw
            total_count += count
        else:
            # Emit updated centroid for previous cluster
            if current_cluster is not None and total_count > 0:
                avg_sl = round(sum_length / total_count, 4)
                avg_sw = round(sum_width / total_count, 4)
                old = INITIAL_CANDIDATES.get(current_cluster, (0.0, 0.0))
                print(f"Cluster {current_cluster}\tOld Centroid: {old}\tUpdated Centroid: ({avg_sl}, {avg_sw})\tAssigned Points: {total_count}")

            current_cluster = cluster_id
            sum_length = sl
            sum_width = sw
            total_count = count

    # Emit the last cluster
    if current_cluster is not None and total_count > 0:
        avg_sl = round(sum_length / total_count, 4)
        avg_sw = round(sum_width / total_count, 4)
        old = INITIAL_CANDIDATES.get(current_cluster, (0.0, 0.0))
        print(f"Cluster {current_cluster}\tOld Centroid: {old}\tUpdated Centroid: ({avg_sl}, {avg_sw})\tAssigned Points: {total_count}")

if __name__ == "__main__":
    main()
```

---

### 9.3 Step-by-Step Execution Guide

#### Step 1: Copy `iris.csv` and Scripts to Container
Notice `iris.csv` already exists in your workspace: `d:\Coding\Learning\CloudComputing\Assignment08\iris.csv`.

In Windows PowerShell:
```powershell
cd d:\Coding\Learning\CloudComputing\Assignment08
docker cp iris.csv namenode:/tmp/
docker cp kmeans_mapper.py namenode:/tmp/
docker cp kmeans_reducer.py namenode:/tmp/
```

#### Step 2: Test Locally Inside Container (Simulation)
In NameNode container shell (`docker exec -it namenode bash`):
```bash
cd /tmp
chmod +x kmeans_mapper.py kmeans_reducer.py

# Test via UNIX pipe
cat iris.csv | python3 kmeans_mapper.py | sort -k1,1n | python3 kmeans_reducer.py
```
**Verify Local Output**:
You will see 3 clusters with their updated centroids and assigned point counts!

#### Step 3: Run on Hadoop Cluster
```bash
# 1. Put iris.csv to HDFS
hdfs dfs -mkdir -p /task3/input
hdfs dfs -put -f /tmp/iris.csv /task3/input/

# 2. Remove old output
hdfs dfs -rm -r -skipTrash /task3/output

# 3. Submit MapReduce Job
hadoop jar $STREAMING_JAR \
  -input /task3/input/iris.csv \
  -output /task3/output \
  -file /tmp/kmeans_mapper.py \
  -file /tmp/kmeans_reducer.py \
  -mapper "python3 kmeans_mapper.py" \
  -reducer "python3 kmeans_reducer.py"

# 4. View Updated Candidate Points
hdfs dfs -cat /task3/output/part-00000
```

📸 **Screenshots to Take**:
1. Terminal showing the simulation pipe output.
2. Terminal showing the `hadoop jar` execution command and completion.
3. Final output from `hdfs dfs -cat /task3/output/part-00000` showing the 3 updated centroids.

---

## 10. Shutting Down & Docker Housekeeping

When you finish your assignment and have taken all required screenshots:

### 10.1 Exit the Container
```bash
exit
```

### 10.2 Stop Docker Containers
In Windows PowerShell (inside `d:\Coding\Learning\CloudComputing\Assignment08`):
```powershell
docker compose down
```
This stops and cleans up the containers while preserving your host files.

---

## 11. Troubleshooting & Common Pitfalls

| Problem | Cause | Solution |
| :--- | :--- | :--- |
| `Output directory already exists` | Hadoop forbids writing to existing directories | Run `hdfs dfs -rm -r -skipTrash <output_path>` before re-running. |
| `/usr/bin/env: 'python3\r': no such file or directory` | Windows CRLF line endings in `.py` script | Change file line endings in VS Code status bar from **CRLF** to **LF**. |
| `Cannot create directory: Name node is in safe mode` | NameNode starts up in read-only safe mode until datanodes register | Run `hdfs dfsadmin -safemode leave` inside the NameNode container. |
| `Cannot find a valid baseurl` / `Could not resolve host: mirrorlist.centos.org` | CentOS 7 reached EOL on June 30, 2024; yum mirrors are offline | Point repos to `vault.centos.org` and run as root (`-u 0`). See Section 3.4. |
| `Permission denied` when running `yum` | Default container user is non-root (`hadoop`) | Use `docker exec -u 0 ...` to run as root. |
| Container name is `assignment08-namenode-1` instead of `namenode` | Docker Compose assigns default project prefix | Add `container_name: namenode` in `docker-compose.yaml` or use `docker compose ps` to find exact name. |

---

## 12. Final Submission Checklist

Before uploading to Google Classroom, verify:
- [ ] Source files contain **Name** and **Roll No** in the top header.
- [ ] All code blocks and functions have explanatory comments.
- [ ] Local simulation verified for each task.
- [ ] Jobs executed successfully on Hadoop Streaming (`apache/hadoop:3`).
- [ ] Screenshots captured for:
  - [ ] Hadoop Web UI at `localhost:9870`
  - [ ] Task 1 distinct words output
  - [ ] Task 2 word count with combiner output & job stats
  - [ ] Task 3 K-Means updated centroids output
- [ ] Screenshots uploaded directly (no `.zip` files).
