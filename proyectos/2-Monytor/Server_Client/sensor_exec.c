#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>


#include "monyt_socket.h"

#define TEMPERATURE_FLAG "##TEMP-\0"
#define N_ATTEMPTS 10
#define MSG_LEN 64

int notifyModule(int socket_, char *module);


int main(int argc, char **argv) {
	pid_t p_sensor;
	int pipe_fd[2];

	/** validate the input */
	if(argc < 2) {
		printf("Usage: %s sensor_program\n", argv[0]);
		return EXIT_FAILURE;
	}

	/** create a pipe to manage the standar output of the sensor */
	if(pipe(pipe_fd) == -1) {
		perror("Error, pipe");
		return EXIT_FAILURE;
	}

	/** create a new process that will execute the sensor executable */
	if((p_sensor = fork()) == -1) {
		/** close the pipe descriptors */
		close(pipe_fd[0]);
		close(pipe_fd[1]);

		perror("Error, fork call ");
		return -1;
	}

	/** If the process if is not the sensor (father) */
	if(p_sensor) {
		int socket;
		int read_b, sent_b;
		char msg[MSG_LEN];
		char n_limit = N_ATTEMPTS;

		/* close the output descriptor of the pipe */
		close(pipe_fd[1]);
		printf("Father -> My pid %d, My son pid: %d\n", getpid(), p_sensor);

		/* change the standar input, now is the pipe descriptor */
		dup2(pipe_fd[0], 0);

		/* wait until the socket is created */
		if(!(socket = client_init())) {
			printf("Error, Cannot connect to the server\n");
			return EXIT_FAILURE;
		}

		/* wait until connect to the server */
		printf("[+] Waiting until connect to the server\n");
		while(n_limit--) {
			if(client_connect(socket))
				break;
			sleep(1);
		}

		/* if the limit is reached we exit with error status */
		if (n_limit < 0) {
			/*********** NOTE MANAGE THE ERROR, CLOSE THE DESCRIPTOR WAIT FOR THE SON AND THAT STUFF */
			printf("Error, Cannot connect to the server\n");
			return EXIT_FAILURE;
		}

		printf("[+] Connection successful\n");
		while(1) {
			if(notifyModule(socket, TEMPERATURE_FLAG))
				break;
			sleep(1);
		}

		/** wait until the son process has finished */
		for(;;) {
			pid_t pid = waitpid(p_sensor, NULL, WNOHANG);

			switch(pid) {
				case -1:
					printf("Error, waitpid has failed\n");
					break;
				case 0:
					read_b = read(0, msg, MSG_LEN);
					sent_b = send(socket, msg, read_b, MSG_NOSIGNAL);

					break;
				default:
					close(socket);
					return EXIT_SUCCESS;
			}
		}
	}
	else { /** Here the sensor program is executed */
		char *v[] = {argv[1], (char *)0};

		/* close the input descriptor of the pipe */
		close(pipe_fd[0]);

		/* change the standar output, now is the pipe descriptor */
		dup2(pipe_fd[1], 1);

		printf("Son -> My pid: %d\n", getpid());

		if(execvp(argv[1], v)) {
			perror("Error, execl call ");
			return -1;
		}

		close(pipe_fd[0]);
	}

	return EXIT_SUCCESS;
}

int notifyModule(int socket_, char *module) {
	int aux;

	aux = send(socket_, module, strlen(module), MSG_NOSIGNAL);
	if(!aux || aux==-1)
		return 0;
	return aux;
}
