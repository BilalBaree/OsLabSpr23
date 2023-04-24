#!/bin/bash

echo "Setup Shell Commands For Task2"
sudo apt-get update
sudo apt-get install mailutils
sudo apt-get install postfix
sudo systemctl restart postfix
