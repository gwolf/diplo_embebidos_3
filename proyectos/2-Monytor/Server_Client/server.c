#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "monyt_socket.h"
#include "monyt_manage_threads.h"

typedef struct __parameters_thread_main {
	uint thread_id;
	int socket;
	char header[16];
	char msg[32];
}thread_parameters;

void *notifierServer(void *param);
void poll_notifier(int socket, thread_parameters *param_thread);
void *checkSensor(void *param);
void poll_sensor(void *param);


int main(int argc, char **argv)
{
	int socket, s_accepted, r_thread;
	struct sockaddr_un remote;
	pthread_t notifier_thread, threads_ids[LIMIT_CONNECTIONS];
	thread_parameters param_thread[LIMIT_CONNECTIONS];
	uint n_thread;

	/* Initialize thread counter */
	if(!init_thread_counter()) {
		printf("Error, Cannot initialize thread counter\n");
		return EXIT_FAILURE;
	}

	/* Create thread for notifier modules */
	r_thread = pthread_create(&notifier_thread, NULL, notifierServer, (void *)param_thread);
	if(r_thread) {
		printf("Error, pthread_create function\n");
		return EXIT_FAILURE;
	}

	/** HERE initialize sensor server mode */
	if(!(socket = sensor_server_init())) {
		printf("Error, Cannot initialize sensor socket\n");
		return EXIT_FAILURE;
	}

	memset(param_thread, 0, sizeof(thread_parameters)*LIMIT_CONNECTIONS);

	for(;;) {
		printf("[+] Sender Waiting connections...\n");
		if((s_accepted = server_accept(socket, &remote))==0) {
			printf("Error, accept function");
			continue;
		}

		if(!getAvailable_thread(&n_thread)) {
			close(s_accepted);
			printf("Error, there is not any thread available\n");
			continue;
		}
		setValue_thread(n_thread, 1);

		param_thread[n_thread].socket = s_accepted;
		param_thread[n_thread].thread_id = n_thread;
		sprintf(param_thread[n_thread].msg, "Thread: %d\0", n_thread);

		r_thread = pthread_create(&threads_ids[n_thread], NULL, checkSensor, (void *)&param_thread[n_thread]);
		if(r_thread) {
			printf("Error, pthread_create function\n");
			continue;
		}
	}

	n_thread = LIMIT_CONNECTIONS;
	while(n_thread--) {
		pthread_join(threads_ids[n_thread], NULL);
	}

	return EXIT_SUCCESS;
}


void *notifierServer(void *param) {
	thread_parameters *param_thread = (thread_parameters *)param;
	int socket, s_accepted;
	struct sockaddr_un remote;

	/** HERE initialize notifier server mode */
	if(!(socket = notifier_server_init())) {
		printf("Error, Cannot initialize notifier socket\n");
		return NULL;
	}

	for(;;) {
		printf("[+] Notifier -- Waiting connections...\n");
		if((s_accepted = server_accept(socket, &remote))==0) {
			printf("Error, accept function");
			continue;
		}

		poll_notifier(s_accepted, param_thread);

	}
}

void poll_notifier(int socket, thread_parameters *param_thread) {

	int sent_b, i;
	char buffer[64];
	char limit = 10, value = 0;

	for(;;) {

		for (i = 0; i < LIMIT_CONNECTIONS; i++) {

			getValue_thread(param_thread[i].thread_id, &value);

			if(!value)
				continue;

			sent_b = send(socket, param_thread[i].msg, strlen(param_thread[i].msg), MSG_NOSIGNAL);
			if(sent_b == -1 || !sent_b) {
				if(limit--)
					continue;
				break;
			}
			else {
				limit = 10;
			}

		}
	}
}

void *checkSensor(void *param) {

	thread_parameters *param_thread = (thread_parameters *)param;

	printf("En el thread -- %s\n", (char *)param_thread->msg);

	int read_b;
	char buffer[64];
	char limit = 10;

	while(limit) {
		read_b = recv(param_thread->socket, buffer, sizeof(buffer), 0);

		switch(read_b) {
			case -1:
				sleep(1);
				continue;
			case 0:
				if(limit--)
					continue;
				break;
			default:
				buffer[read_b] = 0x00;

				if(read_b < 3) {
					printf("First values must be grather than 3 (length)");
				}
				else if(!memcmp(buffer, "##", 2)) {
					/* validate input 16 bytes max */
					printf("(%d) [+] Header - %s ++ %d\n", param_thread->thread_id, buffer, read_b);
					memcpy(param_thread->header, buffer, read_b + 1);
					poll_sensor(param);
				}
				limit = 0;
		}
	}


	printf(" -- Thread terminado -- %s\n", (char *)param_thread->msg);
	setValue_thread(param_thread->thread_id, 0);
	close(param_thread->socket);
}


void poll_sensor(void *param) {

	thread_parameters *param_thread = (thread_parameters *)param;

	int read_b;
	char buffer[64];
	char limit = 10;

	for(;;) {
		read_b = recv(param_thread->socket, buffer, sizeof(buffer), 0);

		if(read_b == -1) {
			sleep(1);
			continue;
		}
		else if(read_b == 0) {
			if(limit--)
				continue;
			break;
		}

		buffer[read_b] = 0x00;
		memcpy(param_thread->msg, buffer, read_b + 1);
		printf("(%d) [+] %s - %s\n", param_thread->thread_id, param_thread->header, buffer);
	}
}
