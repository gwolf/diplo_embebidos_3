#!/usr/bin/python
# *-* Encoding: utf-8

import socket
import sys
import os

server = ('localhost', 2000)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
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
