#!/bin/bash

# Install Apache, MySQL, and PHP
echo "Installing Apache, MySQL, and PHP..."
sudo apt update
sudo apt install apache2 mysql-server php libapache2-mod-php php-mysql

# Restart Apache server
echo "Restarting Apache server..."
sudo systemctl restart apache2

# Start MySQL server
echo "Starting MySQL server..."
sudo systemctl start mysql
