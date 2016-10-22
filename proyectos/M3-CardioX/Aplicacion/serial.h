#ifndef SERIAL_H
#define SERIAL_H

#include <termios.h>
#include <pthread.h>

int  configSerial 	( char [], speed_t );
void leerDatosSerial( int [], int, int );

void forkHiloSerial	( int *, pthread_t * );
void waitHiloSerial	( pthread_t );
void *hiloSerial	( void * );

#endif
