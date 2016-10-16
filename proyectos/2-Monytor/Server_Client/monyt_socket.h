#ifndef _MONYT_SOCKET_
#define _MONYT_SOCKET_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <unistd.h>

/** Number of connections supported by the server. */
#define LIMIT_CONNECTIONS 10
/** Path where the unix socket lives */
#define SOCKET_PATH "/tmp/monyt_socket"

/**
 * @brief Initialize the socket in server mode
 * @param struct sockaddr_un pointer
 * @return socket descriptor if success, 0 otherwise
 */
int server_init();


/**
 * @brief Funtion to wait for connections
 * @param socket descriptor
 * @param struct sockaddr_un to return the client address
 * @return socket of the new connection, 0 otherwise
 */
int server_accept(int i_socket, struct sockaddr_un *i_remote);


/**
 * @brief Initiaize the socket in client mode
 * @return socket if success, 0 otherwise
 */
int client_init();


/**
 * @brief Connect to the server
 * @param socket descriptor
 * @return 1 if success, 0 otherwise
 */
char client_connect(int i_socket);

#endif /* _MONYT_SOCKET_ */
