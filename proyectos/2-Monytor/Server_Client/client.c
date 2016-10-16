#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "monyt_socket.h"

#define TEMPERATURE_FLAG "##TEMP-\0"

int notifyModule(int socket_, char *module);


int main(int argc, char **argv)
{
	int socket_;

	/* wait until connect to the server */
	printf("[+] Waiting until connect to the server\n");
	while(1)
		if((socket_ = client_init()))
			break;
	printf("[+] Waiting...\n");
	while(1) {
		if(client_connect(socket_))
			break;
		sleep(1);
	}
	printf("[+] Connection successful\n");
	

	while(1) {
		if(notifyModule(socket_, TEMPERATURE_FLAG))
			break;
		sleep(1);
	}

	sleep(1);

	close(socket_);
	return EXIT_SUCCESS;
}

int notifyModule(int socket_, char *module) {
	int aux;

	aux = send(socket_, module, strlen(module), MSG_NOSIGNAL);
	if(!aux || aux==-1)
		return 0;
	return aux;
}
