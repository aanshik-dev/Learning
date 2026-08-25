# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3
import os

# Name of the S3 bucket and aws region
bucket_name = "aanshik-a3-web"
region = "ap-south-1"

# Create an S3 client
s3 = boto3.client("s3", region_name=region)


# Create the S3 bucket in the specified AWS region.
s3.create_bucket(
    Bucket=bucket_name,
    CreateBucketConfiguration={
        "LocationConstraint": region
    }
)

print(f"Bucket '{bucket_name}' created successfully.")


web_dir = "website"
for root, directories, files in os.walk(web_dir):
    for filename in files:
        file_path = os.path.join(root, filename)
        relative_path = os.path.relpath(
            file_path,
            web_dir
        )
        s3_key = relative_path.replace(os.sep, "/")
        # print(f"{filename} | {file_path} | {relative_path} | {s3_key}")
        s3.upload_file(
            file_path,
            bucket_name,
            s3_key
        )
        print(f"Uploaded: {s3_key}")
# aws s3 ls s3://aanshik-a3-website/ cmd to verify