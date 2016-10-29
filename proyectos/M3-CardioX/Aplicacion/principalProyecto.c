/*
 *	Descripción: Este programa realiza la detección de frecuencia fundamental de una
 *	señal de pulso cardiaco usando la función de autocorrelación.
 *  Las muestras de la señal de pulso cardiaco son obtenidas mediante el UART
 *  tomando lecturas a una velocidad de 9600 baudios.
 *	El programa calcula esta función en forma paralela usando múltiples procesos.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<syslog.h>

#include"serial.h"
#include"util.h"
#include"defs.h"
#include"servidor.h"
#include"procesos.h"
#include"pds.h"

#define EVER 1

void inicializaDatos( void );

int pulsoCardiaco[N], rxx[N], bufferCircular[N];
int indiceBuffer, indiceProcesar, fdInterfazSerie, sockfd, bloques;
int banDatosProcesados, banDatosCapturados, banDevListo, muestraFinal;

int main()
{
	register int np;

	int pid, pipefd[2], idHilos[] = {1, 2};
	pthread_t idHiloSerial, idHiloServidor;
	
	iniDemonio( );
	iniSignals( );

	for( ;EVER; )
	{
		inicializaDatos( );
		// Se abre un archivo log en modo de escritura.
		openlog( "CARDIOX", LOG_NDELAY | LOG_PID, LOG_LOCAL0 );

		while( !banDevListo );	//Esperamos a que se conecte el dispositivo
		syslog(LOG_INFO, "Dispositivo detectado....");
		retardo();

		sockfd = iniServidor( );
		forkHiloServidor( &idHilos[0], &idHiloServidor );

		syslog(LOG_INFO, "Voy a abrir el serial...");

		fdInterfazSerie = configSerial( "/dev/FTDI_ADQ", B9600 );
		syslog(LOG_INFO, "serial abierto con descriptor: %d\n", fdInterfazSerie );
		//printf("serial abierto con descriptor: %d\n", fdInterfazSerie);
		forkHiloSerial	( &idHilos[1], &idHiloSerial   );

		while( banDevListo )
		{
			if( banDatosCapturados )
			{
				banDatosCapturados = 0;
				ventaneo( );			
				syslog(LOG_INFO, "Bloque No: %d \n", bloques++ );

			//	printf("Bloque No: %d \n", bloques++);
				pipe( pipefd );

				for( np = 0; np < NUM_PROC; np++ )
				{
					pid = fork();
					if( pid == -1 )
					{
						perror("Error al crear el proceso");
						exit(EXIT_FAILURE);
					}else if( !pid )	//PROCESOS HIJOS
					{
						codigoProcesoHijo( np, pipefd );
					}
				}
				codigoProcesoPadre( pipefd );
				banDatosProcesados = 1;	
	//			if( bloques == B ) break; 			
			}
		}
		closelog( );

		waitHiloSerial	( idHiloSerial 	 );
		waitHiloServidor( idHiloServidor );

	}
//	guardaDatosArch( pulsoCardiaco , "pulso.dat" , N );
//	guardaDatosArch( bufferCircular, "buffer.dat", N );

	return 0;
}

/*
 * DESCRIPCION: Esta función inicializa los datos usados en el programa
 * 
 * PARAMETROS:
 *	Ninguno
 *
 * RETORNO:
 *	Ninguno
 *****************************************************************************************
 */
void inicializaDatos( )
{
	register int i;
	
	bloques 			= 0;
	muestraFinal		= 0;
	banDevListo			= 0;			
	banDatosCapturados 	= 0;
	banDatosProcesados 	= 0;
	indiceProcesar		= 0;
	indiceBuffer		= 0;

	for( i = 0; i < N; i++ )
	{
		pulsoCardiaco[i] 	= 0;
		rxx[i] 	 			= 0;
		bufferCircular[i] 	= 0;
	}
}




