
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server
# the program runs the ping command, and emails the result using smtp.gmail.com

# NOTE: Do not forget to allow login from less secure apps in your gmail account. Otherwise gmail will complain about username and password.


import smtplib, ssl
import subprocess

port = 465  # For SSL
email_address = raw_input("Please enter your email address: ")
password = raw_input("Please enter your password: ")
receiver_email = raw_input("Please enter receiver's email address: ")


# ping google.com and save the result
ping = subprocess.Popen(["ping","-c 2","google.com"],stdout=subprocess.PIPE).stdout.read()


# Connecting to the gmail smtp and port
print '\nNow contacting the mail server...'
server = smtplib.SMTP_SSL('smtp.gmail.com', port)
server.ehlo()

print '\nSending email...'

# Creating our subject and text
SUBJECT = 'Server ping result! Tamir Enkhjargal'
TEXT = 'I have pinged google.com and the result is attached to this email:\n\n' + ping
message = 'Subject: {}\n\n{}'.format(SUBJECT, TEXT)

# Login and send email
server.login(email_address, password)
server.sendmail(email_address, receiver_email, message)

