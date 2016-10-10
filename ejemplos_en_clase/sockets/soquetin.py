#!/usr/bin/python
# *-* Encoding: utf-8
import socket
import sys
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
server = '/tmp/socket'
try:
  sock.connect(server)
except socket.error, msg:
  print msg
  sys.exit(1)

try:
  sock.sendall("Blá bla bla bla blá. Bla bla blá bla, bla blá.")
  while True:
    data = sock.recv(16)
    print data
finally:
  sock.close()
