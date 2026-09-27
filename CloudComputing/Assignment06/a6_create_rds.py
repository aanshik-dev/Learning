# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3

# Constants
region = "ap-south-1"
security_group_name = "rds-secgroup"
db_instance_id = "feedback-db-instance"
db_name = "feedback_db"
master_username = "admin"
master_password = "Password123"

# 1. Clients
ec2 = boto3.client("ec2", region_name=region)
rds = boto3.client("rds", region_name=region)

# 2. Get Default VPC
print("\nFinding VPC...")
vpcs = ec2.describe_vpcs(
    Filters=[{"Name": "is-default", "Values": ["true"]}]
)

if not vpcs["Vpcs"]:
    vpcs = ec2.describe_vpcs()

vpc_id = vpcs["Vpcs"][0]["VpcId"]
print("VPC ID:", vpc_id)

# 3. Create or Get Security Group
print("\nChecking Security Group...")
try:
    sg_response = ec2.create_security_group(
        GroupName=security_group_name,
        Description="Security Group for MySQL RDS",
        VpcId=vpc_id
    )
    sg_id = sg_response["GroupId"]
    print("Security Group Created:", sg_id)

    # Authorize MySQL Port 3306 Inbound Rule
    ec2.authorize_security_group_ingress(
        GroupId=sg_id,
        IpPermissions=[
            {
                "IpProtocol": "tcp",
                "FromPort": 3306,
                "ToPort": 3306,
                "IpRanges": [{"CidrIp": "0.0.0.0/0"}]
            }
        ]
    )
    print("Opened Port 3306 to all traffic")

except ec2.exceptions.ClientError as e:
    if "InvalidGroup.Duplicate" in str(e):
        sg_response = ec2.describe_security_groups(
            GroupNames=[security_group_name]
        )
        sg_id = sg_response["SecurityGroups"][0]["GroupId"]
        print("Using existing Security Group:", sg_id)
    else:
        raise

# 4. Create MySQL RDS Instance
print("\nCreating RDS MySQL Instance...")
try:
    response = rds.create_db_instance(
        DBInstanceIdentifier=db_instance_id,
        AllocatedStorage=20,
        DBInstanceClass="db.t3.micro",
        Engine="mysql",
        MasterUsername=master_username,
        MasterUserPassword=master_password,
        DBName=db_name,
        VpcSecurityGroupIds=[sg_id],
        PubliclyAccessible=True,
        MultiAZ=False,
        AutoMinorVersionUpgrade=True
    )
    print("RDS Instance creation initiated")

except rds.exceptions.DBInstanceAlreadyExistsFault:
    print("RDS Instance already exists")

# 5. Wait for RDS Instance to be Available
print("\nWaiting for RDS Instance to become available...")
waiter = rds.get_waiter("db_instance_available")
waiter.wait(
    DBInstanceIdentifier=db_instance_id,
    WaiterConfig={"Delay": 30, "MaxAttempts": 30}
)

# 6. Retrieve and Print RDS Endpoint
db_details = rds.describe_db_instances(
    DBInstanceIdentifier=db_instance_id
)
endpoint = db_details["DBInstances"][0]["Endpoint"]["Address"]
port = db_details["DBInstances"][0]["Endpoint"]["Port"]

print("\nRDS INSTANCE DETAILS")
print("Instance Identifier:", db_instance_id)
print("Database Name:", db_name)
print("Endpoint Host:", endpoint)
print("Port:", port)
print("Master Username:", master_username)