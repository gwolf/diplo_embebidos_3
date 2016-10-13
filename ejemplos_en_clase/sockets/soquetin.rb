#!/usr/bin/ruby
# coding: utf-8
require 'socket'

socket = UNIXSocket.new("/tmp/socket")

# Goes interactive mode
socket.puts("Blá bla bla bla blá. Bla bla blá bla, bla blá.")

while true
  data = socket.recv(16)
  print data
end
