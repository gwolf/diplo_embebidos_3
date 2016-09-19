#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int serial_open( char *serial_name, speed_t baud )
{
	struct termios newtermios;
  	int fd;

  	// Open the serial port
	if((fd=open(serial_name,O_RDWR | O_NOCTTY | O_NDELAY))==-1)
	{
		perror("Error, no se pudo abrir la interfaz serie \n");
		exit(EXIT_FAILURE);
	}

	// Configure the serial port attributes: 
  	//   -- No parity
  	//   -- 8 data bits
  	//   -- other things...
  	newtermios.c_cflag= CBAUD | CS8 | CLOCAL | CREAD;
  	newtermios.c_iflag=IGNPAR;
  	newtermios.c_oflag=0;
  	newtermios.c_lflag=0;
  	newtermios.c_cc[VMIN]=1;
  	newtermios.c_cc[VTIME]=0;

  	// Set the speed
  	cfsetospeed(&newtermios,baud);
  	cfsetispeed(&newtermios,baud);
  
  	// flush the input buffer
  	if (tcflush(fd,TCIFLUSH)==-1) 
    	return -1;
  
  	// flush the output buffer
  	if (tcflush(fd,TCOFLUSH)==-1) 
    	return -1;

  	//-- Configure the serial port now!!
  	if (tcsetattr(fd,TCSANOW,&newtermios)==-1)
    	return -1; 

  	//-- Return the file descriptor
  	return fd;
}


