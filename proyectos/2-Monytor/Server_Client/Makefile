
GCC = gcc
CFLAGS = -lpthread
OBJ_SERVER = monyt_socket.o server.o
OBJ_CLIENT = monyt_socket.o client.o
SERVER = server
CLIENT = client

all: bin

%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

$(SERVER): $(OBJ_SERVER) 
	$(GCC) $(CFLAGS) $(OBJ_SERVER) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT) 
	$(GCC) $(CFLAGS) $(OBJ_CLIENT) -o $(CLIENT)

bin: $(SERVER) $(CLIENT)

clear:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(SERVER) $(CLIENT)

run_server: $(SERVER)
	./$(SERVER)

run_client: $(CLIENT)
	./$(CLIENT)
