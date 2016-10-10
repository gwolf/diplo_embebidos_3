#!/usr/bin/ruby
# coding: utf-8
require 'socket'

server = TCPServer.new 2000

def procesa(client)
  while true
    data = client.gets(16)
    if data
      print "Me dijeron: %s" % data
      client.puts("OK!\n")
    else
      print "Fin de comunicación"
      return 0
    end
  end
end

loop do
  client = server.accept
  procesa(client)
  client.close
end
