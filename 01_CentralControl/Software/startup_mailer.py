#! /usr/bin/python
import smtplib
import urllib
from email.mime.text import MIMEText
import datetime
import time
import socket
from selenium import webdriver
from subprocess import check_output
try:
    from urllib.request import urlopen
except ImportError:
    from urllib2 import urlopen

scan_output = check_output(['iwlist', 'wlan0', 'scan'])
wlan_ssid = [line for line in scan_output.split() if line.startswith('ESSID')][0].split('"')[1]
if wlan_ssid == 'robodev_guest':
    try:
        driver = webdriver.PhantomJS(executable_path='/usr/lib/chromium-browser/chromium-browser')
        driver.get("https://10.1.254.5")
        driver.find_element_by_id("password").send_keys('robodev')
        driver.find_element_by_id("loginBtn").submit()
        time.sleep(1)
    except:
        time.sleep(1)

while True:
    try:
        result = urllib.urlopen('https://www.google.de').read()
        break
    except Exception as e:
        time.sleep(5)  
# get ip address
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(("1.1.1.1", 80))
ipaddr = s.getsockname()[0]

to = 'peiren.yang@linkit.tech,raspberry.smartfactory@linkit.tech'
gmail_user = 'raspberry.smartfactory@linkit.tech'
gmail_password = 'linkit.smartfactory.raspberry'
smtpserver = smtplib.SMTP('smtp.gmail.com', 587)
smtpserver.ehlo()
smtpserver.starttls()
smtpserver.ehlo
smtpserver.login(gmail_user, gmail_password)
today = datetime.date.today()
msg = MIMEText('Your ip is %s' % ipaddr)
msg['Subject'] = 'IP For RaspberryPi on %s' % today.strftime('%b %d %Y')
msg['From'] = gmail_user
msg['To'] = to
tries = 0
while True:
    if (tries > 60):
        exit()
    try:
        smtpserver.sendmail(gmail_user, [to], msg.as_string())
        break
    except Exception as e:
        tries = tries + 1
        time.sleep(1)
smtpserver.quit()
