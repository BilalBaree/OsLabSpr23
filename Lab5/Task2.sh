#!/bin/bash

# Prompt user for email details
read -p "Enter recipient email address: " to_email
read -p "Enter sender email address: " from_email
read -p "Enter email subject: " email_subject
read -p "Enter email message body: " email_body

# Send email using mail command
echo "$email_body" | mail -s "$email_subject" -a "From: $from_email" "$to_email"
