
GCC = gcc
CFLAGS = -Wall -lpthread
OBJ_SERVER = monyt_socket.o monyt_manage_threads.o server.o
OBJ_SENSOR = monyt_socket.o sensor_exec.o
OBJ_NOTIFIER = monyt_socket.o notifier_exec.o
SERVER = server
SENSOR = sensor
NOTIFIER = notifier

all: bin

%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

$(SERVER): $(OBJ_SERVER)
	$(GCC) $(CFLAGS) $(OBJ_SERVER) -o $(SERVER)

$(SENSOR): $(OBJ_SENSOR)
	$(GCC) $(CFLAGS) $(OBJ_SENSOR) -o $(SENSOR)

$(NOTIFIER): $(OBJ_NOTIFIER)
	$(GCC) $(CFLAGS) $(OBJ_NOTIFIER) -o $(NOTIFIER)

bin: $(SERVER) $(SENSOR) $(NOTIFIER)

clear:
	rm -f $(OBJ_SERVER) $(OBJ_SENSOR) $(OBJ_NOTIFIER)

clean:
	rm -f $(OBJ_SERVER) $(OBJ_SENSOR) $(OBJ_NOTIFIER) $(SERVER) $(SENSOR) $(NOTIFIER)

run_server: $(SERVER)
	./$(SERVER)

test_sensor: $(SENSOR)
	./$(SENSOR) '##ANALOG-' ./test.sh

test_notifier: $(NOTIFIER)
	./$(NOTIFIER) ./test_notifier.sh
