#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termio.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>

#include <pthread.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define LIMIT_WAITFOREVER 40
#define MESSAGE_STORAGE 10

char waitForever = 0; /* Flag -> wait until reach response */
char _error = 0;
struct termios options;
char gsm_setup_fail = 0;
char msnUNREAD[MESSAGE_STORAGE];
int msnCont = 0;

/* Modem messages */
enum _Response {GSM_OK = 1, GSM_AT, GSM_READY, GSM_ATE0, GSM_MSG, GSM_MGL, GSM_CREG, GSM_MGR, MSG_AVAILABLE, GSM_ERROR_AT, GSM_ERROR_ECHO, GSM_ERROR_SIM};

/* AT COMMANDS */
const char atc0[] = "AT\r\0";		/* Every AT command starts with "AT" */
const char atc1[] = "ATE0\r\0";		/* Disable echo */
const char atc2[] = "AT+CREG?\r\0";	/* Verify network state */
const char atc3[] = "AT+CMGF=1\r\0";	/* Set text mode messages */
const char atc4[] = "AT#SLED=2\r\0";	/* Enable status led */
const char atc5[] = "AT+CPIN?\r\0";	/* Verify PIN status */
const char atc6[] = "AT+CSMP=17,168,0,240\r\0";	/* SMS parameters */
const char atc7[] = "AT+CNMI=1,1,0,0,0\r\0";	/* Especify message event */

const char atc15[] = "AT+CMGS=\0";		/* Sends SMS to desired number */

const char atc20[] = "AT+CMGL=\"ALL\"\r\0";	/* Check status of ALL received SMS */
const char atc21[] = "AT+CMGL=\"REC UNREAD\"\r\0";	/* Check status of UNREAD recieved SMS */
const char atc22[] = "AT+CMGL=\"REC READ\"\r\0";	/* Check status of READ recieved SMS */
const char atc24[] = "AT+CMGR=\0"; /* read message */


void configureUART(int *uart);
void openUART(int *uart, char *tty);

char waitResponse(int *uart, char response);
char writeUART(int *uart, char *bytes);

char sendCommand(int *uart, char *command, char wait);
char sendMSG(int *uart, char *number, char *msg);

char send_InitCommands(int uart);
char modemRegistered(int uart);
char enableTextMode(int uart);


int main(int argc, char **argv)
{
	char *tty;
	int uart;
	char buffer[64], msg[256];
	int limit_ = 10;
	int numInputs;


	/* validate arguments */
	if(argc!=3)
	{
		syslog(LOG_INFO, "Usage: %s /dev/tty* numInputs\n", argv[0]);
		return EXIT_FAILURE;
	}
	tty = argv[1];
	numInputs = atoi(argv[2]);

	/** Open logger */
	openlog("GSM_logger", LOG_PID|LOG_CONS, LOG_USER);

	/**** Open and configure uart ****/
	syslog(LOG_INFO, "[+] Opening: %s\n\n", tty);
	openUART(&uart, tty);

	sleep(5);


	limit_ = 20;

	/* Initialize GSM modem */
	switch(send_InitCommands(uart))
	{
		case GSM_ERROR_AT:
			syslog(LOG_INFO, "Error, GSM does not respond\n");
			return EXIT_FAILURE;
			break;
		case GSM_ERROR_SIM:
			syslog(LOG_INFO, "Error, SIM is not ready\n");
			return EXIT_FAILURE;
			break;
		case GSM_ERROR_ECHO:
			syslog(LOG_INFO, "Error, Echo command failed\n");
			return EXIT_FAILURE;
	}
	
	/* Verify if modem is registered on the GSM network */
	while(!modemRegistered(uart)) {
		sleep(3);
		if(limit_--)
			continue;
		return EXIT_FAILURE;
	}
	
	/* Enable text mode */
	limit_ = 10;
	while(!enableTextMode(uart)) {
		sleep(1);
		if(limit_--)
			continue;
		return EXIT_FAILURE;
	}

	limit_ = 60;
	for(;;) {
		int i, read_b, idx;
		for(i=0, read_b = 0, idx = 0; i<numInputs; i++) {
			// read from stdin, and store it on msg buffer
			read_b += scanf("%s", buffer);
			memcpy(msg + idx, buffer, read_b);

			// update index
			idx += read_b;
			msg[idx] = ",";
			idx += 1;
		}
		msg[idx] = 0;

		if (limit_--)
			continue;

		limit_ = 60;
		syslog(LOG_INFO, "[*] Data to send by MSN: %s\n", msg);

		sendMSG(&uart, "+525548548089\0", msg);

	}
	

	close(uart);
	return EXIT_SUCCESS;
}

/**
 * @brief Set the uart configuration
 * @param the uart pointer
 * @return Nothing
 */
void configureUART(int *uart)
{
	tcgetattr(*uart, &options);
	cfsetispeed(&options, B19200); /* Set input and output Baudrate 19200 */
	cfsetospeed(&options, B19200);
	options.c_cflag &= ~CSIZE; /*  Mask the character size bits */
	options.c_cflag |= CS8;    /* Select 8 data bits */

	tcsetattr(*uart, TCSANOW, &options);
}

/**
 * @brief Open the UART device
 * @param the uart pointer, where the fd will be store
 * @param the device that will be open
 * @return Nothing
 */
void openUART(int *uart, char *tty) 
{
	*uart = open(tty, O_RDWR | O_NOCTTY | O_NDELAY);
	if(*uart==-1) {
		syslog(LOG_INFO, "Error: cant open uart\n");
		exit(EXIT_FAILURE);
	}
	configureUART(uart);

	/* set the uart nonblocking */
	fcntl(*uart, F_SETFL, FNDELAY);
}


/**
 * @brief Generic function to wait a GSM command respond
 * @param the uart pointer
 * @param the response we are waiting
 * @return Nothing
 */
char waitResponse(int *uart, char response)
{
        char buffer[256];
        char auxBuf[16]; 
	int aux, i;
	char *found = NULL;
	int limit_ = 10;

        aux = read(*uart, buffer, sizeof(buffer));
        if(aux!=-1 && aux>1)
        {
                syslog(LOG_INFO, "  --- Recieved: %d: ", aux);
                for(i=0; i<aux; i++)
                        if(buffer[i]>31 && buffer[i]<127)
                                syslog(LOG_INFO, "%c", buffer[i]);
                syslog(LOG_INFO, "\n");

		found = strstr(buffer, "ERROR\0");
		if(found) {
			_error = 1;
			return 1;
		}

		
		/* Verify response */
		switch(response)
		{
			case GSM_OK:
				strcpy(auxBuf, "OK\0");
				found = strstr(buffer, auxBuf);
				if(found)
					return 1;
			break;
			case GSM_READY:
				strcpy(auxBuf, "READY\0");
				found = strstr(buffer, auxBuf);
				if(found) {
					while(!waitResponse(uart, GSM_OK)) {
						if(limit_--)
							continue;
						return 0;
					}
					return 1;
				}
			break;
			case GSM_AT:
				strcpy(auxBuf, "AT\0");
				found = strstr(buffer, auxBuf);
				if(found) {
					while(!waitResponse(uart, GSM_OK)) {
						if(limit_--)
							continue;
						return 0;
					}
					return 1;
				}
			break;
			case GSM_ATE0:
				strcpy(auxBuf, "ATE0\0");
				found = strstr(buffer, auxBuf);
				if(!found)
					return 0;
				while(!waitResponse(uart, GSM_OK)) {
					if(limit_--)
						continue;
					return 0;
				}
				return 1;
			break;
			case GSM_CREG:
				/* wait "+CREG: 0,1" */
				strcpy(auxBuf, "+CREG\0");
				found = strstr(buffer, auxBuf);
				if(found==NULL)
					return 0;
				found = strstr(buffer, "0,1\0");
				if(found) {
					while(!waitResponse(uart, GSM_OK)) {
						if(limit_--)
							continue;
						return 0;
					}
					return 1;
				}
				while(!waitResponse(uart, GSM_OK)) {
					if(limit_--)
						continue;
					break;
				}
				return 0;
			break;
			case GSM_MSG:
				strcpy(auxBuf, "+CMGS\0");
				found = strstr(buffer, auxBuf);
				if(found) {
					while(!waitResponse(uart, GSM_OK)) {
						if(limit_--)
							continue;
						return 0;
					}
					return 1;
				}
			break;
			case GSM_MGL:
				strcpy(auxBuf, "+CMGL\0");
				found = strstr(buffer, auxBuf);
				if(found) {
					found = strstr(buffer, ":\0");
					int aux = found - buffer + 2;
					
					found = strstr(buffer, ",\0");
					buffer[found-buffer]='\0';
					msnUNREAD[msnCont++] = atoi(buffer + aux);
					while(!waitResponse(uart, GSM_MGL)) {
						if(limit_--)
							continue;
						return 0;
					}
					return 1;
				}
				strcpy(auxBuf, "OK\0");
				found = strstr(buffer, auxBuf);
				if(found)
					return 1;
			break;
		}
	}
        return 0;
}

/**
 * @brief Write on the uart
 * @param the uart pointer
 * @param the data that will be written
 * @return 1 if success, 0 otherwise
 */
char writeUART(int *uart, char *bytes)
{
	int aux;
	syslog(LOG_INFO, "[+] Send -> size:%d, command: %s\n", strlen(bytes), bytes);
	aux = write(*uart, bytes, strlen(bytes));
	if(!aux || aux==-1) {
		syslog(LOG_INFO, "Error: can't send command:\"%s\"\n", bytes);
		return 0;
	}
	return 1;
}

/**
 * @brief Send a GSM command
 * @param the uart pointer
 * @param the command that will be sent
 * @param the time to wait for the response
 * @return 1 if success, 0 otherwise
 */
char sendCommand(int *uart, char *command, char wait)
{
	int aux, i;
	syslog(LOG_INFO, "[+] Send -> size:%d, command: %s\n", strlen(command), command);
	
	/* Send the command */
	aux = write(*uart, command, strlen(command));
	
	if(!aux || aux==-1) {
		syslog(LOG_INFO, "[-] ERROR: can't send command:\"%s\"\n", command);
		return 0;
	}	
	usleep(200000);

	if(wait == GSM_MSG)
		sleep(5);
	if(wait)
	{
		syslog(LOG_INFO, "--- Waiting response\n");
		i = 0;
		while(i<10 || (waitForever && i<LIMIT_WAITFOREVER)) {
			if(waitResponse(uart, wait))
				return 1;
			usleep(30000);
			i++;
		}
	}
	else
		return 1;
	return 0;
}

/**
 * @brief Send a GSM message
 * @param the uart pointer
 * @param the number where the msg will be sent
 * @param the message
 * @return 1 if success, 0 otherwise
 */
char sendMSG(int *uart, char *number, char *msg)
{
	char buf[256];
	char limit_ = 10;

	/* Verify connectivity */
	while(!modemRegistered(*uart)) {
		usleep(20000);
		if(limit_--)
			continue;
		return 0;
	}

	limit_ = 10;
	/* Set text mode */ 
	while(!enableTextMode(*uart)) {
		usleep(20000);
		if(limit_--)
			continue;
		return 0;
	}

	/**** Send Message */
	/* Attach phone number */
	strcpy(buf, atc15);
	strcat(buf, "\"");
	strcat(buf, number);
	strcat(buf, "\"\r");
	strcat(buf, "********************"); /* Add padding for sending errors */
	strcat(buf, msg);	/* Add message */
	strcat(buf, "\x1A\0");
	
	/* wait until get response */
	waitForever = 1;
	limit_ = 4;
	while(!sendCommand(uart, buf, GSM_MSG)) {
		sleep(2);
		if(limit_--)
			continue;
		return 0;
	}
	waitForever = 0;

	/* verify Error flag */
	if(_error) {
		syslog(LOG_INFO, "[-] ERROR: Can not send message\n");
		_error = 0;
		return 0;
	}
	return 1;
}

/**
 * @brief Send Initialize commands
 * @param the uart descriptor
 * @return 1 if success, 0 otherwise
 */
char send_InitCommands(int uart)
{
	char buffer[254];
	int attempts = 10; 
	char limit_ = 10;

	/* send AT command */
	strcpy(buffer, atc0);
	while(attempts--) {
		if(sendCommand(&uart, buffer, GSM_AT))
			break;
		usleep(200000);
	}
	if(attempts <= 0)
		return GSM_ERROR_AT;
	/* Disable echo command */
	strcpy(buffer, atc1);
	while(!sendCommand(&uart, buffer, GSM_ATE0)) {
		usleep(2000000);
		if(limit_--)
			continue;
		return GSM_ERROR_ECHO;
	}
	/* Check SIM status*/
	attempts = 10;
	strcpy(buffer, atc5);
	while(attempts--) {
		if(sendCommand(&uart, buffer, GSM_READY))
			break;
		usleep(2000000);
	}
	if(attempts <= 0)
		return GSM_ERROR_SIM;
	return GSM_OK;
}

/**
 * @brief Verify if the modem is registered
 * @param the uart descriptor
 * @return 1 if success, 0 otherwise
 */
char modemRegistered(int uart)
{
	char buffer[64];

	/* Verify if modem has networked */
	strcpy(buffer, atc2);
	waitForever = 0;
	return sendCommand(&uart, buffer, GSM_CREG);
}

/**
 * @brief Enable text mode on GSM
 * @param the uart descriptor
 * @return 1 if success, 0 otherwise
 */
char enableTextMode(int uart)
{
	char buffer[64];

	/* enable text mode */
	strcpy(buffer, atc3);
	return sendCommand(&uart, buffer, GSM_OK);
}


