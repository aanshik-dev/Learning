# Name: Ansik Singh Tomar
# Roll No: 2401037

import boto3
import pymysql
import requests
from bs4 import BeautifulSoup

# Configuration constants
region = "ap-south-1"
rds_instance_id = "feedback-db-instance"
db_user = "admin"
db_pass = "Password123"
db_name = "feedback_db"

def get_rds_endpoint():
    """Retrieve the RDS MySQL instance endpoint dynamically using boto3."""
    rds = boto3.client("rds", region_name=region)
    response = rds.describe_db_instances(DBInstanceIdentifier=rds_instance_id)
    return response["DBInstances"][0]["Endpoint"]["Address"]

def get_ec2_public_ip():
    """Retrieve the active EC2 web server public IP dynamically."""
    ec2 = boto3.client("ec2", region_name=region)
    response = ec2.describe_instances(
        Filters=[
            {"Name": "tag:Name", "Values": ["A6-Feedback-WebServer"]},
            {"Name": "instance-state-name", "Values": ["running"]}
        ]
    )
    for res in response.get("Reservations", []):
        for inst in res.get("Instances", []):
            if inst.get("PublicIpAddress"):
                return inst["PublicIpAddress"]
    return None

def fetch_feedbacks_via_direct_db():
    """Attempt direct connection to RDS MySQL."""
    db_host = get_rds_endpoint()
    print(f"Connecting to MySQL RDS at {db_host}:3306...")
    conn = pymysql.connect(
        host=db_host,
        user=db_user,
        password=db_pass,
        database=db_name,
        connect_timeout=3,
        cursorclass=pymysql.cursors.DictCursor
    )
    with conn.cursor() as cursor:
        cursor.execute("SELECT id, name, email, message, created_at FROM feedbacks ORDER BY id DESC;")
        records = cursor.fetchall()
    conn.close()
    return records

def fetch_feedbacks_via_ec2():
    """Fetch feedbacks from EC2 Web Server (which accesses RDS from inside the VPC)."""
    public_ip = get_ec2_public_ip()
    if not public_ip:
        raise Exception("No running EC2 instance found with tag 'A6-Feedback-WebServer'.")

    print(f"Direct port 3306 blocked by local network. Fetching data via EC2 Web Server (http://{public_ip})...")
    
    # Try JSON API endpoint first
    try:
        res = requests.get(f"http://{public_ip}/api/feedbacks", timeout=5)
        if res.status_code == 200:
            return res.json().get("feedbacks", [])
    except Exception:
        pass

    # Fallback to HTML parsing from website
    res = requests.get(f"http://{public_ip}/", timeout=5)
    soup = BeautifulSoup(res.text, "html.parser")
    items = soup.find_all("div", class_="feedback-item")
    records = []
    for idx, item in enumerate(items, 1):
        name_el = item.find("span", class_="fb-name")
        email_el = item.find("span", class_="fb-email")
        time_el = item.find("span", class_="fb-time")
        msg_el = item.find("div", class_="fb-msg")

        name = name_el.text.strip() if name_el else ""
        email = email_el.text.strip().replace("<", "").replace(">", "") if email_el else ""
        time_val = time_el.text.strip() if time_el else ""
        msg = msg_el.text.strip() if msg_el else ""

        records.append({
            "id": idx,
            "name": name,
            "email": email,
            "message": msg,
            "created_at": time_val
        })
    return records

def display_records(records):
    """Print the feedback records in a clean, formatted table."""
    print("\n" + "=" * 70)
    print(f"FEEDBACK RECORDS IN RDS DATABASE (Total: {len(records)})")
    print("=" * 70)

    if not records:
        print("No feedback records found.")
    else:
        for row in records:
            print(f"ID         : {row.get('id')}")
            print(f"Name       : {row.get('name')}")
            print(f"Email      : {row.get('email')}")
            print(f"Message    : {row.get('message')}")
            print(f"Submitted  : {row.get('created_at')}")
            print("-" * 70)
    print("\nQuery completed successfully.")

if __name__ == "__main__":
    try:
        feedbacks = fetch_feedbacks_via_direct_db()
        display_records(feedbacks)
    except Exception:
        try:
            feedbacks = fetch_feedbacks_via_ec2()
            display_records(feedbacks)
        except Exception as e2:
            print("Error retrieving feedbacks:", e2)
