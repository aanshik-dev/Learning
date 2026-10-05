# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3

# Constants
region = "ap-south-1"
app_name = "a7-app"
env_name = "a7-app-env"
role_name = "aanshik-beanstalk-role"
instance_profile_name = "aanshik-beanstalk-profile"
bucket_name = "a7-beanstalk-bucket"

# 1. Clients
iam = boto3.client("iam", region_name=region)
s3 = boto3.client("s3", region_name=region)
s3_resource = boto3.resource("s3", region_name=region)
eb = boto3.client("elasticbeanstalk", region_name=region)

# 2. Terminate Elastic Beanstalk Environment (if exists)
print("\n1. Terminating Elastic Beanstalk Environment...")
try:
    eb.terminate_environment(
        EnvironmentName=env_name,
        TerminateResources=True
    )
    print(f"Termination initiated for environment: {env_name}")
except eb.exceptions.ClientError as e:
    print(f"Environment cleanup skipped/not found: {e}")

# 3. Delete Elastic Beanstalk Application (if exists)
print("\n2. Deleting Elastic Beanstalk Application...")
try:
    eb.delete_application(
        ApplicationName=app_name,
        TerminateEnvByForce=True
    )
    print(f"Deleted Elastic Beanstalk application: {app_name}")
except eb.exceptions.ClientError as e:
    print(f"Application cleanup skipped/not found: {e}")

# 4. Empty and Delete S3 Bucket
print("\n3. Deleting S3 Bucket...")
try:
    bucket = s3_resource.Bucket(bucket_name)
    # Delete all objects in bucket
    bucket.objects.all().delete()
    bucket.object_versions.all().delete()
    # Delete bucket
    s3.delete_bucket(Bucket=bucket_name)
    print(f"Deleted S3 Bucket: {bucket_name}")
except s3.exceptions.ClientError as e:
    if "NoSuchBucket" in str(e):
        print(f"S3 Bucket {bucket_name} does not exist.")
    else:
        print(f"S3 cleanup error: {e}")

# 5. Remove Role from Instance Profile & Delete Instance Profile
print("\n4. Cleaning up IAM Instance Profile...")
try:
    iam.remove_role_from_instance_profile(
        InstanceProfileName=instance_profile_name,
        RoleName=role_name
    )
    print(f"Removed role {role_name} from instance profile {instance_profile_name}.")
except iam.exceptions.NoSuchEntityException:
    print("Role was not attached to instance profile.")
except iam.exceptions.ClientError as e:
    print(f"Instance profile role removal skipped: {e}")

try:
    iam.delete_instance_profile(InstanceProfileName=instance_profile_name)
    print(f"Deleted Instance Profile: {instance_profile_name}")
except iam.exceptions.NoSuchEntityException:
    print(f"Instance Profile {instance_profile_name} does not exist.")
except iam.exceptions.ClientError as e:
    print(f"Instance profile deletion skipped: {e}")

# 6. Detach Policy and Delete IAM Role
print("\n5. Cleaning up IAM Role...")
try:
    iam.detach_role_policy(
        RoleName=role_name,
        PolicyArn="arn:aws:iam::aws:policy/AWSElasticBeanstalkWebTier"
    )
    print(f"Detached AWSElasticBeanstalkWebTier policy from {role_name}.")
except iam.exceptions.NoSuchEntityException:
    print("Policy was not attached to role.")
except iam.exceptions.ClientError as e:
    print(f"Policy detachment skipped: {e}")

try:
    iam.delete_role(RoleName=role_name)
    print(f"Deleted IAM Role: {role_name}")
except iam.exceptions.NoSuchEntityException:
    print(f"IAM Role {role_name} does not exist.")
except iam.exceptions.ClientError as e:
    print(f"Role deletion skipped: {e}")

print("\nCleanup process finished.")
