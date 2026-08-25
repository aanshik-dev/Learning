# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3
import os

# AWS Region
region = "ap-south-1"

# Create an EC2 client
ec2 = boto3.client("ec2", region_name=region)

# Step 1: Create Security Group with Port 80 Open
sg_name = "a3-web-sg"

try:
    sg_response = ec2.create_security_group(
        GroupName=sg_name,
        Description="Security group allowing HTTP traffic on port 80"
    )
    sg_id = sg_response["GroupId"]
    print(f"Created Security Group: {sg_id}")

    ec2.authorize_security_group_ingress(
        GroupId=sg_id,
        IpPermissions=[
            {
                "IpProtocol": "tcp",
                "FromPort": 80,
                "ToPort": 80,
                "IpRanges": [{"CidrIp": "0.0.0.0/0"}]
            }
        ]
    )
    print("Opened Port 80 for HTTP traffic.")

except ec2.exceptions.ClientError as e:
    if "InvalidGroup.Duplicate" in str(e):
        sgs = ec2.describe_security_groups(GroupNames=[sg_name])
        sg_id = sgs["SecurityGroups"][0]["GroupId"]
        print(f"Using existing Security Group: {sg_id}")
    else:
        raise e

# Step 2: Read Startup Script (a3_q2.sh)
script_dir = os.path.dirname(os.path.abspath(__file__))
script_path = os.path.join(script_dir, "a3_q2.sh")

with open(script_path, "r") as file:
    startup_script = file.read()

# Step 3: Launch t3.micro EC2 Instance with UserData
ami_id = "ami-01a00762f46d584a1"

response = ec2.run_instances(
    ImageId=ami_id,
    InstanceType="t3.micro",
    MinCount=1,
    MaxCount=1,
    SecurityGroupIds=[sg_id],
    UserData=startup_script
)

instance_id = response["Instances"][0]["InstanceId"]
print(f"Launched EC2 Instance: {instance_id}")

# Step 4: Wait until Instance status changes to 'running'
print("Checking status... Waiting for instance to enter 'running' state...")
waiter = ec2.get_waiter("instance_running")
waiter.wait(InstanceIds=[instance_id])
print("Instance status is now 'running'.")

# Step 5: Get and return Public DNS address (and Public IP)
instance_desc = ec2.describe_instances(InstanceIds=[instance_id])
instance = instance_desc["Reservations"][0]["Instances"][0]

public_dns = instance.get("PublicDnsName")
public_ip = instance.get("PublicIpAddress")

print(f"Public DNS Address: {public_dns}")
print(f"Public IP Address:  http://{public_ip}")
