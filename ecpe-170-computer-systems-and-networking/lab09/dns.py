#!/usr/bin/env python3

# Python DNS query client
#
# Example usage:
#   ./dns.py --type=A --name=www.pacific.edu --server=8.8.8.8
#   ./dns.py --type=AAAA --name=www.google.com --server=8.8.8.8

# Should provide equivalent results to:
#   dig www.pacific.edu A @8.8.8.8 +noedns
#   dig www.google.com AAAA @8.8.8.8 +noedns
#   (note that the +noedns option is used to disable the pseduo-OPT
#    header that dig adds. Our Python DNS client does not need
#    to produce that optional, more modern header)


from dns_tools import dns  # Custom module for boilerplate code

import argparse
import ctypes
import random
import socket
import struct
import sys

def main():

    # Setup configuration
    parser = argparse.ArgumentParser(description='DNS client for ECPE 170')
    parser.add_argument('--type', action='store', dest='qtype',
                        required=True, help='Query Type (A or AAAA)')
    parser.add_argument('--name', action='store', dest='qname',
                        required=True, help='Query Name')
    parser.add_argument('--server', action='store', dest='server_ip',
                        required=True, help='DNS Server IP')

    args = parser.parse_args()
    qtype = args.qtype
    qname = args.qname
    server_ip = args.server_ip
    port = 53
    server_address = (server_ip, port)

    if qtype not in ("A", "AAAA"):
        print("Error: Query Type must be 'A' (IPv4) or 'AAAA' (IPv6)")
        sys.exit()


    # Define structure
    class Flags(ctypes.BigEndianStructure):
        _fields_ = [
            ("response", ctypes.c_uint16, 1),
            ("opcode", ctypes.c_uint16, 4),
            ("truncated", ctypes.c_uint16, 2),
            ("recursion_desired", ctypes.c_uint16, 1),
            ("z", ctypes.c_uint16, 2),
            ("ad_bit", ctypes.c_uint16, 1),
            ("non_auth_data", ctypes.c_uint16, 1),
            ("reserved", ctypes.c_uint16, 4)
        ]

    # Create UDP socket
    # ---------
    # STUDENT TO-DO
    # ---------
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Generate DNS request message
    # ---------
    # STUDENT TO-DO
    # ---------
    txn_id = random.randrange(0, 65535, 1)
    raw_bytes = struct.pack("!H", txn_id)
    # print("Transaction ID: %s" % hex(txn_id))
    
    flags = Flags()
    flags.response = 0 # Not a response, but a query
    flags.opcode = 0 # Standard query
    flags.truncated = 0 # Not truncated
    flags.recursion_desired = 1 # Do query recursively
    flags.z = 0 # reserved
    flags.ad_bit = 1 # AD bit: Set
    flags.non_auth_data = 0 # Non authenticated data unacceptable
    flags.reserved = 0 # Bits unused, keep 0
    raw_bytes += bytes(flags)
    
    # hex_string = "".join("%02x " % b for b in bytes(flags))
    # print("Flags: 0x%s" % hex_string)

    questions = 1
    answer_rrs = 0
    authority_rrs = 0
    additional_rrs = 0
    raw_bytes += struct.pack("!HHHH", questions, answer_rrs, authority_rrs, additional_rrs)

    domains = qname.split('.')
    # print(domains)
    for domain in domains:
        raw_bytes += struct.pack("!B", len(domain))
        raw_bytes += bytes(domain, 'ascii') # Need to change to hex encoding
    raw_bytes += struct.pack("!B", 0) # 00 to signal end of url

    if (qtype == "A"):
        raw_bytes += struct.pack("!H", 1)
    elif (qtype == "AAAA"):
        raw_bytes += struct.pack("!H", 28)
    
    raw_bytes += struct.pack("!H", 1) # Class: IN

    print("Generated request")
    print(raw_bytes.hex())

    # Send request message to server
    # (Tip: Use sendto() function for UDP)
    # ---------
    # STUDENT TO-DO
    # ---------

    print(f"Sending request for {qname}, type {qtype}, to server {server_ip}, port {port}")
    bytes_sent = s.sendto(raw_bytes, server_address)
    print("Sent %i bytes" % bytes_sent)

    # Receive message from server
    # (Tip: use recvfrom() function for UDP)
    # ---------
    # STUDENT TO-DO
    # ---------

    max_bytes = 4096
    raw_bytes = bytearray()
    (raw_bytes, src_addr) = s.recvfrom(max_bytes)


    # Close socket
    # ---------
    # STUDENT TO-DO
    # ---------

    s.close()

    # Decode DNS message and display to screen
    dns.decode_dns(raw_bytes)


if __name__ == "__main__":
    sys.exit(main())
