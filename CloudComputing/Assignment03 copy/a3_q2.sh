#!/bin/bash
export DEBIAN_FRONTEND=noninteractive

# Wait for any background cloud-init dpkg/apt lock to be released
while fuser /var/lib/dpkg/lock-frontend >/dev/null 2>&1 || fuser /var/lib/apt/lists/lock >/dev/null 2>&1; do
    sleep 2
done

# Update package manager and install Apache & curl
apt-get update -y
apt-get install -y apache2 curl

# Stop Apache during setup
systemctl stop apache2

# Remove default Apache html files completely
rm -rf /var/www/html
mkdir -p /var/www/html

# Download manifest.txt listing all website files and clean any carriage returns (\r)
curl -sL https://aanshik-a3-website.s3.ap-south-1.amazonaws.com/manifest.txt | tr -d '\r' > /tmp/manifest.txt

# Download every website file from S3 into /var/www/html/
while IFS= read -r file_key; do
    file_key=$(echo "$file_key" | tr -d '\r')
    if [ -n "$file_key" ]; then
        dir_name=$(dirname "$file_key")
        if [ "$dir_name" != "." ]; then
            mkdir -p "/var/www/html/$dir_name"
        fi
        curl -sL "https://aanshik-a3-website.s3.ap-south-1.amazonaws.com/$file_key" -o "/var/www/html/$file_key"
    fi
done < /tmp/manifest.txt

# Set ownership and permissions for Apache
chown -R www-data:www-data /var/www/html
chmod -R 755 /var/www/html

# Restart Apache web server
systemctl start apache2
systemctl enable apache2