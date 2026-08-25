# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3
import os
import json

# Name of the S3 bucket
bucket_name = "aanshik-a3-website"
# AWS Region
region = "ap-south-1"

# Create an S3 client
s3 = boto3.client("s3", region_name=region)

# Create the S3 bucket if it doesn't exist
try:
    if region == "us-east-1":
        s3.create_bucket(Bucket=bucket_name)
    else:
        s3.create_bucket(
            Bucket=bucket_name,
            CreateBucketConfiguration={"LocationConstraint": region}
        )
    print(f"Bucket '{bucket_name}' created successfully.")
except s3.exceptions.BucketAlreadyOwnedByYou:
    print(f"Bucket '{bucket_name}' already exists.")
except Exception as e:
    print(f"Bucket check note: {e}")

# Enable public read access on bucket so EC2 can copy files without AWS credentials
try:
    s3.delete_public_access_block(Bucket=bucket_name)
    bucket_policy = {
        "Version": "2012-10-17",
        "Statement": [
            {
                "Sid": "PublicReadGetObject",
                "Effect": "Allow",
                "Principal": "*",
                "Action": "s3:GetObject",
                "Resource": f"arn:aws:s3:::{bucket_name}/*"
            }
        ]
    }
    s3.put_bucket_policy(Bucket=bucket_name, Policy=json.dumps(bucket_policy))
    print("Public read policy applied to bucket.")
except Exception as e:
    print(f"Public access note: {e}")

# Locate website directory path dynamically
script_dir = os.path.dirname(os.path.abspath(__file__))
web_dir = os.path.join(script_dir, "website")
if not os.path.exists(web_dir):
    web_dir = os.path.join(script_dir, "..", "website")

print(f"Uploading files from directory: {web_dir}")

# Upload website files to S3 bucket and record manifest
s3_keys = []
uploaded_count = 0

for root, directories, files in os.walk(web_dir):
    for filename in files:
        file_path = os.path.join(root, filename)
        relative_path = os.path.relpath(file_path, web_dir)
        s3_key = relative_path.replace(os.sep, "/")

        s3.upload_file(file_path, bucket_name, s3_key)
        print(f"Uploaded: {s3_key}")
        s3_keys.append(s3_key)
        uploaded_count += 1

# Upload manifest.txt file listing all uploaded keys with Linux LF (\n) line endings
manifest_path = os.path.join(script_dir, "manifest.txt")
with open(manifest_path, "w", encoding="utf-8", newline="\n") as f:
    f.write("\n".join(s3_keys))

s3.upload_file(manifest_path, bucket_name, "manifest.txt")
print("Uploaded: manifest.txt")

print(f"Done. Uploaded {uploaded_count} files + manifest.txt to s3://{bucket_name}/")