/*
 *	Descripción: Este modulo contiene las diversas funciones utiles, como el manejo de señales
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

extern int banDevListo;

/*
 * DESCRIPCION: Esta función proporciona la funcionalidad de las señales
 * 
 * PARAMETROS:
 *	signum - Señal recibida por el demonio
 *
 * RETORNO:
 *	Ninguno
 *****************************************************************************************
 */

void manejador(int signum)
{
	if( signum == SIGUSR1 )
		banDevListo = 1;
	else if( signum == SIGUSR2 )
		banDevListo = 0;
}

/*
 * DESCRIPCION: Esta función inicializa las señales USR1 y USR2
 * 
 * PARAMETROS:
 *	Ninguno
 *
 * RETORNO:
 *	Ninguno
 *****************************************************************************************
 */

void iniSignals( void )
{
	if( signal(SIGUSR1, manejador) == SIG_ERR )
	{
		perror("fallo en signal");
		exit(EXIT_FAILURE);
	}
	if( signal(SIGUSR2, manejador) == SIG_ERR )
	{
		perror("fallo en signal");
		exit(EXIT_FAILURE);
	}
}

/*
 * Descripción: Esta función verifica los codigos de retorno de funciones
 *
 * PARAMETROS:
 *   codigo: Código generado por la función
 *   msjError: Mensaje de error a desplegar
 * RETORNO:
 *   Ninguno
 **************************************************************************************
 */

void verificaError( int codigo, char msjError[] )
{
	if( codigo  == -1 )
  	{
		perror( msjError );
		exit( EXIT_FAILURE );
  	}
}

/*
 * DESCRIPCION: Esta funcion guarda los datos de la señal de pulso cardiaco 
 * 	y la funcion de autocorrelacion en archivos para su posterior graficacion
 *
 * PARAMETROS: 
 *	archivo:	Nombre del archivo
 *	datos:		Arreglo de datos a guardar
 *	numDatos:	Número de datos a guardar
 * 
 * RETORNO:
 *	NINGUNO  
 *****************************************************************************************
 */
void guardaDatosArch( int datos[], char archivo[], int numDatos )
{
	FILE *apFile;
	register int i;

	apFile = fopen( archivo, "w");
	if( apFile == NULL )
	{
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}

	for( i = 0; i < numDatos; i++ )
	{
		fprintf(apFile, "%d \n", datos[i]);
	}
	fclose(apFile);	
}

/*
 * DESCRIPCION: Esta función genera un retardo de 2^32 ciclos de reloj
 * 
 * PARAMETROS:
 *	Ninguno
 *
 * RETORNO:
 *	Ninguno
 *****************************************************************************************
 */

void retardo ( void )
{
	register unsigned int delay;

	for( delay = 0; delay < 0xFFFFFFFF; delay++ );

}


