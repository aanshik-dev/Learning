# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3

region = "ap-south-1"

ec2 = boto3.client("ec2", region_name=region)


# Check the health of the running instances.
running_instances = ec2.describe_instances(
  Filters=[
    {
      "Name": "instance-state-name",
      "Values": ["running"]
    }
  ]
)

instance_ids = []
# Getting the instance ids
for reservation in running_instances["Reservations"]:
    for instance in reservation["Instances"]:
        instance_ids.append(instance["InstanceId"])

# Getting the instance health
health = ec2.describe_instance_status(
    InstanceIds=instance_ids
)

# Printing the instance health
for status in health["InstanceStatuses"]:
    print(f"Instance ID: {status['InstanceId']}")
    print(f"System Status: {status['SystemStatus']['Status']}")
    print(f"Instance Status: {status['InstanceStatus']['Status']}")
