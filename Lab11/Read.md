<p> Summary <p><br>
<p> Introduction <p>
 <p> Squid is a popular open-source caching and proxy server that runs on Linux and Unix-like
operating systems. It provides a range of features, including caching web pages, filtering
requests, and logging user activity. Squid is commonly used by organizations to improve network
performance by reducing bandwidth usage and speeding up web page loading times for users.
Squid can also be used for content filtering, blocking access to certain websites, and enforcing
access control policies<p>
<p>Guide To Installation Of Squid<p>
<p>1. To install the squid package, run the following command:<br>
  <code>sudo apt-get update</code><br>
  <code>sudo apt-get install squid</code><br><p>
 (https://user-images.githubusercontent.com/123714188/234471968-5fe86a0b-b851-49f1-98a0-5a8b0263e583.png)

<p>2.To make configuration use the comand:<br>
  <code>sudo Gedit /etc/squi.conf</code><br><p>
https://user-images.githubusercontent.com/123714188/234471997-913c9a5f-c09b-46b3-98eb-d1b7b1f04578.png)

<p>3.Now go to black site file using comand:<br>
  <code>sudo gedit /etc/squid/blocksite</code><br>
  add all the sites you want to block<br><p>
 (https://user-images.githubusercontent.com/123714188/234472031-2f593297-a1da-488b-9cc6-670e09429b71.png)

 <p>4. Now restart squid using command:<br>
   <code>sudo systemctl restart squid</code><br><p>
 <p>5. Now go to browser Go to setting and search for proxy<p>
 <p>6. Click on settings Select manual proxy configuration and your ip and default por<p>
 <p>7. Now Browse for site you block<p>
 <p>Linux Hardening: <p>
<p>Linux hardening is the process of securing a Linux-based operating system by implementing various security measures to protect against potential threats, vulnerabilities, and attacks. It involves configuring the system to minimize potential attack vectors and reduce the risk of unauthorized access, data breaches, and system compromises.<p>
