#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <pthread.h>

void forkHiloServidor	( int *, pthread_t * );
void waitHiloServidor	( pthread_t );
void *hiloServidor		( void * );
int iniServidor			( void );

#endif
