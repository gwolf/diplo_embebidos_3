# Monytor

This is a simple client-server sensors administrator, the objective is to
serve us as a little framework to manage a different class of sensors.

This is under development, so there is still a lot of work to do, but for now
we have some headers:

- monyt_socket - This file exist to make us easy the manage of a unix socket that we will use as a communication channel between the sensors and the server.
- monyt_manage_thread - This file is for manage the threads that will be created onece a connection is accepted on the server (in other words each time a sensor is connected to the server).

