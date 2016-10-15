#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define LIMIT_CONNECTIONS 10
#define SOCKET_PATH "/tmp/project_socket"

typedef struct __parameters_thread_main {
	char *thread_id;
	int socket_;
	char msn[32];
}thread_parameters;

char server_init(int *socket_, struct sockaddr_un *local);
int server_accept(int socket_, struct sockaddr_un *remote);

char getValue_thread(char *thread);
void setValue_thread(char *thread, char value);
char getAvailable_thread(char *threads);

void *_checkSensor(void *param);


int main(int argc, char **argv)
{
	int socket_, s_accepted, _thread_aux;
	struct sockaddr_un local, remote;
	int len_r;
	char cont_threads[LIMIT_CONNECTIONS];
	pthread_t _threads[LIMIT_CONNECTIONS];
	thread_parameters param_thread[LIMIT_CONNECTIONS];
	char aux_threads;


	if(!server_init(&socket_, &local)) {
		printf("Error, Cannot initialize socket\n");
		return EXIT_FAILURE;
	}

	/* clean threads counter */
	memset(cont_threads, 0, sizeof(char)*LIMIT_CONNECTIONS);

	while(1) {
		printf("Waiting connections...\n");
		if((s_accepted = server_accept(socket_, &remote))==0) {
			printf("Error, accept function");
		}
		
		aux_threads = getAvailable_thread(cont_threads);
		if(aux_threads == -1) {
			close(s_accepted);
			printf("Error, there is not any thread available\n");
			continue;
		}
		setValue_thread(&cont_threads[aux_threads], 1);

		param_thread[aux_threads].socket_ = s_accepted;
		param_thread[aux_threads].thread_id = &cont_threads[aux_threads];
		sprintf(param_thread[aux_threads].msn, "Thread: %d\0", aux_threads);

		_thread_aux = pthread_create(&_threads[aux_threads], NULL, _checkSensor, (void *)&param_thread[aux_threads]);
		if(_thread_aux) {
			printf("Error, pthread_create function\n");
			continue;
		}
	}

	aux_threads = LIMIT_CONNECTIONS;
	while(aux_threads--) {
		pthread_join(_threads[aux_threads], NULL);
	}

	return EXIT_SUCCESS;
}


/** Initialize socket for server mode */
/* return 1 if success, otherwise 0 */
char server_init(int *socket_, struct sockaddr_un *local)
{
	/* create nonblocking socket */
	if((*socket_ = socket(AF_UNIX, SOCK_STREAM, 0))==-1)
		return 0;

	local->sun_family = AF_UNIX;
	strcpy(local->sun_path, SOCKET_PATH);
	unlink(local->sun_path);

	if(bind(*socket_, (struct sockaddr *)local, strlen(local->sun_path) + sizeof(local->sun_family)))
		return 0;

	if(listen(*socket_, LIMIT_CONNECTIONS) == -1)
		return 0;
	return 1;
}


/** Accept connection */
/* return the file descriptor of the socket if success, otherwise 0 */
int server_accept(int socket_, struct sockaddr_un *remote)
{
	int len_r = sizeof(remote);
	int s_accepted;

	if((s_accepted = accept(socket_, (struct sockaddr *)remote, &len_r))==-1)
		return 0;
	return s_accepted;
}


/* functions for managing the threads */
char getValue_thread(char *thread) {
	return *thread;
}

void setValue_thread(char *thread, char value) {
	*thread = (value) ? 1: 0;
}

char getAvailable_thread(char *threads) {
	int i = LIMIT_CONNECTIONS;
	while(i--) {
		if(getValue_thread(&threads[i]))
			continue;
		return i;
	}
	return -1;
}


void *_checkSensor(void *param) {
	char buffer[64];
	int aux;
	char *found;
	char limit_ = 10;

	thread_parameters *param_thread = (thread_parameters *)param;

	printf("En el thread -- %s\n", (char *)param_thread->msn);

	sleep(2);

	printf(" -- Thread terminado -- %s\n", (char *)param_thread->msn);
	setValue_thread(param_thread->thread_id, 0);
}
