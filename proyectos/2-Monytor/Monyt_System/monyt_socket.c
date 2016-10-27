

#include "monyt_socket.h"

/** Initialize the socket in server mode */
static int server_init(char *socket_path)
{
	int l_socket;
	struct sockaddr_un l_addr;

	/* create nonblocking socket */
	if((l_socket = socket(AF_UNIX, SOCK_STREAM, 0))==-1)
		return 0;

	/* fill address structure */
	l_addr.sun_family = AF_UNIX;
	strcpy(l_addr.sun_path, socket_path);
	unlink(l_addr.sun_path);

	/* bind and write listen limit */
	if(bind(l_socket, (struct sockaddr *)&l_addr, strlen(l_addr.sun_path) + sizeof(l_addr.sun_family)))
		return 0;

	if(listen(l_socket, LIMIT_CONNECTIONS) == -1)
		return 0;
	return l_socket;
}

/** Initialize the socket in server mode */
int sensor_server_init()
{
	return server_init(SENSOR_PATH);
}

/** Initialize the socket in server mode */
int notifier_server_init()
{
	return server_init(NOTIFIER_PATH);
}


/** Funtion to wait for connections */
int server_accept(int i_socket, struct sockaddr_un *i_remote)
{
	int len_r = sizeof(i_remote);
	int l_socket;

	if((l_socket = accept(i_socket, (struct sockaddr *)i_remote, &len_r))==-1)
		return 0;
	return l_socket;
}



/** Initiaize the socket in client mode */
int client_init()
{
	int l_socket;

	/* Create a socket in the UNIX domain */
	if((l_socket = socket(AF_UNIX, SOCK_STREAM, 0))==-1)
		return 0;

	return l_socket;
}

/** Connect to the server */
char sensor_server_connect(int i_socket)
{
	struct sockaddr_un l_addr;

	/* Fill the address structure */
	l_addr.sun_family = AF_UNIX;
	strcpy(l_addr.sun_path, SENSOR_PATH);

	if(connect(i_socket, (struct sockaddr *)&l_addr, strlen(l_addr.sun_path) + sizeof(l_addr.sun_family)))
		return 0;
	return 1;
}

/** Connect to the server */
char notifier_server_connect(int i_socket)
{
	struct sockaddr_un l_addr;

	/* Fill the address structure */
	l_addr.sun_family = AF_UNIX;
	strcpy(l_addr.sun_path, NOTIFIER_PATH);

	if(connect(i_socket, (struct sockaddr *)&l_addr, strlen(l_addr.sun_path) + sizeof(l_addr.sun_family)))
		return 0;
	return 1;
}

