# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3

region = "ap-south-1"
linux_ami = "ami-0ac7b260cf76d8865"
ubuntu_ami = "ami-01a00762f46d584a1"

ec2 = boto3.client("ec2", region_name=region)

# Creating two Ubuntu instances
ubuntu_instance = ec2.run_instances(
  ImageId=ubuntu_ami,
  InstanceType="t3.micro",
  MinCount=2,
  MaxCount=2
)

print("\nUbuntu Instances:")
# Getting both instance ids
ubuntu_id1 = ubuntu_instance["Instances"][0]["InstanceId"]
ubuntu_id2 = ubuntu_instance["Instances"][1]["InstanceId"]
print(f"Launched EC2 Ubuntu Instance: {ubuntu_id1}")
print(f"Launched EC2 Ubuntu Instance: {ubuntu_id2}")

# waiting for instances to enter running state
print("Waiting for Ubuntu instances to enter Running state")
waiter = ec2.get_waiter("instance_running")
waiter.wait(InstanceIds=[ubuntu_id1, ubuntu_id2])

# Getting the instance details
ubuntu_desc = ec2.describe_instances(InstanceIds=[ubuntu_id1, ubuntu_id2])

for reservation in ubuntu_desc["Reservations"]:
    for instance in reservation["Instances"]:
        # printing the instance details
        print("Status: RUNNING")
        print(f"Instance ID: {instance['InstanceId']}")
        print(f"Public DNS Address: {instance['PublicDnsName']}")
        print(f"Public IP Address: {instance['PublicIpAddress']}\n")