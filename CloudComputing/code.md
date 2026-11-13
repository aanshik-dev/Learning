# 📝 Cloud Computing Lab Endsem - Pen & Paper Code Compendium

> **Complete, exact, and hand-writeable code blocks & snippets from Lab Assignments 1 to 9.**
> Formatted specifically for writing down accurately during a pen-and-paper examination.

---

## 📌 Quick Reference: Most Repeated Pen-Paper One-Liners

```python
import boto3
ec2 = boto3.client("ec2", region_name="ap-south-1")
s3  = boto3.client("s3",  region_name="ap-south-1")
rds = boto3.client("rds", region_name="ap-south-1")
eb  = boto3.client("elasticbeanstalk", region_name="ap-south-1")

# 1. Launch EC2 instance
ec2.run_instances(ImageId="ami-01a00762f46d584a1", InstanceType="t3.micro", MinCount=1, MaxCount=1)

# 2. Upload file to S3
s3.upload_file("local.txt", "my-bucket", "remote.txt")

# 3. Create S3 Bucket (ap-south-1 requires LocationConstraint; us-east-1 does not)
s3.create_bucket(Bucket="my-bucket", CreateBucketConfiguration={"LocationConstraint": "ap-south-1"})

# 4. Describe Running EC2 Instances
ec2.describe_instances(Filters=[{"Name": "instance-state-name", "Values": ["running"]}])

# 5. Get Public IP of EC2
res = ec2.describe_instances(InstanceIds=["i-1234567890abcdef0"])
ip = res["Reservations"][0]["Instances"][0]["PublicIpAddress"]

# 6. Stop and Terminate EC2
ec2.stop_instances(InstanceIds=["i-xxx"])
ec2.terminate_instances(InstanceIds=["i-xxx"])

# 7. Important Waiters
ec2.get_waiter("instance_running").wait(InstanceIds=["i-xxx"])
ec2.get_waiter("instance_stopped").wait(InstanceIds=["i-xxx"])
ec2.get_waiter("instance_terminated").wait(InstanceIds=["i-xxx"])
rds.get_waiter("db_instance_available").wait(DBInstanceIdentifier="db-xxx")
```

---

# 1️⃣ Assignment 1: Python Warmup & Functional Programming

### 1.1 Custom Class with `apply()` Method & Exception Handling

```python
class AtomicList:
    def __init__(self, *values):
        # Store arbitrary items as list
        self.values = list(values)

    def apply(self, func):
        try:
            # .copy() ensures the original instance variable is not modified
            return func(self.values.copy())
        except Exception as e:
            raise Exception(f"Error while applying function: {e}")

# Usage:
al = AtomicList(1, 2, 6, 5, 4)
result = al.apply(lambda x: [i * 2 for i in x])  # [2, 4, 12, 10, 8]
```

### 1.2 `map()` and `functools.reduce()`

```python
import functools

# map: Upper-case all words in a list
def upper(words):
    return list(map(lambda x: x.upper(), words))

# reduce: Compute product of all numbers in a list
def product(numbers):
    return functools.reduce(lambda x, y: x * y, numbers)

# Example:
# upper(["hello", "world"]) -> ['HELLO', 'WORLD']
# product([1, 2, 3, 4, 5])   -> 120
```

### 1.3 Comprehensions, Dictionaries, and Sets

```python
# List comprehension (squares of 0 to n-1)
def sqr(n):
    return [x**2 for x in range(n)]

# Dictionary comprehension (number -> square)
def sqrMap(n):
    return {x: x**2 for x in range(n)}

# Dictionary with even numbers mapped to [square, cube]
def sq_Cube(n):
    return {x: [x**2, x**3] for x in range(0, n, 2)}

# Pair consecutive elements from two lists using zip
def tupList(l1, l2):
    return list(zip(l1, l2))

# Frequency count using dict
def get_frequency(lst):
    freq = {}
    for item in lst:
        freq[item] = freq.get(item, 0) + 1
    return freq

# First repeating element using set
def repeating(lst):
    seen = set()
    for item in lst:
        if item in seen:
            return item
        seen.add(item)
    return None
```

---

# 2️⃣ Assignment 2: AWS S3 & EC2 CLI & Bucket Policies

### 2.1 Essential AWS CLI Commands

```bash
# S3 Bucket Creation
aws s3 mb s3://my-web-bucket --region ap-south-1

# Upload a single file
aws s3 cp index.html s3://my-web-bucket/

# Recursively sync website directory to S3
aws s3 sync ./website s3://my-web-bucket --acl public-read

# Enable Static Website Hosting
aws s3 website s3://my-web-bucket/ --index-document index.html --error-document error.html

# Launch EC2 instance via CLI
aws ec2 run-instances --image-id ami-01a00762f46d584a1 --count 1 \
  --instance-type t3.micro --key-name my-key --security-group-ids sg-xxxx
```

### 2.2 S3 Bucket Policy for Public Static Website (JSON)

```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Sid": "PublicReadGetObject",
      "Effect": "Allow",
      "Principal": "*",
      "Action": "s3:GetObject",
      "Resource": "arn:aws:s3:::my-web-bucket/*"
    }
  ]
}
```

---

# 3️⃣ Assignment 3: Boto3 S3 & EC2 Integration

### 3.1 Create S3 Bucket and Upload Entire Directory Recursively

```python
import boto3
import os

bucket_name = "my-web-bucket-2401037"
region = "ap-south-1"

s3 = boto3.client("s3", region_name=region)

# Create Bucket (LocationConstraint required outside us-east-1)
s3.create_bucket(
    Bucket=bucket_name,
    CreateBucketConfiguration={"LocationConstraint": region}
)

# Recursive upload of directory
web_dir = "./website"
for root, dirs, files in os.walk(web_dir):
    for file in files:
        file_path = os.path.join(root, file)
        # S3 key maintains directory structure using forward slashes
        s3_key = os.path.relpath(file_path, web_dir).replace(os.sep, "/")
        s3.upload_file(file_path, bucket_name, s3_key)
        print(f"Uploaded: {s3_key}")
```

### 3.2 Launch EC2 Instance with UserData & Wait for Running

```python
import boto3

region = "ap-south-1"
ec2 = boto3.client("ec2", region_name=region)

# Startup script to install Apache and sync website from S3
startup_script = """#!/bin/bash
apt-get update -y
apt-get install -y apache2 awscli
systemctl start apache2
systemctl enable apache2
rm -rf /var/www/html/*
aws s3 cp s3://my-web-bucket-2401037/ /var/www/html/ --recursive
chown -R www-data:www-data /var/www/html
chmod -R 755 /var/www/html
"""

# Launch EC2 instance
response = ec2.run_instances(
    ImageId="ami-01a00762f46d584a1",
    InstanceType="t3.micro",
    MinCount=1,
    MaxCount=1,
    UserData=startup_script,
    IamInstanceProfile={"Name": "my-s3-access-role"}  # Grants S3 read permission
)

instance_id = response["Instances"][0]["InstanceId"]
print(f"Launched Instance: {instance_id}")

# Wait until running
waiter = ec2.get_waiter("instance_running")
waiter.wait(InstanceIds=[instance_id])

# Fetch Public IP and Public DNS
desc = ec2.describe_instances(InstanceIds=[instance_id])
inst = desc["Reservations"][0]["Instances"][0]
print(f"Public IP:  {inst.get('PublicIpAddress')}")
print(f"Public DNS: {inst.get('PublicDnsName')}")
```

### 3.3 IMDSv2 Instance Metadata Retrieval Script (Inside EC2)

```bash
#!/bin/bash
# 1. Fetch IMDSv2 session token (TTL = 21600 seconds)
TOKEN=$(curl -s -X PUT "http://169.254.169.254/latest/api/token" \
  -H "X-aws-ec2-metadata-token-ttl-seconds: 21600")

# 2. Query instance metadata using token
INSTANCE_ID=$(curl -s -H "X-aws-ec2-metadata-token: $TOKEN" \
  "http://169.254.169.254/latest/meta-data/instance-id")

PUBLIC_IP=$(curl -s -H "X-aws-ec2-metadata-token: $TOKEN" \
  "http://169.254.169.254/latest/meta-data/public-ipv4")

# Inject dynamically into webpage
sed -i "s/{{INSTANCE_ID}}/$INSTANCE_ID/g" /var/www/html/index.html
```

---

# 4️⃣ Assignment 4: Boto3 EC2 Lifecycle Automation & Security Groups

### 4.1 Create Security Group & Open Inbound Ports (HTTP 80 & SSH 22)

```python
import boto3

ec2 = boto3.client("ec2", region_name="ap-south-1")

# Create Security Group
sg = ec2.create_security_group(
    GroupName="web-ssh-sg",
    Description="Allow HTTP (80) and SSH (22)"
)
sg_id = sg["GroupId"]

# Authorize Ingress Rules
ec2.authorize_security_group_ingress(
    GroupId=sg_id,
    IpPermissions=[
        {
            "IpProtocol": "tcp",
            "FromPort": 80,
            "ToPort": 80,
            "IpRanges": [{"CidrIp": "0.0.0.0/0", "Description": "HTTP Traffic"}]
        },
        {
            "IpProtocol": "tcp",
            "FromPort": 22,
            "ToPort": 22,
            "IpRanges": [{"CidrIp": "0.0.0.0/0", "Description": "SSH Access"}]
        }
    ]
)
print("Security Group created with ID:", sg_id)
```

### 4.2 Check Health of Running Instances

```python
import boto3

ec2 = boto3.client("ec2", region_name="ap-south-1")

# 1. Get running instance IDs
running = ec2.describe_instances(
    Filters=[{"Name": "instance-state-name", "Values": ["running"]}]
)

instance_ids = [
    inst["InstanceId"]
    for res in running["Reservations"]
    for inst in res["Instances"]
]

# 2. Check health status
if instance_ids:
    status_resp = ec2.describe_instance_status(InstanceIds=instance_ids)
    for s in status_resp["InstanceStatuses"]:
        print(f"Instance ID:    {s['InstanceId']}")
        print(f"System Status:  {s['SystemStatus']['Status']}")
        print(f"Instance State: {s['InstanceStatus']['Status']}")
```

### 4.3 Stop Running Instances & Terminate Stopped Instances

```python
import boto3

ec2 = boto3.client("ec2", region_name="ap-south-1")

all_instances = ec2.describe_instances()

# Stop all running instances
running_ids = [
    inst["InstanceId"]
    for res in all_instances["Reservations"]
    for inst in res["Instances"]
    if inst["State"]["Name"] == "running"
]

if running_ids:
    ec2.stop_instances(InstanceIds=running_ids)
    ec2.get_waiter("instance_stopped").wait(InstanceIds=running_ids)
    print("Stopped:", running_ids)

# Terminate all stopped instances
stopped_ids = [
    inst["InstanceId"]
    for res in all_instances["Reservations"]
    for inst in res["Instances"]
    if inst["State"]["Name"] == "stopped"
]

if stopped_ids:
    ec2.terminate_instances(InstanceIds=stopped_ids)
    ec2.get_waiter("instance_terminated").wait(InstanceIds=stopped_ids)
    print("Terminated:", stopped_ids)
```

---

# 5️⃣ Assignment 5: AWS Auto Scaling & CloudWatch Alarms

### 5.1 Complete Auto Scaling Setup (Launch Template + ASG + Policies + Alarms)

```python
import boto3
import base64

region = "ap-south-1"
ec2 = boto3.client("ec2", region_name=region)
autoscaling = boto3.client("autoscaling", region_name=region)
cloudwatch = boto3.client("cloudwatch", region_name=region)

# 1. Base64 encode UserData startup script
script = """#!/bin/bash
apt-get update -y && apt-get install -y apache2
systemctl start apache2 && systemctl enable apache2
"""
userdata_b64 = base64.b64encode(script.encode()).decode()

# 2. Create Launch Template
lt_resp = ec2.create_launch_template(
    LaunchTemplateName="web-launch-template",
    LaunchTemplateData={
        "ImageId": "ami-01a00762f46d584a1",
        "InstanceType": "t3.micro",
        "SecurityGroupIds": ["sg-0123456789abcdef0"],
        "UserData": userdata_b64,
        "KeyName": "my-key"
    }
)
lt_id = lt_resp["LaunchTemplate"]["LaunchTemplateId"]

# 3. Create Auto Scaling Group
autoscaling.create_auto_scaling_group(
    AutoScalingGroupName="web-asg",
    LaunchTemplate={"LaunchTemplateId": lt_id, "Version": "$Latest"},
    MinSize=1,
    MaxSize=3,
    DesiredCapacity=1,
    VPCZoneIdentifier="subnet-0123456789abcdef0",  # Subnet ID
    HealthCheckType="EC2",
    HealthCheckGracePeriod=120
)

# 4. Scale-Out Policy (Add 1 instance)
scale_out = autoscaling.put_scaling_policy(
    AutoScalingGroupName="web-asg",
    PolicyName="scale-out-policy",
    PolicyType="SimpleScaling",
    AdjustmentType="ChangeInCapacity",
    ScalingAdjustment=1,
    Cooldown=120
)
scale_out_arn = scale_out["PolicyARN"]

# 5. Scale-In Policy (Remove 1 instance)
scale_in = autoscaling.put_scaling_policy(
    AutoScalingGroupName="web-asg",
    PolicyName="scale-in-policy",
    PolicyType="SimpleScaling",
    AdjustmentType="ChangeInCapacity",
    ScalingAdjustment=-1,
    Cooldown=120
)
scale_in_arn = scale_in["PolicyARN"]

# 6. CloudWatch Alarm: High CPU (>= 20%) -> Scale Out
cloudwatch.put_metric_alarm(
    AlarmName="cpu-high-alarm",
    MetricName="CPUUtilization",
    Namespace="AWS/EC2",
    Statistic="Average",
    Period=60,
    EvaluationPeriods=2,
    Threshold=20.0,
    ComparisonOperator="GreaterThanOrEqualToThreshold",
    Dimensions=[{"Name": "AutoScalingGroupName", "Value": "web-asg"}],
    AlarmActions=[scale_out_arn]
)

# 7. CloudWatch Alarm: Low CPU (<= 10%) -> Scale In
cloudwatch.put_metric_alarm(
    AlarmName="cpu-low-alarm",
    MetricName="CPUUtilization",
    Namespace="AWS/EC2",
    Statistic="Average",
    Period=60,
    EvaluationPeriods=2,
    Threshold=10.0,
    ComparisonOperator="LessThanOrEqualToThreshold",
    Dimensions=[{"Name": "AutoScalingGroupName", "Value": "web-asg"}],
    AlarmActions=[scale_in_arn]
)
```

---

# 6️⃣ Assignment 6: AWS RDS (MySQL) & EC2 Web Application

### 6.1 Create MySQL RDS Instance & Wait for Availability

```python
import boto3

rds = boto3.client("rds", region_name="ap-south-1")

db_id = "feedback-db-instance"

# Create MySQL RDS Database Instance
rds.create_db_instance(
    DBInstanceIdentifier=db_id,
    AllocatedStorage=20,            # 20 GB storage
    DBInstanceClass="db.t3.micro",
    Engine="mysql",
    MasterUsername="admin",
    MasterUserPassword="Password123",
    DBName="feedback_db",
    VpcSecurityGroupIds=["sg-0123456789abcdef0"], # Port 3306 open
    PubliclyAccessible=True,
    MultiAZ=False
)

# Wait until database is available (crucial waiter)
waiter = rds.get_waiter("db_instance_available")
waiter.wait(DBInstanceIdentifier=db_id, WaiterConfig={"Delay": 30, "MaxAttempts": 30})

# Retrieve Endpoint Address and Port
details = rds.describe_db_instances(DBInstanceIdentifier=db_id)
endpoint = details["DBInstances"][0]["Endpoint"]["Address"]
port     = details["DBInstances"][0]["Endpoint"]["Port"]
print(f"RDS Endpoint: {endpoint}:{port}")
```

### 6.2 PyMySQL: Database Connection, Table Creation & CRUD Operations

```python
import pymysql

DB_HOST = "feedback-db-instance.xxxxx.ap-south-1.rds.amazonaws.com"
DB_USER = "admin"
DB_PASS = "Password123"
DB_NAME = "feedback_db"

# Connect to MySQL RDS
conn = pymysql.connect(
    host=DB_HOST,
    user=DB_USER,
    password=DB_PASS,
    database=DB_NAME,
    cursorclass=pymysql.cursors.DictCursor,
    autocommit=True
)

with conn.cursor() as cursor:
    # 1. Create table
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS feedbacks (
            id INT AUTO_INCREMENT PRIMARY KEY,
            name VARCHAR(100) NOT NULL,
            email VARCHAR(200) NOT NULL,
            message VARCHAR(500) NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        );
    """)

    # 2. Insert record
    insert_sql = "INSERT INTO feedbacks (name, email, message) VALUES (%s, %s, %s);"
    cursor.execute(insert_sql, ("John Doe", "john@example.com", "Great cloud lab!"))

    # 3. Query records
    cursor.execute("SELECT id, name, email, message, created_at FROM feedbacks ORDER BY id DESC;")
    records = cursor.fetchall()
    for row in records:
        print(row["id"], row["name"], row["email"], row["message"])

conn.close()
```

---

# 7️⃣ Assignment 7: AWS Elastic Beanstalk (EB / EBS)

### 7.1 IAM Role & Instance Profile for Elastic Beanstalk

```python
import boto3

iam = boto3.client("iam", region_name="ap-south-1")

role_name = "aws-elasticbeanstalk-ec2-role"
profile_name = "aws-elasticbeanstalk-ec2-profile"

# Trust policy allowing EC2 service to assume role
trust_policy = """{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Principal": { "Service": "ec2.amazonaws.com" },
      "Action": "sts:AssumeRole"
    }
  ]
}"""

iam.create_role(RoleName=role_name, AssumeRolePolicyDocument=trust_policy)

# Attach required WebTier policy
iam.attach_role_policy(
    RoleName=role_name,
    PolicyArn="arn:aws:iam::aws:policy/AWSElasticBeanstalkWebTier"
)

# Create instance profile and add role
iam.create_instance_profile(InstanceProfileName=profile_name)
iam.add_role_to_instance_profile(InstanceProfileName=profile_name, RoleName=role_name)
```

### 7.2 Elastic Beanstalk Deployment Script

```python
import time
import boto3

region = "ap-south-1"
eb = boto3.client("elasticbeanstalk", region_name=region)
s3 = boto3.client("s3", region_name=region)

app_name    = "my-flask-app"
env_name    = "my-flask-env"
version_tag = "v1"
bucket_name = "my-eb-app-bucket-2401037"
zip_file    = "application.zip"

# 1. Upload application.zip to S3
s3_key = f"{app_name}/{zip_file}"
s3.upload_file(zip_file, bucket_name, s3_key)

# 2. Create EB Application
eb.create_application(ApplicationName=app_name, Description="My Flask App")

# 3. Create Application Version
eb.create_application_version(
    ApplicationName=app_name,
    VersionLabel=version_tag,
    SourceBundle={"S3Bucket": bucket_name, "S3Key": s3_key},
    AutoCreateApplication=True
)

# 4. Create Environment
solution_stack = "64bit Amazon Linux 2023 v4.2.0 running Python 3.12"
option_settings = [
    {
        "Namespace": "aws:autoscaling:launchconfiguration",
        "OptionName": "IamInstanceProfile",
        "Value": "aws-elasticbeanstalk-ec2-profile"
    },
    {
        "Namespace": "aws:autoscaling:launchconfiguration",
        "OptionName": "InstanceType",
        "Value": "t3.micro"
    },
    {
        "Namespace": "aws:elasticbeanstalk:environment",
        "OptionName": "EnvironmentType",
        "Value": "SingleInstance"
    }
]

eb.create_environment(
    ApplicationName=app_name,
    EnvironmentName=env_name,
    VersionLabel=version_tag,
    SolutionStackName=solution_stack,
    OptionSettings=option_settings
)

# 5. Poll until Environment is Ready
while True:
    resp = eb.describe_environments(ApplicationName=app_name, EnvironmentNames=[env_name])
    env = resp["Environments"][0]
    print(f"Status: {env['Status']} | Health: {env.get('Health')}")
    if env["Status"] == "Ready":
        print("Application URL: http://" + env["CNAME"])
        break
    time.sleep(20)
```

### 7.3 Standard Flask Entry Point for Elastic Beanstalk (`application.py`)

```python
from flask import Flask

# Elastic Beanstalk looks for 'application' callable by default!
application = Flask(__name__)

@application.route("/")
def index():
    return "<h1>Hello from AWS Elastic Beanstalk!</h1>"

if __name__ == "__main__":
    application.run(host="0.0.0.0", port=5000)
```

---

# 8️⃣ Assignment 8: Hadoop & MapReduce Streaming (Python)

### 8.1 Key HDFS Commands

```bash
hdfs dfs -mkdir -p /user/root/input               # Create HDFS directory
hdfs dfs -put -f /local/path/file.txt /user/root/input/  # Upload to HDFS
hdfs dfs -cat /user/root/output/part-00000        # Display output
hdfs dfs -rm -r /user/root/output                 # Remove output directory
```

### 8.2 Hadoop Streaming Execution Command

```bash
hadoop jar /opt/hadoop/share/hadoop/tools/lib/hadoop-streaming-3.3.6.jar \
  -files mapper.py,reducer.py \
  -input /user/root/input/big.txt \
  -output /user/root/output_count \
  -mapper "python3 mapper.py" \
  -reducer "python3 reducer.py"
```

### 8.3 Word Count Pattern

#### `mapper_wc.py`

```python
import sys

for line in sys.stdin:
    line = line.strip()
    words = line.split()
    for word in words:
        if word:
            # Emit key and count separated by tab
            print(f"{word}\t1")
```

#### `reducer_wc.py` (Handles key transition logic)

```python
import sys

current_word = None
current_count = 0

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    word, count = line.split('\t')
    count = int(count)

    if current_word == word:
        current_count += count
    else:
        if current_word is not None:
            print(f"{current_word}\t{current_count}")
        current_word = word
        current_count = count

# Emit last key
if current_word is not None:
    print(f"{current_word}\t{current_count}")
```

#### `combiner_wc.py` (Local pre-aggregation on Mapper nodes)

```python
# Combiner logic is identical to Reducer, but runs locally before shuffling
import sys

current_word = None
current_count = 0

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    word, count = line.split('\t')
    count = int(count)

    if current_word == word:
        current_count += count
    else:
        if current_word is not None:
            print(f"{current_word}\t{current_count}")
        current_word = word
        current_count = count

if current_word is not None:
    print(f"{current_word}\t{current_count}")
```

### 8.4 Distinct (Unique) Words Pattern

#### `mapper_distinct.py`

```python
import sys
import string

for line in sys.stdin:
    line = line.strip()
    # Strip punctuation and convert to lowercase
    line = line.translate(str.maketrans('', '', string.punctuation)).lower()
    for word in line.split():
        if word:
            print(f"{word}\t1")
```

#### `reducer_distinct.py`

```python
import sys

current_word = None

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    word = line.split('\t')[0]

    # Because Hadoop sorts identical keys together, print each word only once
    if word != current_word:
        current_word = word
        print(current_word)
```

### 8.5 K-Means Clustering via MapReduce (Iris Dataset)

#### `mapper_kmeans.py`

```python
import sys
import math

# Initial/Current candidate centroids
CENTROIDS = {
    "C1": (5.8, 4.0),
    "C2": (6.1, 2.8),
    "C3": (6.3, 2.7)
}

def euclidean_dist(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

for line in sys.stdin:
    parts = line.strip().split(',')
    if len(parts) >= 2:
        try:
            sl, sw = float(parts[0]), float(parts[1])
            point = (sl, sw)

            # Find nearest cluster centroid
            best_cluster = None
            min_dist = float("inf")
            for cid, coords in CENTROIDS.items():
                d = euclidean_dist(point, coords)
                if d < min_dist:
                    min_dist = d
                    best_cluster = cid

            # Emit cluster ID and coordinate string
            print(f"{best_cluster}\t{sl},{sw}")
        except ValueError:
            continue
```

#### `reducer_kmeans.py`

```python
import sys

current_cluster = None
sum_sl = 0.0
sum_sw = 0.0
count = 0

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    cluster, coords = line.split('\t')
    sl, sw = map(float, coords.split(','))

    if current_cluster == cluster:
        sum_sl += sl
        sum_sw += sw
        count += 1
    else:
        if current_cluster is not None:
            # Recompute mean centroid coordinates
            print(f"{current_cluster}\t{sum_sl / count:.2f},{sum_sw / count:.2f}\t{count}")
        current_cluster = cluster
        sum_sl = sl
        sum_sw = sw
        count = 1

if current_cluster is not None:
    print(f"{current_cluster}\t{sum_sl / count:.2f},{sum_sw / count:.2f}\t{count}")
```

### 8.6 Python Simulation of MapReduce Shuffle & Sort (Exam Question)

```python
from collections import defaultdict

def map_phase(doc):
    return [(word, 1) for word in doc.split()]

def shuffle_sort(mapped_data):
    grouped_data = defaultdict(list)
    for word, count in mapped_data:
        grouped_data[word].append(count)
    return list(grouped_data.items())

def reduce_phase(grouped_data):
    word, counts = grouped_data
    return (word, sum(counts))
```

---

# 9️⃣ Assignment 9: Apache Spark & PySpark

### 9.1 SparkSession Initialization & DataFrame CSV Read

```python
from pyspark.sql import SparkSession
from pyspark.sql.functions import col, trim

# 1. Initialize SparkSession
spark = SparkSession.builder \
    .appName("Assignment9") \
    .master("local[*]") \
    .getOrCreate()

# 2. Read CSV with Schema Inference
columns = ["age", "workclass", "fnlwgt", "education", "education_num",
           "marital_status", "occupation", "relationship", "race", "sex",
           "capital_gain", "capital_loss", "hours_per_week", "native_country", "income"]

df = spark.read.csv("adult.data", header=False, inferSchema=True, ignoreLeadingWhiteSpace=True)
df = df.toDF(*columns)

# 3. Clean whitespace from all string columns
for col_name, dtype in df.dtypes:
    if dtype == "string":
        df = df.withColumn(col_name, trim(col(col_name)))

df.show(5)
print("Total records:", df.count())
```

### 9.2 Core RDD Transformations & Actions

```python
rdd = df.rdd

# Question 1: Country with highest adults (excluding USA and '?')
top_country = rdd.filter(
    lambda r: r.native_country not in ["United-States", "?"]
).map(
    lambda r: (r.native_country, 1)
).reduceByKey(
    lambda a, b: a + b
).sortBy(
    lambda x: x[1], ascending=False
).take(1)

print("Top Non-US Country:", top_country)  # e.g., [('Mexico', 643)]

# Question 2: Count people with Master's+ (education_num >= 14) in Tech-support
masters_tech = rdd.filter(
    lambda r: r.education_num >= 14 and r.occupation == "Tech-support"
).count()

print("Masters in Tech Support:", masters_tech)

# Question 3: Count unmarried males working in Local-gov
unmarried_males = rdd.filter(
    lambda r: r.sex == "Male" and r.marital_status == "Never-married" and r.workclass == "Local-gov"
).count()

print("Unmarried Males in Local-gov:", unmarried_males)
```

### 9.3 PySpark DataFrame SQL / Aggregation Equivalent

```python
from pyspark.sql.functions import count, desc

# Country with highest adults excluding US
df.filter(~col("native_country").isin(["United-States", "?"])) \
  .groupBy("native_country") \
  .agg(count("*").alias("total")) \
  .orderBy(desc("total")) \
  .show(1)

# Stop SparkSession at the end of the script
spark.stop()
```

### 9.4 PySpark MLlib K-Means Clustering (Standard Exam Solution)

```python
from pyspark.ml.clustering import KMeans
from pyspark.ml.feature import VectorAssembler

# 1. Assemble features into a vector column
assembler = VectorAssembler(
    inputCols=["age", "education_num", "hours_per_week"],
    outputCol="features"
)
feature_df = assembler.transform(df.na.drop())

# 2. Train KMeans Model (k=3)
kmeans = KMeans(k=3, seed=42, featuresCol="features", predictionCol="cluster")
model = kmeans.fit(feature_df)

# 3. Predict clusters & show cluster centers
clustered = model.transform(feature_df)
clustered.select("age", "education_num", "hours_per_week", "cluster").show(5)

for i, center in enumerate(model.clusterCenters()):
    print(f"Cluster {i} Center: {center}")
```

---

# 🧠 Pen-and-Paper Memory Checklist: Exact Spelling & Pitfalls

| Function / Parameter                | Common Writing Mistake        | Correct Exact Spelling                                                                       |
| :---------------------------------- | :---------------------------- | :------------------------------------------------------------------------------------------- |
| **S3 Region Configuration**   | `Location: region`          | `CreateBucketConfiguration={"LocationConstraint": region}`                                 |
| **Boto3 Launch EC2**          | `ec2.create_instances(...)` | `ec2.run_instances(ImageId=..., InstanceType=..., MinCount=1, MaxCount=1)`                 |
| **EC2 Waiter**                | `instance_run`              | `ec2.get_waiter("instance_running").wait(InstanceIds=[...])`                               |
| **Security Group Rule**       | `Port=80`                   | `IpProtocol="tcp"`, `FromPort=80`, `ToPort=80`, `IpRanges=[{"CidrIp": "0.0.0.0/0"}]` |
| **AutoScaling Adjustment**    | `Adjustment=1`              | `AdjustmentType="ChangeInCapacity"`, `ScalingAdjustment=1`                               |
| **CloudWatch Alarm Operator** | `GreaterThan`               | `ComparisonOperator="GreaterThanOrEqualToThreshold"`                                       |
| **Elastic Beanstalk File**    | `app.py`                    | Must name callable `application = Flask(__name__)` in `application.py`                   |
| **Hadoop Output Separator**   | `,` or space                | Tab: `print(f"{word}\t{count}")`                                                           |
| **Spark RDD Aggregation**     | `groupByKey().reduce()`     | `reduceByKey(lambda a, b: a + b)` (avoids shuffle overflow)                                |
| **SparkSession Builder**      | `SparkSession()`            | `SparkSession.builder.appName("...").master("local[*]").getOrCreate()`                     |
