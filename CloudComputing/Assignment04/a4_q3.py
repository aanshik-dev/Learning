# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3

region = "ap-south-1"

ec2 = boto3.client("ec2", region_name=region)

# Getting all the instances with state "running". 
running_instances = ec2.describe_instances(
  Filters=[
    {
      "Name": "instance-state-name",
      "Values": ["running"]
    }
  ]
)

# Getting the instance details
for reservation in running_instances["Reservations"]:
    for instance in reservation["Instances"]:
        # Printing the running instance details
        print("Status: RUNNING")
        print(f"Instance ID: {instance['InstanceId']}")
        print(f"Public DNS Address: {instance['PublicDnsName']}")
        print(f"Public IP Address: {instance['PublicIpAddress']}\n")