#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termio.h>
#include <fcntl.h>
#include <errno.h>

void getLocation(int uart);
void configureUART(int *uart);


int main(int argc, char **argv)
{
	int uart; /* UART file descriptor */
	char *tty; /* tty to open */

	if(argc < 2) {
		printf("Usage: %s /dev/tty*\n", argv[0]);
		return EXIT_FAILURE;
	}
	tty = argv[1];

	printf("Opening: %s\n", tty);
	uart = open(tty, O_RDWR | O_NOCTTY | O_NDELAY);
	
	if(uart==-1) {
		perror("Error: Can't open uart\n");
		return EXIT_FAILURE;
	}

	/* configure UART */
	configureUART(&uart);
	
	/* not wait for response */
	fcntl(uart, F_SETFL, FNDELAY);

	/* loop to get the location */
	printf("Get location\n");
	getLocation(uart);
	
	return EXIT_SUCCESS;
}

/** Uart configuration */
void configureUART(int *uart)
{
	struct termios options;

	tcgetattr(*uart, &options);
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	options.c_cflag &= ~CSIZE; /* Mask the character size bits */
	options.c_cflag |= CS8;    /* Select 8 data bits */

	tcsetattr(*uart, TCSANOW, &options);
}

/** Function to get the latitude and longitude */
void getLocation(int uart)
{
	int rBytes;
	char buffer[256];
	char latitude[32];
	char longitude[32];

	sprintf(latitude, "INVALID");
	sprintf(longitude, "INVALID");
	latitude[7] = 0;
	longitude[7] = 0;

	/* read data from the GPS */
	while(1) {
		rBytes = read(uart, buffer, sizeof(buffer));
		if(rBytes!=-1 && rBytes>4)
		{
			/* filter the information recieved, we only need the GPGLL package */
			char *found = strstr(buffer, "GPGLL");
			if(found) 
			{
				int valid = strstr(buffer, "*") - buffer;

				/* Verify if the information is correct */
				if(buffer[valid-3] == 'A') {
					char *pAux;
					int posI = 1, posF = 1;
					
					/* read latitude */
					pAux = strstr(buffer, ",");
					posI = pAux - buffer + 1;
					pAux = strstr(pAux+1, ",");
					posF = pAux - buffer;

					strncpy(latitude, buffer+posI, posF - posI);
					latitude[posF-posI] = 0;

					/* read latitude */
					pAux = strstr(&buffer[posF+2], ",");
					posI = pAux - buffer + 1;
					pAux = strstr(pAux+1, ",");
					posF = pAux - buffer;

					strncpy(longitude, buffer+posI, posF - posI);
					longitude[posF-posI] = 0;
					printf("[+] lat: %s, lon: %s\n", latitude, longitude);
					sleep(1);

				}
			}
		}
		else {
			printf("[-] lat: %s, lon: %s\n", latitude, longitude);
			sleep(1);
		}
	}
}

