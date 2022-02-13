#!/usr/bin/python3

# Usage:
#  ./display.py --help
#  ./display.py --port=??? --url=????
#
# Example commands:
#  ./display.py --port=80 --url=http://ut-images.s3.amazonaws.com/wp-content/uploads/2009/09/SED_wall_1920x1200.jpg
#  ./display.py --port=80 --url=http://www.personal.psu.edu/users/m/e/mel992/space_shuttle_13.jpg

import argparse
import string
import socket
import sys
import os
from subprocess import call
from urllib.parse import urlparse

# Size of receive buffer.
# Maximum number of bytes to get from network in one recv() call
max_recv = 64*1024

# Setup configuration
parser = argparse.ArgumentParser(description='Download client for ECPE 170')
parser.add_argument('--url', 
                    action='store',
                    dest='url', 
                    required=True,
                    help='URL of file to download')
parser.add_argument('--port', 
                    action='store',
                    dest='port', 
                    required=True,
                    help='Port number of web server')

args = parser.parse_args()
url = args.url
port = int(args.port)

print("Running download client")
print("Download url: %s" % url)
print("Download port number: %i" % port)

# Split URL into "host", "path", and "filename" variables.
# http://www.google.com/images/srpr/logo3w.png
#  * host=www.google.com
#  * path=/images/srpr
#  * file=logo3w.png

u = urlparse(url)
print("Parsing URL:")
print(" * scheme=%s" % u.scheme)
print(" * netloc=%s" % u.netloc)
print(" * path+file=%s" % u.path)
print(" * path=%s" % os.path.dirname(u.path))
print(" * file=%s" %os.path.basename(u.path))
print()

# Download file (image) from http://host/path/filename
host = u.netloc
path = os.path.dirname(u.path) + '/'
filename = os.path.basename(u.path)

print("Preparing to download object from http://" + host + path + filename)


# *****************************
# STUDENT WORK: 
#  (1) Build the HTTP request string to send to the server
#      and *print it* on the screen.
#
#      Requirements:
#        HTTP 1.1
#        Use the Host header
#        Request the connection be closed after response sent.
#
#      Tip: What is the important sequence of characters that
#      must be provided at the end of the HTTP client request
#      to the server? (otherwise, the server won't begin processing)
# *****************************

request = "GET {} HTTP/1.1\r\n".format(u.path)
request += "Host: {}\r\n".format(u.netloc)
request += "Connection: close\r\n\r\n"
print("\nSending HTTP Request")
print("--------------------")
print(request)

# *****************************
# STUDENT WORK: 
#  (2) Create a TCP socket (SOCK_STREAM)
#  (3) Connect to the remote host using the socket
#  (4) Send the HTTP request to the remote host.
#      Tip: Look at the demo client program to see how
#      to convert a unicode string to a byte array
#      prior to transmitting it.
# *****************************

# Create TCP socket
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error as msg:
    print("Error: could not create socket")
    print("Description: " + str(msg))
    sys.exit()

# Override port if port found in url
if u.port != None:
    print("Port found in URL, overriding port in argument")
    port = u.port
    netloc = u.netloc[:-(len(str(port)) + 1)]
    print(netloc)
else:
    netloc = u.netloc
# Connect to server

print("Connecting to server at " + netloc + " on port " + str(port))

try:
    s.connect((netloc , port))
except socket.error as msg:
    print("Error: Could not open connection")
    print("Description: " + str(msg))
    sys.exit()

print("Connection established")

# Send message to server
raw_bytes = bytes(request,'ascii')

try:
    # Send the string
    # Note: send() might not send all the bytes!
    # You should loop, or use sendall()
    s.sendall(raw_bytes)
except socket.error as msg:
    print("Error: send() failed")
    print("Description: " + str(msg))
    sys.exit()

# *****************************
# STUDENT WORK: 
#  (5) Receive everything the remote host sends us
#      in chunks of 'max_recv' bytes (64kB).
#      When the server finishes sending us the data,
#      it will close the socket. That is detected locally
#      by receiving an array of length ZERO
#      (i.e. no bytes received)
#  (6) Close the socket - finished with the network now
# *****************************

# Receive data

print("Receiving data...");
try:
    received_raw_bytes = s.recv(max_recv)
except socket.error as msg:
    print("Error: unable to recv()")
    print("Description: " + str(msg))
    sys.exit()

while True:
    try:
        more_raw_bytes = s.recv(max_recv)
    except socket.error as msg:
        print("Error: unable to recv()")
        print("Description: " + str(msg))
        sys.exit()
    if len(more_raw_bytes) == 0:
        break
    received_raw_bytes += more_raw_bytes

s.close()

print("Received %d bytes" % len(received_raw_bytes))

# *****************************
# STUDENT WORK: 
#  (7) Split the response into two parts:
#        1.) The part before the \r\n\r\n sequence - the HEADER
#        2.) The part after the \r\n\r\n sequence - the DATA
#  (8) Print the HEADER out on the screen - it's ASCII text
#  (9) Save the DATA to disk as a binary file. Somewhere
#      in the /tmp directory would be a great spot.
# *****************************

sequenceIndex = received_raw_bytes.find(bytes("\r\n\r\n", 'ascii'))
header = received_raw_bytes[:sequenceIndex].decode('ascii')
data = received_raw_bytes[sequenceIndex+4:] #+4 because data after \r\n\r\n sequence

print("\nHTTP Response Header")
print("--------------------")
print(header)

saved_filename = "/tmp/{}".format(os.path.basename(u.path))

file = open(saved_filename, "wb")
file.write(data)
file.close()

print("--------------------")
print("File saved to %s"%saved_filename)

# *****************************
# END OF STUDENT WORK
# *****************************

# Assuming you downloaded the image, and placed its path/filename
# in the variable 'saved_filename', use the 'eog' utility to 
# display the image on screen
call(["eog", saved_filename])
