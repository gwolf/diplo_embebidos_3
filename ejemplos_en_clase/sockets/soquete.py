#!/usr/bin/python
# *-* Encoding: utf-8

import socket
import sys
import os

server = '/tmp/socket'
try:
  os.unlink(server)
except OSError:
  pass

sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
sock.bind(server)

sock.listen(1)

while True:
  connection, client = sock.accept()
  while True:
    data = connection.recv(10)
    if data:
      print "Me dijeron: %s" % data
      connection.send("OK!\n")
    else:
      print "Fin de comunicación"
      break
