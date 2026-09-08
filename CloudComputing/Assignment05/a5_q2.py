# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3

# constants
region = "ap-south-1"
ubuntu_ami = "ami-01a00762f46d584a1"

# website and script path
startup_file ="D:/Coding/Learning/CloudComputing/Assignment05/a5_q1.sh"

# clients
ec2 = boto3.client("ec2", region_name=region)

# Reading Script File
with open(startup_file, "r") as f:
    startup_script = f.read()

# Creating the Security Group
try:
    security_grp = ec2.create_security_group(
      GroupName="ec2-sg",
      Description="Allow SSH and HTTP traffic"
    )

    grpId = security_grp["GroupId"]
    print("Security Group Created with ID:", grpId)

    ec2.authorize_security_group_ingress(
      GroupId=grpId,
      IpPermissions=[
        {
          "IpProtocol": "tcp",
          "FromPort": 80,
          "ToPort": 80,
          "IpRanges": [
            {
              "CidrIp": "0.0.0.0/0",
              "Description": "Allow http traffic"
            }
          ]
        },
        {
          "IpProtocol": "tcp",
          "FromPort": 22,
          "ToPort": 22,
          "IpRanges": [
              {
                  "CidrIp": "0.0.0.0/0",
                  "Description": "Allow SSH traffic"
              }
          ]
        }
      ]
    )
    print("HTTP:80 and SSH:22 ports opened")
except ec2.exceptions.ClientError as e:
    if "InvalidGroup.Duplicate" in str(e):
        grpId = ec2.describe_security_groups(GroupNames=["ec2-sg"])["SecurityGroups"][0]["GroupId"]
        print(f"Using existing Security Group: {grpId}")
    else:
        raise e


# Creating EC2 Instance
instance = ec2.run_instances(
  ImageId=ubuntu_ami,
  InstanceType="t3.micro",
  MinCount=1,
  MaxCount=1,
  SecurityGroupIds=[grpId],
  UserData=startup_script,
  KeyName="iam-key-pair"
)

# Instance ID
instanceId = instance["Instances"][0]["InstanceId"]
print("Instance Created with ID: ", instanceId)


# waiting for instance to enter running state
print("Waiting for instance to enter running state...")
waiter = ec2.get_waiter("instance_running")
waiter.wait(InstanceIds=[instanceId])
print("Instance is now running!")

# getting the instance details
instance_desc = ec2.describe_instances(InstanceIds=[instanceId])
instance = instance_desc["Reservations"][0]["Instances"][0]

public_dns = instance["PublicDnsName"]
public_ip = instance["PublicIpAddress"]

print(f"Public DNS Address: {public_dns}")
print(f"Public IP Address:  http://{public_ip}")


# History
# Policy
# Cloud Watch Alarms
# ASG
# Instance
# Launch Template