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
 ![Screenshot from 2023-04-26 09-26-09](https://user-images.githubusercontent.com/123714188/234472487-aad0a073-6168-4587-b13a-9f8f58a58538.png)
<p>2.To make configuration use the comand:<br>
  <code>sudo Gedit /etc/squi.conf</code><br><p>
   ![Screenshot from 2023-04-26 09-40-49](https://user-images.githubusercontent.com/123714188/234472518-18d76636-e1b3-42ae-8b60-ddeb97b493bb.png)
<p>3.Now go to black site file using comand:<br>
  <code>sudo gedit /etc/squid/blocksite</code><br>
  add all the sites you want to block<br><p>
![Screenshot from 2023-04-26 09-41-03](https://user-images.githubusercontent.com/123714188/234472530-d2e75294-22de-4247-96d8-d3b8c7b3a194.png)
   <code>sudo systemctl restart squid</code><br><p>
 <p>5. Now go to browser Go to setting and search for proxy<p>
 <p>6. Click on settings Select manual proxy configuration and your ip and default por<p>
 <p>7. Now Browse for site you block<p>
 <p>Linux Hardening: <p>
<p>Linux hardening is the process of securing a Linux-based operating system by implementing various security measures to protect against potential threats, vulnerabilities, and attacks. It involves configuring the system to minimize potential attack vectors and reduce the risk of unauthorized access, data breaches, and system compromises.<p>
