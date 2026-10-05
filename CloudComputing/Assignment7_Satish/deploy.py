# Name: satish tailor
# Roll No: 2401176

import time
import boto3

# Constants and Configuration
region = "ap-south-1"
app_name = "a7-app"
env_name = "a7-app-env"
version_label = "v2"

role_name = "satish-eb-beanstalk-role"
instance_profile_name = "satish-eb-beanstalk-profile"

# S3 Bucket Configuration
bucket_name = "satish-tailor-eb"
zip_filename = "application.zip"
zip_file_path = "./application.zip"

# 1. Clients
iam = boto3.client("iam", region_name=region)
s3 = boto3.client("s3", region_name=region)
eb = boto3.client("elasticbeanstalk", region_name=region)

# 2. Setup IAM Role and Instance Profile
print("\n1. Setting up IAM Role and Instance Profile")

# Trust policy
assume_role_policy = """{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Effect": "Allow",
            "Principal": { "Service": "ec2.amazonaws.com" },
            "Action": "sts:AssumeRole"
        }
    ]
}"""

try:
    iam.create_role(
        RoleName=role_name,
        AssumeRolePolicyDocument=assume_role_policy,
        Description="Role for Elastic Beanstalk EC2 instances"
    )
    print(f"Created IAM Role: {role_name}")
except iam.exceptions.EntityAlreadyExistsException:
    print(f"IAM Role {role_name} already exists.")

# Attach required Web Tier policy
iam.attach_role_policy(
    RoleName=role_name,
    PolicyArn="arn:aws:iam::aws:policy/AWSElasticBeanstalkWebTier"
)
print("Attached AWSElasticBeanstalkWebTier policy.")

# Create Instance Profile and attach Role
try:
    iam.create_instance_profile(InstanceProfileName=instance_profile_name)
    print(f"Created Instance Profile: {instance_profile_name}")
except iam.exceptions.EntityAlreadyExistsException:
    print(f"Instance Profile {instance_profile_name} already exists.")

# Adding iam role to the instance profile
try:
    iam.add_role_to_instance_profile(
        InstanceProfileName=instance_profile_name,
        RoleName=role_name
    )
    print(f"Added role {role_name} to instance profile {instance_profile_name}.")
except iam.exceptions.LimitExceededException:
    print(f"Role {role_name} is already attached to instance profile {instance_profile_name}.")
except Exception as e:
    if "already exists" in str(e):
        print(f"Role {role_name} is already attached to instance profile {instance_profile_name}.")
    else:
        raise e

# Wait brief period for IAM setup across AWS region
print("Waiting for IAM role and profile setup")
time.sleep(10)

# 3. Create S3 Bucket and Upload Application ZIP
print("\n2. Creating S3 Bucket and uploading application bundle")

try:
    s3.create_bucket(
        Bucket=bucket_name,
        CreateBucketConfiguration={
            "LocationConstraint": region
        }
    )
    print(f"Created S3 Bucket: {bucket_name}")
except s3.exceptions.BucketAlreadyOwnedByYou:
    print(f"S3 Bucket {bucket_name} already exists.")

s3_key = f"{app_name}/{zip_filename}"
print(f"Uploading application.zip file to S3 Bucket: {bucket_name}")
s3.upload_file(zip_file_path, bucket_name, s3_key)

# 4. Create Elastic Beanstalk Application
print(f"\n3. Creating Elastic Beanstalk Application: {app_name}")
try:
    eb.create_application(
        ApplicationName=app_name,
        Description="Personal Website Application"
    )
    print("Application created.")
except eb.exceptions.ClientError as e:
    if "already exists" in str(e):
        print("Application already exists.")
    else:
        raise e

# 5. Create Application Version
print(f"\n4. Creating Application Version: {version_label}")
try:
    eb.create_application_version(
        ApplicationName=app_name,
        VersionLabel=version_label,
        SourceBundle={
            "S3Bucket": bucket_name,
            "S3Key": s3_key
        },
        AutoCreateApplication=True
    )
    print("Application Version created.")
except eb.exceptions.ClientError as e:
    if "already exists" in str(e):
        print("Application Version already exists.")
    else:
        raise e

# 6. Resolve Solution Stack
print("\n5. Determining Platform Solution Stack")
solution_stacks = eb.list_available_solution_stacks()["SolutionStacks"]
solution_stack = None
for stack in solution_stacks:
    if "Python" in stack and "64bit Amazon Linux 2023" in stack:
        solution_stack = stack
        break

if not solution_stack:
    solution_stack = "64bit Amazon Linux 2023 v4.2.0 running Python 3.12"

print(f"Selected Solution Stack: {solution_stack}")

# 7. Create Elastic Beanstalk Environment
print(f"\n6. Creating Elastic Beanstalk Environment: {env_name}")
option_settings = [
    {
        "Namespace": "aws:autoscaling:launchconfiguration",
        "OptionName": "IamInstanceProfile",
        "Value": instance_profile_name
    },
    {
        "Namespace": "aws:autoscaling:launchconfiguration",
        "OptionName": "InstanceType",
        "Value": "t3.micro"
    },
    {
        "Namespace": "aws:elasticbeanstalk:environment",
        "OptionName": "EnvironmentType",
        "Value": "SingleInstance"
    }
]

try:
    response = eb.create_environment(
        ApplicationName=app_name,
        EnvironmentName=env_name,
        VersionLabel=version_label,
        SolutionStackName=solution_stack,
        OptionSettings=option_settings
    )
    print(f"Environment creation initiated. Status: {response['Status']}")
except eb.exceptions.ClientError as e:
    if "already exists" in str(e):
        print(f"Environment '{env_name}' already exists.")
    else:
        raise e

# 8. Wait for Environment to be Ready
print("\n7. Waiting for environment deployment to become Ready")
while True:
    res = eb.describe_environments(
        ApplicationName=app_name,
        EnvironmentNames=[env_name]
    )

    env = res["Environments"][0]
    status = env.get("Status")
    health = env.get("Health")
    print(f"Status: {status} | Health: {health}")

    if status == "Ready":
        cname = env.get("CNAME")
        endpoint_url = env.get("EndpointURL")
        print("\n" + "=" * 50)
        print("DEPLOYMENT COMPLETE")
        print("=" * 50)
        print(f"Application Name : {app_name}")
        print(f"Environment Name : {env_name}")
        print(f"Health           : {health}")
        print(f"Environment URL  : http://{cname}")
        print(f"Endpoint URL     : {endpoint_url}")
        print("=" * 50)
        break

    time.sleep(30)