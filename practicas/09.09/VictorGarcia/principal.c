/*
	Este programa genera dos procesos hijos:
	El proceso 1 realiza lecturas de la interfaz serie y guarda
	bloques de TAM_BLOQUE en el archivo de muestras.txt,
	posteriormente manda la señal SIGUSER1 al proceso 2 para que lea
	las muestras del archivo y las procese. El procesamiento consiste
	en promediar las muestras.
*/


#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "serial.h"

#define NUM_BLOQUES 1
#define TAM_BLOQUE  256
#define NUM_PROC    2

void recibir			( int );
void manejador			( int );
void codigoProcesoHijo		( int );
void codigoProcesoPadre		( void );
int serial_open			( char *, speed_t );

int numProc, fd_serie;

int main()
{
	register int i;
	int pid[NUM_PROC];

	if( signal(SIGCHLD, manejador) == SIG_ERR )
	{
		perror("fallo en signal");
		exit(EXIT_FAILURE);
	}

	fd_serie = serial_open( "/dev/ttyUSB0", B9600 );
	printf("serial abierto con descriptor: %d\n", fd_serie);

	numProc = 0;
	for( i = 0; i < NUM_PROC; i++ )
	{
		pid[i] = fork();
		if( pid[i] == -1 )
		{
			perror("Error al crear el proceso");
			exit(EXIT_FAILURE);
		}else if( !pid[i] )	//PROCESOS HIJOS
		{
			codigoProcesoHijo( i + 1 );
		}
	}
	codigoProcesoPadre();

	return 0;
}


void recibir( int signum )
{
	register int i;
	int promedio;
	int suma;
	FILE *apFile;
	int datos[TAM_BLOQUE];

	if( signum == SIGUSR1 )
	{
		printf(" PROCESANDO DATOS EN SEÑAL..\n");

		apFile = fopen("muestras.txt", "r");
		if( !apFile )
		{
			perror("Error en la apertura del archivo de muestras");
			exit(EXIT_FAILURE);
		}
		for( i = 0; i < TAM_BLOQUE; i++ )
			datos[i] = fgetc(apFile);
		fclose(apFile);

		suma = 0;
		for( i = 0; i < TAM_BLOQUE; i++ )
		{
			suma += datos[i];
		}

		promedio = suma >> 8;//(float)suma / (float)TAM_BLOQUE;
		printf("Promedio del bloque: %d \n", promedio);

	}else if( signum == SIGTERM )
	{

		printf(" SEÑAL TERM RECIBIDA..\n");
		//exit(2);
	}

	signal(SIGUSR1, recibir);
}


void codigoProcesoHijo( int id )
{
	register int i;
	int ndatos, pid, lecturas = 0, numBloques = 0;
	unsigned char dato;
	unsigned char datos[TAM_BLOQUE];
	FILE *apFile;

	if( id == 1 ) //PROCESO 1
	{
		printf("Proceso %d, ejecutado\n", id);
		while(1)
		{
			ndatos = read ( fd_serie, &dato, 1 );
			if( ndatos != -1 )
			{
				datos[lecturas++] = dato;
				printf("dato: %d \n", dato);
				if( lecturas == TAM_BLOQUE )
				{
					apFile = fopen("muestras.txt", "w");
					if( !apFile )
					{
						perror("Error en la apertura del archivo de muestras");
						exit(EXIT_FAILURE);
					}
					for( i = 0; i < TAM_BLOQUE; i++ )
						fprintf(apFile,"%d ", datos[i]);
					fclose(apFile);

					lecturas = 0;
					numBloques++;
					pid = getpid();
					kill( pid+1, SIGUSR1 );

					if( numBloques == NUM_BLOQUES )
					{
						sleep(1);
						exit(id);
					}

				}
			}
		}

	}else //PROCESO 2
	{
		if( signal(SIGUSR1, recibir) == SIG_ERR )
		{
			perror("fallo en signal");
			exit(EXIT_FAILURE);
		}

		printf("Proceso %d, ejecutado\n", id);

		for( i = 0; i < NUM_BLOQUES; i++ )
			pause();

		exit(id);
	}
}

void codigoProcesoPadre( void )
{
	register int i;

	printf("Código del proceso padre ejecutado \n");
	while( 1 )
	{
		if( numProc == NUM_PROC )
		{
			close( fd_serie );
			exit(0);
		}
	}
}

void manejador( int numSig )
{
	int pid, salida;

	numProc++;
	pid = wait( &salida );
	printf("Proceso %d con ID: %d terminado, #señal: %d\n", pid, salida>>8, numProc);

	signal(SIGCHLD, manejador);
}


