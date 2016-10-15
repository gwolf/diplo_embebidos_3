#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/project_socket"

#define TEMPERATURE_FLAG "##TEMP-\0"

char client_init(int *socket_, struct sockaddr_un *remote);
char client_connect(int socket_, struct sockaddr_un *remote);
int notifyModule(int socket_, char *module);


int main(int argc, char **argv)
{
	int socket_;
	struct sockaddr_un remote;
	int pin;
	int celsius, fahrenheit;
	int bytes;
	char buffer[64];
	int limit_ = 10;

	/* wait until connect to the server */
	printf("[+] Waiting until connect to the server\n");
	while(1)
		if(client_init(&socket_, &remote))
			break;
	printf("[+] Waiting...\n");
	while(1) {
		if(client_connect(socket_, &remote))
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

/** Initialize socket for client mode */
/* return 1 if success, otherwise 0 */
char client_init(int *socket_, struct sockaddr_un *remote)
{
	/* Create a socket in the UNIX domain */
	if((*socket_ = socket(AF_UNIX, SOCK_STREAM, 0))==-1)
		return 0;

	/* Fill the address data */ 
	remote->sun_family = AF_UNIX;
	strcpy(remote->sun_path, SOCKET_PATH);
	return 1;
}

/** Connect to the server */
/* return 1 if success, otherwise 0 */
char client_connect(int socket_, struct sockaddr_un *remote)
{
	if(connect(socket_, (struct sockaddr *)remote, strlen(remote->sun_path) + sizeof(remote->sun_family)))
		return 0;
	return 1;
}

int notifyModule(int socket_, char *module) {
	int aux;

	aux = send(socket_, module, strlen(module), MSG_NOSIGNAL);
	if(!aux || aux==-1)
		return 0;
	return aux;
}
