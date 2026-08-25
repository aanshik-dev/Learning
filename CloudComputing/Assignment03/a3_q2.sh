#!/bin/bash

# Update the package manager.
apt-get update -y

# Install Apache web server and AWS CLI.
apt-get install -y apache2 awscli

# Start Apache and configure it to start automatically on boot.
systemctl start apache2
systemctl enable apache2

# Remove the default Apache website.
rm -rf /var/www/html/*

# Copy all website files from the S3 bucket to Apache's web directory.
aws s3 cp s3://aanshik-a3-web/ /var/www/html/ --recursive

# Set appropriate ownership for Apache.
chown -R www-data:www-data /var/www/html

# Set read and execute permissions for the website files.
chmod -R 755 /var/www/html