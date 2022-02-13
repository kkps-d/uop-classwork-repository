#!/usr/bin/env python3

import socket
import struct
import ctypes
import sys

def main():
    server_addr = ("cyberlab.pacific.edu", 3456) # Server address information
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # Create a UDP socket

    protocol_version = 1 # Protocol version 1
    integer_1 = 5 # First integer to send
    integer_2 = 10 # Second integer to send
    name = "Kaung Khant Pyae Sone" # Name
    name_length = len(name) # Length of name

    # Encode data into bytes
    raw_bytes = bytearray()
    raw_bytes += struct.pack("!B", protocol_version) # Protocol version 1
    raw_bytes += struct.pack("!L", integer_1) # First integer
    raw_bytes += struct.pack("!L", integer_2) # Second integer
    raw_bytes += struct.pack("!L", name_length) # Length of name
    raw_bytes += bytes(name, 'ascii') # Name

    s.sendto(raw_bytes, server_addr) # Send request to server
    
    bytes_received = bytearray()
    (bytes_received, src_addr) = s.recvfrom(4096) # Receive response from server

    # Decode bytes into data
    (res_protocol_version, res_status, res_integer) = struct.unpack("!BHL", bytes_received)
    
    # Print out decoded data
    if res_status == 1:
        print("Success")
    else:
        print("Failure")
    print("%i + %i = %i" % (integer_1, integer_2, res_integer))    

if __name__ == "__main__":
    sys.exit(main())