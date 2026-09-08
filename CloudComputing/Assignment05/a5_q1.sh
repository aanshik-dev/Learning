#!/bin/bash

# Update packages
apt-get update -y

# Install Apache and Git
apt-get install -y apache2 git

# Start Apache
systemctl start apache2
systemctl enable apache2

# Remove default Apache page
rm -rf /var/www/html/*

# Clone website from GitHub
git clone https://github.com/aanshik-dev/cc_assignment05.git /tmp/repo

# Copy website files to Apache directory
cp -r /tmp/repo/website/* /var/www/html/

# Remove Git repository files
rm -rf /tmp/repo

# Get EC2 Instance ID using metadata
TOKEN=$(curl -s -X PUT \
"http://169.254.169.254/latest/api/token" \
-H "X-aws-ec2-metadata-token-ttl-seconds: 21600")

INSTANCE_ID=$(curl -s \
-H "X-aws-ec2-metadata-token: $TOKEN" \
"http://169.254.169.254/latest/meta-data/instance-id")

# Replace placeholder with actual Instance ID
sed -i "s/{{INSTANCE_ID}}/$INSTANCE_ID/g" /var/www/html/index.html

# Set permissions
chown -R www-data:www-data /var/www/html
chmod -R 755 /var/www/html

# Restart Apache
systemctl restart apache2

echo "Website deployed successfully"
echo "Instance ID: $INSTANCE_ID"