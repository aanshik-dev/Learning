# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3
import time
import requests

region = "ap-south-1"
linux_ami = "ami-0ac7b260cf76d8865"
ubuntu_ami = "ami-01a00762f46d584a1"

ec2 = boto3.client("ec2", region_name=region)

# creating the security group with custom inbound rule
security_group = ec2.create_security_group(
    GroupName="a4-web-sg",
    Description="Security group for HTTP server that allow HTTP traffic on port 80 from anywhere."
)
sg_id = security_group["GroupId"]
print(f"Created Security Group: {sg_id}")

# adding the inbound rule to allow HTTP traffic at post 80
ec2.authorize_security_group_ingress(
    GroupId=sg_id,
    IpPermissions=[
        {
            "IpProtocol": "tcp",
            "FromPort": 80,
            "ToPort": 80,
            "IpRanges": [
                {
                    "CidrIp": "0.0.0.0/0",
                    "Description": "Allow HTTP traffic"
                }
            ]
        }
    ]
)

print("Inbound HTTP permission added at port 80")

# Script to install and run HTTP server
user_data = """#!/bin/bash
dnf update -y
dnf install httpd -y
systemctl start httpd
systemctl enable httpd
echo "HTTP Server is Running" > /var/www/html/index.html
"""

# running the instance
linux_instance = ec2.run_instances(
    ImageId=linux_ami,
    InstanceType="t3.micro",
    MinCount=1,
    MaxCount=1,
    SecurityGroupIds=[sg_id],
    UserData=user_data
)
linux_id = linux_instance["Instances"][0]["InstanceId"]
print(f"\nLinux Instance ID: {linux_id}")
print("Waiting for instance to enter Running state...")

# waiting for instance to enter running state
waiter = ec2.get_waiter("instance_running")
waiter.wait(
    InstanceIds=[linux_id]
)
print("Linux instance is RUNNING.")

# getting the instance details
linux_desc = ec2.describe_instances(
    InstanceIds=[linux_id]
)
instance = linux_desc["Reservations"][0]["Instances"][0]
public_dns = instance["PublicDnsName"]
public_ip = instance["PublicIpAddress"]

# printing the instance details
print(f"Public DNS: {public_dns}")
print(f"Public IP : {public_ip}")

# waiting for HTTP server to start
print("\nWaiting for HTTP server to start...")
time.sleep(30)

# Verifying HTTP server
try:
    url = f"http://{public_ip}"
    response = requests.get(url, timeout=10)

    if response.status_code == 200:
        print("HTTP Server is running successfully.")
        print(f"HTTP Status Code: {response.status_code}")
        print(f"Response: {response.text}")
    else:
        print("HTTP Server is not responding correctly.")
        print(f"HTTP Status Code: {response.status_code}")

except requests.exceptions.RequestException as e:
    print("HTTP Server verification failed.")
    print(f"Error: {e}")