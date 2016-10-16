#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "monyt_socket.h"
#include "monyt_manage_threads.h"

typedef struct __parameters_thread_main {
	uint thread_id;
	int socket_;
	char msn[32];
}thread_parameters;

void *_checkSensor(void *param);


int main(int argc, char **argv)
{
	int socket_, s_accepted, _thread_aux;
	struct sockaddr_un remote;
	pthread_t _threads[LIMIT_CONNECTIONS];
	thread_parameters param_thread[LIMIT_CONNECTIONS];
	uint n_thread;


	if(!(socket_ = server_init())) {
		printf("Error, Cannot initialize socket\n");
		return EXIT_FAILURE;
	}

	if(!init_thread_counter()) {
		printf("Error, Cannot initialize thread counter\n");
		return EXIT_FAILURE;
	}


	while(1) {
		printf("Waiting connections...\n");
		if((s_accepted = server_accept(socket_, &remote))==0) {
			printf("Error, accept function");
			continue;
		}

		if(!getAvailable_thread(&n_thread)) {
			close(s_accepted);
			printf("Error, there is not any thread available\n");
			continue;
		}
		setValue_thread(n_thread, 1);

		param_thread[n_thread].socket_ = s_accepted;
		param_thread[n_thread].thread_id = n_thread;
		sprintf(param_thread[n_thread].msn, "Thread: %d\0", n_thread);

		_thread_aux = pthread_create(&_threads[n_thread], NULL, _checkSensor, (void *)&param_thread[n_thread]);
		if(_thread_aux) {
			printf("Error, pthread_create function\n");
			continue;
		}
	}

	n_thread = LIMIT_CONNECTIONS;
	while(n_thread--) {
		pthread_join(_threads[n_thread], NULL);
	}

	return EXIT_SUCCESS;
}


void *_checkSensor(void *param) {

	thread_parameters *param_thread = (thread_parameters *)param;

	printf("En el thread -- %s\n", (char *)param_thread->msn);

	int aux;
	char buffer[64];
	char limit_ = 10;

	while(1) {
		aux = recv(param_thread->socket_, buffer, sizeof(buffer), 0);
		if(aux==-1) {
			sleep(1);
			continue;
		}

		else if(aux==0) {
			if(limit_--)
				continue;
			break;
		}
		buffer[aux] = 0x00;
		printf("[+] (%d) - %s\n", param_thread->thread_id, buffer);
	}


	printf(" -- Thread terminado -- %s\n", (char *)param_thread->msn);
	setValue_thread(param_thread->thread_id, 0);
}
