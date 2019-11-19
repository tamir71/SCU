
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server

# Note:
# Run a local smtp mail server using the following command before running this code:
# python -m smtpd -c DebuggingServer -n localhost:6000


from socket import *
import ssl


# Choose a mail server
mailserver = 'localhost'


# Create socket called clientSocket and establish a TCP connection with mailserver
clientSocket = socket(AF_INET, SOCK_STREAM)

# Port number may change according to the mail server
serverPort = 6000
serverAddr = (mailserver,serverPort)
clientSocket.connect(serverAddr)

recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '220':
    print('220 reply not received from server.')


# Send HELO command along with the server address
HELOmsg = "HELO localhost:6000\r\n"
HELOmsg = HELOmsg.encode()
clientSocket.send(HELOmsg)

recv = clientSocket.recv(1024).decode()
print(recv)

# Send MAIL FROM command and print server response
MAILfrm = "MAIL FROM: tenk@localhost.com\r\n"
MAILfrm = MAILfrm.encode()
clientSocket.send(MAILfrm)

recv = clientSocket.recv(1024).decode()
print(recv)

# Send RCPT TO command and print server response
RCPTto = "RCPT TO: coen146@localhost.com\r\n"
RCPTto = RCPTto.encode()
clientSocket.send(RCPTto)

recv = clientSocket.recv(1024).decode()
print(recv)

# Send DATA command and print server response
DATAmsg = "DATA\r\n"
DATAmsg = DATAmsg.encode()
clientSocket.send(DATAmsg)

recv = clientSocket.recv(1024).decode()
print(recv)

# Send message data.
msg = "SUBJECT: Greeting To you!\nThis is line1\nThis is line 2.\n"

# Message to send
msg = msg.encode()
clientSocket.send(msg)

# Message ends with a single period
msg = "\r\n.\r\n"
msg = msg.encode()
clientSocket.send(msg)

recv = clientSocket.recv(1024).decode()
print(recv)

# Send QUIT command and get server response
QUITmsg = "QUIT\r\n"
QUITmsg = QUITmsg.encode()
clientSocket.send(QUITmsg)

recv = clientSocket.recv(1024).decode()
print(recv)

