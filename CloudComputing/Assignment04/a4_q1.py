# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3

region = "ap-south-1"
linux_ami = "ami-0ac7b260cf76d8865"
ubuntu_ami = "ami-01a00762f46d584a1"

ec2 = boto3.client("ec2", region_name=region)

# Creating one Linux instance
linux_instance = ec2.run_instances(
  ImageId=linux_ami,
  InstanceType="t3.micro",
  MinCount=1,
  MaxCount=1
)

print("Linux Instances:")
# Accessing the instance id from the response
linux_id = linux_instance["Instances"][0]["InstanceId"]
print(f"Launched EC2 Linux Instance: {linux_id}")

# waiting for instance to enter running state
print("Waiting for Linux instance to enter Running state")
waiter = ec2.get_waiter("instance_running")
waiter.wait(InstanceIds=[linux_id])

# Getting the instance details
linux_desc = ec2.describe_instances(InstanceIds=[linux_id])
instance_data = linux_desc["Reservations"][0]["Instances"][0]

public_dns = instance_data.get("PublicDnsName")
public_ip = instance_data.get("PublicIpAddress")

# Printing the instance details like dns and ip
print("Status: RUNNING")
print(f"Instance ID: {linux_id}")
print(f"Public DNS Address: {public_dns}")
print(f"Public IP Address:  {public_ip}")