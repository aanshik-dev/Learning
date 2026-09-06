# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3
import time
import base64

# Constants
region = "ap-south-1"
ubuntu_ami = "ami-01a00762f46d584a1"
security_group_name = "ec2-sg"
iamRole = "aanshik-ec2-s3-role"
launch_template_name = "a5-web-launch-template"
asg_name = "a5-web-asg"

# 1. Clients
ec2 = boto3.client("ec2",region_name=region)
autoscaling = boto3.client("autoscaling",region_name=region)
cloudwatch = boto3.client("cloudwatch",region_name=region)


# 2. Get Existing Security Group
print("\nFinding existing Security Group...")
response = ec2.describe_security_groups(
    GroupNames=[security_group_name]
)
grpId = response["SecurityGroups"][0]["GroupId"]
print("Security Group:", grpId)

# 3. Read Startup Script
startup_file = ("D:/Coding/Learning/CloudComputing/Assignment05/a5_q1.sh")

with open(startup_file, "r") as f:
    startup_script = f.read()
print("Startup script loaded")

userdata = base64.b64encode(
    startup_script.encode()
).decode()

# 4. Find a Subnet in Mumbai
print("\nFinding subnet...")
subnets = ec2.describe_subnets(
    Filters=[
        {
            "Name": "availability-zone",
            "Values": ["ap-south-1a"]
        }
    ]
)

if not subnets["Subnets"]:
    raise Exception("No subnet found in ap-south-1a")

subnet_id = subnets["Subnets"][0]["SubnetId"]
availability_zone = subnets["Subnets"][0]["AvailabilityZone"]
print("Subnet ID:", subnet_id)
print("Availability Zone:", availability_zone)


# 5. Create Launch Template
print("\nCreating Launch Template...")
try:
    response = ec2.create_launch_template(
        LaunchTemplateName=launch_template_name,
        LaunchTemplateData={
            "ImageId": ubuntu_ami,
            "InstanceType": "t3.micro",
            "SecurityGroupIds": [
                grpId
            ],
            "IamInstanceProfile": {
                "Name": iamRole
            },
            "UserData": userdata,
            "KeyName": "iam-key-pair"
        }
    )

    launch_template_id = response["LaunchTemplate"]["LaunchTemplateId"]
    print("Launch Template Created:",launch_template_id)

except ec2.exceptions.ClientError as e:
    if "InvalidLaunchTemplateName.AlreadyExistsException" in str(e):
        response = ec2.describe_launch_templates(
            LaunchTemplateNames=[
                launch_template_name
            ]
        )
        launch_template_id = response["LaunchTemplates"][0]["LaunchTemplateId"]
        print("Using existing Launch Template:",launch_template_id)
    else:
        raise

# 6. Create Auto Scaling Group
print("\nCreating Auto Scaling Group...")
try:
    autoscaling.create_auto_scaling_group(
        AutoScalingGroupName=asg_name,
        LaunchTemplate={
            "LaunchTemplateId": launch_template_id,
            "Version": "$Latest"
        },
        MinSize=1,
        MaxSize=3,
        DesiredCapacity=1,
        VPCZoneIdentifier=subnet_id,
        HealthCheckType="EC2",
        HealthCheckGracePeriod=120
    )
    print("Auto Scaling Group created")

except autoscaling.exceptions.AlreadyExistsFault:
    print("Auto Scaling Group already exists")


# 7. Create Scale-Out Policy
print("\nCreating Scale Policy")
scale_out = autoscaling.put_scaling_policy(
    AutoScalingGroupName=asg_name,
    PolicyName="a5-scale-out",
    PolicyType="SimpleScaling",
    AdjustmentType="ChangeInCapacity",
    ScalingAdjustment=1,
    Cooldown=120
)
scale_out_arn = scale_out["PolicyARN"]
print("Scale-Out Policy created")


# 8. Create Scale-In Policy
scale_in = autoscaling.put_scaling_policy(
    AutoScalingGroupName=asg_name,
    PolicyName="a5-scale-in",
    PolicyType="SimpleScaling",
    AdjustmentType="ChangeInCapacity",
    ScalingAdjustment=-1,
    Cooldown=120
)
scale_in_arn = scale_in["PolicyARN"]
print("Scale-In Policy created")

print("\nCreating CloudWatch Alarm")
# 9. CloudWatch Scale-Out Alarm
cloudwatch.put_metric_alarm(
    AlarmName="a5-cpu-high",
    AlarmDescription=(
        "Scale out when average CPU is "
        "greater than or equal to 20% for 2 minutes"
    ),
    Namespace="AWS/EC2",
    MetricName="CPUUtilization",
    Dimensions=[
        {
            "Name": "AutoScalingGroupName",
            "Value": asg_name
        }
    ],
    Statistic="Average",
    Period=60,
    EvaluationPeriods=2,
    DatapointsToAlarm=2,
    Threshold=20,
    ComparisonOperator="GreaterThanOrEqualToThreshold",
    AlarmActions=[
        scale_out_arn
    ]
)
print("Scale-Out Alarm created")


# 10. CloudWatch Scale-In Alarm
cloudwatch.put_metric_alarm(
    AlarmName="a5-cpu-low",
    AlarmDescription=(
        "Scale in when average CPU is "
        "less than or equal to 30% for 2 minutes"
    ),
    Namespace="AWS/EC2",
    MetricName="CPUUtilization",
    Dimensions=[
        {
            "Name": "AutoScalingGroupName",
            "Value": asg_name
        }
    ],
    Statistic="Average",
    Period=60,
    EvaluationPeriods=2,
    DatapointsToAlarm=2,
    Threshold=30,
    ComparisonOperator="LessThanOrEqualToThreshold",
    AlarmActions=[
        scale_in_arn
    ]
)
print("Scale-In Alarm created")

# 11. Wait for ASG Instance
print("\nWaiting for Auto Scaling Group...")
time.sleep(60)

# 12. Get ASG Details
response = autoscaling.describe_auto_scaling_groups(
    AutoScalingGroupNames=[asg_name]
)
asg = response["AutoScalingGroups"][0]

print("AUTO SCALING GROUP")
print("ASG Name:", asg["AutoScalingGroupName"])
print("Min Size:", asg["MinSize"])
print("Max Size:", asg["MaxSize"])
print("Desired Capacity:", asg["DesiredCapacity"])
print("Instances:")
for instance in asg["Instances"]:
    instance_id = instance["InstanceId"]
    instance_response = ec2.describe_instances(
        InstanceIds=[instance_id]
    )
    instance_details = instance_response["Reservations"][0]["Instances"][0]

    public_ip = instance_details.get("PublicIpAddress")
    public_dns = instance_details.get("PublicDnsName")
    print("  Instance ID:", instance_id, " | Public IP:", public_ip, " | Public DNS:", public_dns)

    # ssh -i "D:\Coding\Learning\CloudComputing\aws\iam-key-pair.pem" ubuntu@0.0.0.0
    # stress --cpu 1 --timeout 180