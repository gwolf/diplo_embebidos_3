#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>


#include "monyt_socket.h"

#define N_ATTEMPTS 10
#define MSG_LEN 64

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

		/* close the input descriptor of the pipe */
		close(pipe_fd[0]);
		printf("Father -> My pid %d, My son pid: %d\n", getpid(), p_sensor);

		/* change the standar output, now is the pipe descriptor */
		dup2(pipe_fd[1], 1);

		/* wait until the socket is created */
		if(!(socket = client_init())) {
			printf("Error, Cannot connect to the server\n");
			return EXIT_FAILURE;
		}

		/* wait until connect to the server */
		printf("[+] Waiting until connect to the server\n");
		while(n_limit--) {
			if(notifier_server_connect(socket))
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

		/** wait until the son process has finished */
		n_limit = N_ATTEMPTS;
		for(;;) {
			pid_t pid = waitpid(p_sensor, NULL, WNOHANG);

			switch(pid) {
				case -1:
					printf("Error, waitpid has failed\n");
					break;
				case 0:
					read_b = recv(socket, msg, MSG_LEN, 0);
					
					if(read_b == -1) {
						sleep(1);
						continue;
					}
					else if (read_b == 0) {
						if(n_limit--)
							continue;
						close(socket);
						return EXIT_FAILURE;
					}

					sent_b = write(1, msg, read_b);

					break;
				default:
					close(socket);
					return EXIT_SUCCESS;
			}
		}
	}
	else { /** Here the sensor program is executed */
		char *v[] = {argv[1], (char *)0};

		/* close the output descriptor of the pipe */
		close(pipe_fd[1]);

		/* change the standar input, now is the pipe descriptor */
		dup2(pipe_fd[0], 0);

		printf("Son -> My pid: %d\n", getpid());

		if(execvp(argv[1], v)) {
			perror("Error, execl call ");
			return -1;
		}

		close(pipe_fd[0]);
	}

	return EXIT_SUCCESS;
}

