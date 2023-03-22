echo "Enter Credentials : "
echo "Bilal Bari - 21k-3582"
read -p "Enter Server Name : " server_name
read -p "Samba Share Name  : " share_name
read -p "Enter Username : " username
read -p "Enter Password : " password

sudo apt-get update
sudo apt-get install samba -y
sudo useradd $username
sudo smbpasswd -a $username

# Configuration
sudo echo "[$share_name]" | sudo tee -a /etc/samba/smb.conf
sudo echo "path = /srv/$share_name" | sudo tee -a /etc/samba/smb.conf
sudo echo "valid users = $username" | sudo tee -a /etc/samba/smb.conf
sudo echo "read only = no" | sudo tee -a /etc/samba/smb.conf


sudo service smbd restart
if ps aux | grep smbd | grep -v grep; then
echo "Setup Successful , Server Running"
else
echo "Setup Error , Server Not Running"
fi
