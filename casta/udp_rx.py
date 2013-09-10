#!/usr/bin/python
#
import socket, subprocess

UDP_IP = ""   # local  IP address (all ports)
UDP_PORT = 4011         # And port

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    f = open("/run/pipelights.fifo", "w+")
    f.write(data)
    f.close()
    #print "received message:\n", data
