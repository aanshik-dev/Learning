# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3
import os

# Configuration constants
region = "ap-south-1"
ubuntu_ami = "ami-01a00762f46d584a1"  # Ubuntu 24.04 in ap-south-1
key_name = "iam-key-pair"
security_group_name = "ec2-feedback-sg"
rds_instance_id = "feedback-db-instance"
db_user = "admin"
db_pass = "Password123"
db_name = "feedback_db"

# Path to the startup script
script_path = os.path.join(os.path.dirname(__file__), "a6_script.sh")

# 1. Initialize AWS Clients
ec2 = boto3.client("ec2", region_name=region)
rds = boto3.client("rds", region_name=region)

# 2. Retrieve RDS Endpoint dynamically
print("Fetching RDS instance details...")
rds_details = rds.describe_db_instances(DBInstanceIdentifier=rds_instance_id)
db_endpoint = rds_details["DBInstances"][0]["Endpoint"]["Address"]
print(f"RDS Endpoint: {db_endpoint}")

# 3. Get Default VPC
print("\nFinding VPC...")
vpcs = ec2.describe_vpcs(Filters=[{"Name": "is-default", "Values": ["true"]}])
if not vpcs["Vpcs"]:
    vpcs = ec2.describe_vpcs()
vpc_id = vpcs["Vpcs"][0]["VpcId"]
print(f"VPC ID: {vpc_id}")

# 4. Create or Get EC2 Security Group
print("\nChecking Security Group...")
try:
    sg_response = ec2.create_security_group(
        GroupName=security_group_name,
        Description="Security Group for Web Feedback App (HTTP 80, SSH 22)",
        VpcId=vpc_id
    )
    sg_id = sg_response["GroupId"]
    print(f"Created Security Group: {sg_id}")

    # Authorize HTTP (80) and SSH (22)
    ec2.authorize_security_group_ingress(
        GroupId=sg_id,
        IpPermissions=[
            {
                "IpProtocol": "tcp",
                "FromPort": 80,
                "ToPort": 80,
                "IpRanges": [{"CidrIp": "0.0.0.0/0", "Description": "Allow HTTP"}]
            },
            {
                "IpProtocol": "tcp",
                "FromPort": 22,
                "ToPort": 22,
                "IpRanges": [{"CidrIp": "0.0.0.0/0", "Description": "Allow SSH"}]
            }
        ]
    )
    print("Opened Port 80 (HTTP) and Port 22 (SSH)")
except ec2.exceptions.ClientError as e:
    if "InvalidGroup.Duplicate" in str(e):
        sg_response = ec2.describe_security_groups(
            Filters=[
                {"Name": "group-name", "Values": [security_group_name]},
                {"Name": "vpc-id", "Values": [vpc_id]}
            ]
        )
        sg_id = sg_response["SecurityGroups"][0]["GroupId"]
        print(f"Using existing Security Group: {sg_id}")
    else:
        raise

# 5. Read and prepare UserData Startup Script
with open(script_path, "r") as f:
    raw_user_data = f.read()

user_data_script = (
    raw_user_data
    .replace("__DB_HOST__", db_endpoint)
    .replace("__DB_USER__", db_user)
    .replace("__DB_PASS__", db_pass)
    .replace("__DB_NAME__", db_name)
)

# 6. Launch EC2 Instance with UserData
print("\nLaunching EC2 Instance...")
run_response = ec2.run_instances(
    ImageId=ubuntu_ami,
    InstanceType="t3.micro",
    MinCount=1,
    MaxCount=1,
    SecurityGroupIds=[sg_id],
    UserData=user_data_script,
    KeyName=key_name,
    TagSpecifications=[
        {
            "ResourceType": "instance",
            "Tags": [{"Key": "Name", "Value": "A6-Feedback-WebServer"}]
        }
    ]
)

instance_id = run_response["Instances"][0]["InstanceId"]
print(f"Instance created with ID: {instance_id}")

# 7. Wait for Instance to enter running state
print("\nWaiting for instance to enter running state...")
waiter = ec2.get_waiter("instance_running")
waiter.wait(InstanceIds=[instance_id])
print("Instance is now running!")

# 8. Retrieve Public DNS and Public IP
desc_response = ec2.describe_instances(InstanceIds=[instance_id])
instance_info = desc_response["Reservations"][0]["Instances"][0]
public_dns = instance_info.get("PublicDnsName", "")
public_ip = instance_info.get("PublicIpAddress", "")

print("\n" + "=" * 50)
print("EC2 DEPLOYMENT COMPLETED")
print("=" * 50)
print(f"Instance ID : {instance_id}")
print(f"Public DNS  : http://{public_dns}")
print(f"Public IP   : http://{public_ip}")
print("=" * 50)
print("Note: Please wait ~1-2 minutes for UserData startup script to finish package installations and launch Flask.")