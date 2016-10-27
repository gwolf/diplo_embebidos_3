/*
 *	Descripción: Este modulo contiene las funciones para manejo de la
 *	interfaz serie
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <termios.h>
#include <fcntl.h>

#include "defs.h"
#include "util.h"

extern int indiceBuffer, indiceProcesar, fdInterfazSerie, bloques;
extern int banDatosCapturados, banDevListo, bufferCircular[N];
/*
 * DESCRIPCION: Este hilo se encarga de realizar las lecturas de la interfaz serie
 * 	de forma continua en un buffer circular...
 *
 * PARAMETROS:
 *	Ninguno
 *
 * RETORNO:
 *	Ninguno
 *****************************************************************************************
 */
void *hiloSerial( void *id )
{
	int rank = *(int *)id;
	int dato;

	printf("Hilo %d Ejecutado \n", rank);

	while( banDevListo )
	{
		//if( !banDevListo ) break;
		read( fdInterfazSerie, &dato, 1 );
//		printf("Dato %d = %d \n", indiceBuffer, dato );
		bufferCircular[indiceBuffer++] = dato - 160;

		if( !(indiceBuffer % M) )
		{
			indiceProcesar = indiceBuffer;
			banDatosCapturados = 1;
		}
	//	if( bloques == B )break; 
		indiceBuffer = indiceBuffer & 0x0FFF;
	}

//	printf("Saliendo del hilo serial \n");
	close( fdInterfazSerie );
	pthread_exit( id );
}


/*
 * DESCRIPCION: Esta función se encarga de crear el hilo que se encarga de realizar 
 * las lecturas de la interfaz serie de forma continua en un buffer circular...
 *
 * PARAMETROS:
 *	Ninguno
 *
 * RETORNO:
 *	Ninguno
 *****************************************************************************************
 */
void forkHiloSerial( int *id, pthread_t *idHiloSerial )
{
	int error;

  	error = pthread_create( idHiloSerial, NULL, hiloSerial, id );
	if( error )
	{
		perror("Error al crear el hilo");
		exit(EXIT_FAILURE);
	}
	printf("Hilo %d creado\n", *id);
}

/*
 * DESCRIPCION: Esta función se encarga de esperar la ejecución del hilo que se encarga de realizar 
 * las lecturas de la interfaz serie de forma continua en un buffer circular...
 *
 * PARAMETROS:
 *	Ninguno
 *
 * RETORNO:
 *	Ninguno
 *****************************************************************************************
 */
void waitHiloSerial( pthread_t idHiloSerial )
{
	int *salida, error;

   	error = pthread_join( idHiloSerial, (void **)&salida );
	if( error )
	{
		perror("Error al esperar el hilo");
		exit(1);
	}		
	printf("Hilo Serial %d terminado...\n", *salida);
}


/*
 * DESCRIPCION: Esta funcion Configura la interfaz serie
 *
 * PARAMETROS:
 *   dispositivo_serial: Nombre el dispositivo serial a usar: ttyUSB0, ttyUSB1, etc
 *   baudios: Velocidad de comunicacion. Se usa la constante Bxxxx, donde xxxx  es la
 *          velocidad. Estan definidas en termios.h. Ejemplo: B9600, B19200..
 * RETORNO:
 *   Descriptor del serial
 **************************************************************************************
 */
int configSerial( char dispositivo_serial [], speed_t baudios )
{
	struct termios newtermios;
  	int fd = -1;
/*
 * Se abre un descriptor de archivo para manejar la interfaz serie
 *  O_RDWR - Se abre el descriptor para lectura y escritura
 *  O_NOCTTY - El dispositivo terminal no se convertira en la terminal del proceso
 *  ~O_NONBLOCK - Se hace bloqueante la lectura de datos
 */
	while( fd == -1 )
	{
  		fd = open( dispositivo_serial, O_RDWR | O_NOCTTY & ~O_NONBLOCK );
	}
	//verificaError( fd, "Error al abrir el dispositivo tty" );
/*
 * cflag - Proporciona los indicadores de modo de control
 *		CBAUD	- Velocidad de transmision en baudios.
 * 		CS8	- Especifica los bits por dato, en este caso 8
 * 		CLOCAL 	- Ignora las lineas de control del modem: CTS y RTS
 * 		CREAD  	- Habilita el receptor del UART
 * iflag - proporciona los indicadores de modo de entrada
 * 		IGNPAR 	- Ingnora errores de paridad, es decir, comunicación sin paridad
 * oflag - Proporciona los indicadores de modo de salida
 * lflag - Proporciona indicadores de modo local
 * 		TCIOFLUSH - Elimina datos recibidos pero no leidos, como los escritos pero no transmitidos
 * 		~ICANON - Establece modo no canonico, en este modo la entrada esta disponible inmediatamente
 * cc[]	 - Arreglo que define caracteres especiales de control
 *		VMIN > 0, VTIME = 0 - Bloquea la lectura hasta que el numero de bytes (1) esta disponible
 */
	newtermios.c_cflag 		= CBAUD | CS8 | CLOCAL | CREAD;
  	newtermios.c_iflag 		= IGNPAR;
  	newtermios.c_oflag		= 0;
  	newtermios.c_lflag 		= TCIOFLUSH | ~ICANON;
  	newtermios.c_cc[VMIN]	= 1;
  	newtermios.c_cc[VTIME]	= 0;

// Configura la velocidad
  	verificaError( cfsetospeed( &newtermios, baudios ), "Error al establecer velocidad de salida" );
	verificaError( cfsetispeed( &newtermios, baudios ), "Error al establecer velocidad de entrada" );

// Limpia el buffer de entrada
	verificaError( tcflush( fd, TCIFLUSH ), "Error al limpiar el buffer de entrada" );
// Limpia el buffer de salida
	verificaError( tcflush( fd, TCOFLUSH ), "Error al limpiar el buffer de salida" );
/*
 * Se establece los parametros de terminal asociados con el
 * descriptor de archivo fd utilizando la estrucutura termios
 * TCSANOW - Cambia los valores inmediatamente
 */
	verificaError( tcsetattr( fd, TCSANOW, &newtermios ), "Error al establecer los parametros de la terminal" );

//Retorna el descriptor de archivo
	return fd;
}

/*
 * DESCRIPCION: Esta función lee las muestras provenientes de la interfaz serie  
 *	Se leen 128 muestras para calcular la función de autocorrelación de un bloque de 
 *  4096 muestras, lo que significa que se tiene un traslape de 3968 muestras.
 * 
 * PARAMETROS:
 *	fdSerial: Descriptor de la interfaz serie
 *  pulso: Arreglo donde se colocan las muestras
 *
 * RETORNO:
 *   Ninguno
 *****************************************************************************************
 */
void leerDatosSerial( int datos[], int fdSerial, int numDatos )
{
	register int i;
	int ndatos;
	unsigned char dato;

	for( i = 0; i < numDatos; i++ )
	{
		ndatos = read ( fdSerial, &dato, 1 );
		datos[i] = (int)dato;
		printf("datos: %d \n", ndatos);
	}
}

