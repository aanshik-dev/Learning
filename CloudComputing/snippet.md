<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **CLOUD COMPUTING - CODE SNIPPETS** 🔥🐦‍🔥

> Important boto3 / Python code blocks for Mid Sem Exam
> Based on Lab Assignments 1-5

<br>

# 🐦‍🔥 PYTHON WARMUP (Assignment 1)

## 🔥 Python Class with apply method

```python
class AtomicList:
    def __init__(self, *values):
        self.values = list(values)

    def apply(self, func):
        try:
            return func(self.values.copy())
        except Exception as e:
            raise Exception(f"Error while applying function: {e}")

# Usage
al = AtomicList(1, 2, 6, 5, 4)
print(al.apply(lambda x: [i * 2 for i in x]))
# Output: [2, 4, 12, 10, 8]
```

> 📝 NOTE : .copy() use kiya taaki original list modify na ho

<br>

## 🔥 map and reduce with functools

```python
import functools

# map - uppercase all words in a list
def upper(ls):
    return list(map(lambda x: x.upper(), ls))

print(upper(["hello", "world"]))
# Output: ['HELLO', 'WORLD']

# reduce - product of all numbers
def product(ls):
    return functools.reduce(lambda x, y: x * y, ls)

print(product([1, 2, 3, 4, 5]))
# Output: 120
```

<br>

## 🔥 Dictionary and List Comprehension

```python
# List comprehension - squares of 0 to n
def sqr(n):
    return [x**2 for x in range(n)]

# Dictionary comprehension - number to square mapping
def sqrMap(n):
    return {x: x**2 for x in range(n)}

# Dict with key mapped to [square, cube]
def sq_Cube(n):
    dictionary = {}
    for num in range(0, n, 2):
        dictionary[num] = [num**2, num**3]
    return dictionary
```

<br>

## 🔥 Frequency Count using dict

```python
def get_frequency(lst):
    frequency = {}
    for num in lst:
        if num in frequency:
            frequency[num] += 1
        else:
            frequency[num] = 1
    return frequency
```

<br>

## 🔥 First Repeating Element using set

```python
def repeating(lst):
    seen = set()
    for num in lst:
        if num in seen:
            return num
        else:
            seen.add(num)
```

<br>

---

# 🐦‍🔥 BOTO3 - S3 OPERATIONS (Assignment 3)

## 🔥 Create S3 Bucket and Upload Files

```python
import boto3
import os

bucket_name = "my-web-bucket"
region = "ap-south-1"

# Create S3 client
s3 = boto3.client("s3", region_name=region)

# Create Bucket
s3.create_bucket(
    Bucket=bucket_name,
    CreateBucketConfiguration={
        "LocationConstraint": region
    }
)
print(f"Bucket '{bucket_name}' created successfully.")

# Upload all files from a directory to S3
web_dir = "website"
for root, directories, files in os.walk(web_dir):
    for filename in files:
        file_path = os.path.join(root, filename)
        s3_key = os.path.relpath(file_path, web_dir).replace(os.sep, "/")
        s3.upload_file(file_path, bucket_name, s3_key)
        print(f"Uploaded: {s3_key}")
```

> 📝 NOTE : ap-south-1 region ke liye LocationConstraint zaroori hai. us-east-1 ke liye nahi chahiye.

<br>

## 🔥 Upload a Single File to S3

```python
import boto3

s3 = boto3.client("s3")

s3.upload_file(
    "local_file.txt",       # local file path
    "my-bucket-name",       # bucket name
    "uploaded_file.txt"     # S3 key (path in bucket)
)
print("File uploaded!")
```

<br>

---

# 🐦‍🔥 BOTO3 - EC2 OPERATIONS (Assignment 3 and 4)

## 🔥 Launch an EC2 Instance (Basic)

```python
import boto3

region = "ap-south-1"
ami_id = "ami-01a00762f46d584a1"   # Ubuntu AMI

ec2 = boto3.client("ec2", region_name=region)

# Launch Instance
response = ec2.run_instances(
    ImageId=ami_id,
    InstanceType="t3.micro",
    MinCount=1,
    MaxCount=1
)

instance_id = response["Instances"][0]["InstanceId"]
print(f"Launched EC2 Instance: {instance_id}")

# Wait for Running state
waiter = ec2.get_waiter("instance_running")
waiter.wait(InstanceIds=[instance_id])
print("Instance is now RUNNING")

# Get Public IP and DNS
desc = ec2.describe_instances(InstanceIds=[instance_id])
instance = desc["Reservations"][0]["Instances"][0]
print(f"Public DNS: {instance.get('PublicDnsName')}")
print(f"Public IP:  {instance.get('PublicIpAddress')}")
```

<br>

## 🔥 Create Security Group and Add Inbound Rule

```python
import boto3

region = "ap-south-1"
ec2 = boto3.client("ec2", region_name=region)

# Create Security Group
sg_response = ec2.create_security_group(
    GroupName="my-web-sg",
    Description="Allow HTTP traffic on port 80"
)
sg_id = sg_response["GroupId"]
print(f"Created Security Group: {sg_id}")

# Add Inbound Rule - Allow HTTP (Port 80)
ec2.authorize_security_group_ingress(
    GroupId=sg_id,
    IpPermissions=[
        {
            "IpProtocol": "tcp",
            "FromPort": 80,
            "ToPort": 80,
            "IpRanges": [
                {"CidrIp": "0.0.0.0/0"}
            ]
        }
    ]
)
print("Port 80 opened for HTTP traffic")
```

> 📝 NOTE : "0.0.0.0/0" matlab sabke liye open. Production mein specific IP range use karo.

<br>

## 🔥 Launch EC2 with Security Group and UserData

```python
import boto3

region = "ap-south-1"
ec2 = boto3.client("ec2", region_name=region)

# Startup script for HTTP server
user_data = """#!/bin/bash
apt-get update -y
apt-get install -y apache2
systemctl start apache2
systemctl enable apache2
echo "Hello from Cloud!" > /var/www/html/index.html
"""

# Launch Instance with SG and UserData
response = ec2.run_instances(
    ImageId="ami-01a00762f46d584a1",
    InstanceType="t3.micro",
    MinCount=1,
    MaxCount=1,
    SecurityGroupIds=[sg_id],
    UserData=user_data
)

instance_id = response["Instances"][0]["InstanceId"]
print(f"Launched: {instance_id}")
```

> 📝 NOTE : UserData bash script hai jo instance first boot pe automatically run hota hai. Web server install aur start karne ke liye use hota hai.

<br>

## 🔥 Launch EC2 with IAM Role

```python
response = ec2.run_instances(
    ImageId=ami_id,
    InstanceType="t3.micro",
    MinCount=1,
    MaxCount=1,
    SecurityGroupIds=[sg_id],
    UserData=startup_script,
    IamInstanceProfile={
        'Name': 'my-ec2-s3-role'
    }
)
```

> 📝 NOTE : IamInstanceProfile use karte hain jab EC2 instance ko S3 ya doosre AWS services access karne hain bina access keys ke.

<br>

## 🔥 List Running EC2 Instances

```python
import boto3

ec2 = boto3.client("ec2", region_name="ap-south-1")

# Filter only running instances
response = ec2.describe_instances(
    Filters=[
        {
            "Name": "instance-state-name",
            "Values": ["running"]
        }
    ]
)

for reservation in response["Reservations"]:
    for instance in reservation["Instances"]:
        print(f"ID: {instance['InstanceId']}")
        print(f"IP: {instance['PublicIpAddress']}")
        print(f"DNS: {instance['PublicDnsName']}\n")
```

<br>

## 🔥 Get IP Address of EC2 Instance

```python
import boto3

ec2 = boto3.client("ec2", region_name="ap-south-1")

response = ec2.describe_instances()

for reservation in response["Reservations"]:
    for instance in reservation["Instances"]:
        print(f"Instance ID: {instance['InstanceId']}")
        print(f"Public IP: {instance.get('PublicIpAddress', 'N/A')}")
        print(f"Private IP: {instance.get('PrivateIpAddress', 'N/A')}")
```

<br>

## 🔥 Check Health of EC2 Instances

```python
import boto3

ec2 = boto3.client("ec2", region_name="ap-south-1")

# Get running instance IDs
running = ec2.describe_instances(
    Filters=[{"Name": "instance-state-name", "Values": ["running"]}]
)

instance_ids = []
for r in running["Reservations"]:
    for inst in r["Instances"]:
        instance_ids.append(inst["InstanceId"])

# Check health
health = ec2.describe_instance_status(InstanceIds=instance_ids)

for status in health["InstanceStatuses"]:
    print(f"Instance: {status['InstanceId']}")
    print(f"System Status: {status['SystemStatus']['Status']}")
    print(f"Instance Status: {status['InstanceStatus']['Status']}")
```

<br>

## 🔥 Stop Running Instances

```python
import boto3

ec2 = boto3.client("ec2", region_name="ap-south-1")

# Get all running instance IDs
all_inst = ec2.describe_instances()
running_ids = []
for r in all_inst["Reservations"]:
    for inst in r["Instances"]:
        if inst["State"]["Name"] == "running":
            running_ids.append(inst["InstanceId"])

# Stop them
if running_ids:
    ec2.stop_instances(InstanceIds=running_ids)
    waiter = ec2.get_waiter("instance_stopped")
    waiter.wait(InstanceIds=running_ids)
    print("Instances STOPPED")
```

<br>

## 🔥 Terminate Instances

```python
import boto3

ec2 = boto3.client("ec2", region_name="ap-south-1")

# Get stopped instance IDs
all_inst = ec2.describe_instances()
stopped_ids = []
for r in all_inst["Reservations"]:
    for inst in r["Instances"]:
        if inst["State"]["Name"] == "stopped":
            stopped_ids.append(inst["InstanceId"])

# Terminate them
if stopped_ids:
    ec2.terminate_instances(InstanceIds=stopped_ids)
    waiter = ec2.get_waiter("instance_terminated")
    waiter.wait(InstanceIds=stopped_ids)
    print("Instances TERMINATED")
```

<br>

---

# 🐦‍🔥 BASH - EC2 USER DATA SCRIPTS (Assignment 3 and 5)

## 🔥 Install Apache and Copy from S3

```bash
#!/bin/bash
# Update and install
apt-get update -y
apt-get install -y apache2 awscli

# Start Apache
systemctl start apache2
systemctl enable apache2

# Remove default page
rm -rf /var/www/html/*

# Copy website from S3 bucket
aws s3 cp s3://my-bucket-name/ /var/www/html/ --recursive

# Set permissions
chown -R www-data:www-data /var/www/html
chmod -R 755 /var/www/html
```

<br>

## 🔥 Install Apache and Clone from GitHub

```bash
#!/bin/bash
apt-get update -y
apt-get install -y apache2 git

systemctl start apache2
systemctl enable apache2

rm -rf /var/www/html/*

# Clone from GitHub
git clone https://github.com/user/repo.git /tmp/repo
cp -r /tmp/repo/website/* /var/www/html/
rm -rf /tmp/repo

# Get EC2 Instance ID using metadata (IMDSv2)
TOKEN=$(curl -s -X PUT \
    "http://169.254.169.254/latest/api/token" \
    -H "X-aws-ec2-metadata-token-ttl-seconds: 21600")

INSTANCE_ID=$(curl -s \
    -H "X-aws-ec2-metadata-token: $TOKEN" \
    "http://169.254.169.254/latest/meta-data/instance-id")

# Replace placeholder in HTML
sed -i "s/{{INSTANCE_ID}}/$INSTANCE_ID/g" /var/www/html/index.html

chown -R www-data:www-data /var/www/html
chmod -R 755 /var/www/html
systemctl restart apache2
```

> 📝 NOTE : IMDSv2 (Instance Metadata Service v2) se EC2 instance apni metadata fetch kar sakta hai jaise instance-id, public-ip etc. Pehle token lena padta hai PUT request se, fir us token ke saath metadata request karte hain.

<br>

## 🔥 Simple HTTP Server Script (for Amazon Linux)

```bash
#!/bin/bash
dnf update -y
dnf install httpd -y
systemctl start httpd
systemctl enable httpd
echo "HTTP Server is Running" > /var/www/html/index.html
```

> 📝 NOTE : Ubuntu mein apache2 use hota hai (apt-get), Amazon Linux mein httpd use hota hai (dnf/yum).

<br>

---

# 🐦‍🔥 BOTO3 - AUTO SCALING (Assignment 5)

## 🔥 Complete Auto Scaling Setup with CloudWatch

```python
import boto3
import base64

region = "ap-south-1"
ubuntu_ami = "ami-01a00762f46d584a1"

# 1. Create Clients
ec2 = boto3.client("ec2", region_name=region)
autoscaling = boto3.client("autoscaling", region_name=region)
cloudwatch = boto3.client("cloudwatch", region_name=region)

# 2. Get Security Group ID
sg = ec2.describe_security_groups(GroupNames=["my-sg"])
sg_id = sg["SecurityGroups"][0]["GroupId"]

# 3. Read and Encode Startup Script
with open("startup.sh", "r") as f:
    script = f.read()

userdata = base64.b64encode(script.encode()).decode()

# 4. Find Subnet
subnets = ec2.describe_subnets(
    Filters=[{
        "Name": "availability-zone",
        "Values": ["ap-south-1a"]
    }]
)
subnet_id = subnets["Subnets"][0]["SubnetId"]
```

<br>

## 🔥 Create Launch Template

```python
# 5. Create Launch Template
response = ec2.create_launch_template(
    LaunchTemplateName="my-launch-template",
    LaunchTemplateData={
        "ImageId": ubuntu_ami,
        "InstanceType": "t3.micro",
        "SecurityGroupIds": [sg_id],
        "UserData": userdata,
        "KeyName": "my-key-pair"
    }
)
template_id = response["LaunchTemplate"]["LaunchTemplateId"]
print(f"Launch Template: {template_id}")
```

<br>

## 🔥 Create Auto Scaling Group

```python
# 6. Create Auto Scaling Group
autoscaling.create_auto_scaling_group(
    AutoScalingGroupName="my-asg",
    LaunchTemplate={
        "LaunchTemplateId": template_id,
        "Version": "$Latest"
    },
    MinSize=1,
    MaxSize=3,
    DesiredCapacity=1,
    VPCZoneIdentifier=subnet_id,
    HealthCheckType="EC2",
    HealthCheckGracePeriod=120
)
print("Auto Scaling Group created")
```

<br>

## 🔥 Create Scale-Out and Scale-In Policies

```python
# 7. Scale-Out Policy (Add 1 instance)
scale_out = autoscaling.put_scaling_policy(
    AutoScalingGroupName="my-asg",
    PolicyName="scale-out",
    PolicyType="SimpleScaling",
    AdjustmentType="ChangeInCapacity",
    ScalingAdjustment=1,
    Cooldown=120
)
scale_out_arn = scale_out["PolicyARN"]

# 8. Scale-In Policy (Remove 1 instance)
scale_in = autoscaling.put_scaling_policy(
    AutoScalingGroupName="my-asg",
    PolicyName="scale-in",
    PolicyType="SimpleScaling",
    AdjustmentType="ChangeInCapacity",
    ScalingAdjustment=-1,
    Cooldown=120
)
scale_in_arn = scale_in["PolicyARN"]
```

> 📝 NOTE : ScalingAdjustment = 1 matlab ek instance add karo. -1 matlab ek instance remove karo. Cooldown period (120 sec) ke andar dobara scaling nahi hogi.

<br>

## 🔥 Create CloudWatch Alarms for Auto Scaling

```python
# 9. Scale-Out Alarm (CPU >= 20% for 2 minutes)
cloudwatch.put_metric_alarm(
    AlarmName="cpu-high",
    AlarmDescription="Scale out when CPU >= 20%",
    Namespace="AWS/EC2",
    MetricName="CPUUtilization",
    Dimensions=[{
        "Name": "AutoScalingGroupName",
        "Value": "my-asg"
    }],
    Statistic="Average",
    Period=60,
    EvaluationPeriods=2,
    Threshold=20,
    ComparisonOperator="GreaterThanOrEqualToThreshold",
    AlarmActions=[scale_out_arn]
)

# 10. Scale-In Alarm (CPU <= 30% for 2 minutes)
cloudwatch.put_metric_alarm(
    AlarmName="cpu-low",
    AlarmDescription="Scale in when CPU <= 30%",
    Namespace="AWS/EC2",
    MetricName="CPUUtilization",
    Dimensions=[{
        "Name": "AutoScalingGroupName",
        "Value": "my-asg"
    }],
    Statistic="Average",
    Period=60,
    EvaluationPeriods=2,
    Threshold=30,
    ComparisonOperator="LessThanOrEqualToThreshold",
    AlarmActions=[scale_in_arn]
)
```

> 📝 NOTE : Period=60 matlab har 60 seconds pe metric check hoga. EvaluationPeriods=2 matlab 2 consecutive periods tak threshold cross hona chahiye alarm trigger hone ke liye.

<br>

## 🔥 Get Auto Scaling Group Details

```python
# 11. Describe ASG
response = autoscaling.describe_auto_scaling_groups(
    AutoScalingGroupNames=["my-asg"]
)
asg = response["AutoScalingGroups"][0]

print(f"ASG Name: {asg['AutoScalingGroupName']}")
print(f"Min: {asg['MinSize']}, Max: {asg['MaxSize']}")
print(f"Desired: {asg['DesiredCapacity']}")

for inst in asg["Instances"]:
    inst_id = inst["InstanceId"]
    details = ec2.describe_instances(InstanceIds=[inst_id])
    inst_data = details["Reservations"][0]["Instances"][0]
    print(f"  ID: {inst_id} | IP: {inst_data.get('PublicIpAddress')}")
```

<br>

---

# 🐦‍🔥 QUICK REFERENCE - BOTO COMMANDS FOR EXAM

## 🔥 One-liner Boto Commands (PYQ 2024 Q5)

```python
import boto3
ec2 = boto3.client("ec2", region_name="ap-south-1")
s3  = boto3.client("s3")

# (a) Launch an EC2 instance
ec2.run_instances(ImageId="ami-xxx", InstanceType="t3.micro", MinCount=1, MaxCount=1)

# (b) Upload file to S3 bucket
s3.upload_file("local.txt", "my-bucket", "remote.txt")

# (c) Get IP address of EC2 instance
resp = ec2.describe_instances(InstanceIds=["i-xxx"])
ip = resp["Reservations"][0]["Instances"][0]["PublicIpAddress"]

# (d) List running EC2 instances
ec2.describe_instances(Filters=[{"Name":"instance-state-name","Values":["running"]}])
```

<br>

## 🔥 Important Waiters

```python
# Wait for instance to be running
ec2.get_waiter("instance_running").wait(InstanceIds=[instance_id])

# Wait for instance to be stopped
ec2.get_waiter("instance_stopped").wait(InstanceIds=[instance_id])

# Wait for instance to be terminated
ec2.get_waiter("instance_terminated").wait(InstanceIds=[instance_id])
```

<br>

## 🔥 Security Group - Allow SSH + HTTP

```python
ec2.authorize_security_group_ingress(
    GroupId=sg_id,
    IpPermissions=[
        {
            "IpProtocol": "tcp",
            "FromPort": 80,
            "ToPort": 80,
            "IpRanges": [{"CidrIp": "0.0.0.0/0", "Description": "HTTP"}]
        },
        {
            "IpProtocol": "tcp",
            "FromPort": 22,
            "ToPort": 22,
            "IpRanges": [{"CidrIp": "0.0.0.0/0", "Description": "SSH"}]
        }
    ]
)
```

<br>

---

# 🐦‍🔥 FLOW SUMMARY - What happens in each step

```
1. boto3.client("ec2")          --> EC2 client create karo
2. create_security_group()      --> SG banao (firewall rules)
3. authorize_security_group_ingress() --> Port 80/22 kholo
4. run_instances()              --> EC2 instance launch karo
5. get_waiter("instance_running").wait() --> Running hone ka wait karo
6. describe_instances()         --> IP/DNS get karo
7. stop_instances()             --> Instance rok do
8. terminate_instances()        --> Instance permanently delete karo
```

```
AutoScaling Flow:
1. create_launch_template()     --> Template banao (AMI, type, SG, UserData)
2. create_auto_scaling_group()  --> ASG banao (min, max, desired, subnet)
3. put_scaling_policy()         --> Scale-out (+1) aur Scale-in (-1) policy
4. put_metric_alarm()           --> CloudWatch alarm jo policy trigger kare
5. CPU high --> Alarm --> Scale-out policy --> New instance launch
6. CPU low  --> Alarm --> Scale-in policy  --> Instance terminate
```

<br>

</div>
</div>
