# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3

region = "ap-south-1"
ec2 = boto3.client("ec2", region_name=region)

# Getting all the instances
all_instances = ec2.describe_instances()

running_instances = []
# extracting the running instances from the response
for reservation in all_instances["Reservations"]:
  for instance in reservation["Instances"]:
    if instance["State"]["Name"] == "running":
      running_instances.append(instance["InstanceId"])
print("Running Instances: ", running_instances)

# Stopping the running instances
if running_instances:
    print("Stopping running instances...")
    ec2.stop_instances(
        InstanceIds=running_instances
    )
    # Waiting for instances to stop
    stop_waiter = ec2.get_waiter("instance_stopped")
    stop_waiter.wait(InstanceIds=running_instances)
    print("Instance STOPPED.")
else:
    print("No running instances found.")

response = ec2.describe_instances()
# printing all the instances with the state
for reservation in response["Reservations"]:
  for instance in reservation["Instances"]:
    print(f'{instance["InstanceId"]} - {instance["State"]["Name"]}')