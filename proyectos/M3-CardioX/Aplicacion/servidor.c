#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "defs.h"

#define PUERTO 			5000	//Número de puerto asignado al servidor
#define COLA_CLIENTES 	5 		//Tamaño de la cola de espera para clientes

extern int sockfd, bloques, banDatosProcesados, muestraFinal, banDevListo;

/*
 * DESCRIPCION: Este hilo se encarga de ejecutar al servidor
 *
 * PARAMETROS:
 *	Ninguno
 *
 * RETORNO:
 *	Ninguno
 *****************************************************************************************
 */
void *hiloServidor( void *id )
{
	int rank = *(int *)id;
	int cliente_sockfd;

//	printf("Hilo %d Ejecutado \n", rank);

//	printf ("En espera de peticiones de conexión ...\n");

   	//Selecciona un cliente de la cola de conexiones establecidas
   	//se crea un nuevo descriptor de socket para el manejo
   	//de la nueva conexion. Apartir de este punto se debe
   	//utilizar el nuevo descriptor de socket
	   	
   	if( (cliente_sockfd = accept(sockfd, NULL, NULL)) < 0 )
	{
		perror("Ocurrio algun problema al atender a un cliente");
		exit(EXIT_FAILURE);	
   	}
	while( banDevListo )
	{
		if( banDatosProcesados )
		{
			banDatosProcesados = 0;

		   	if( write (cliente_sockfd, &muestraFinal, sizeof(int)) < 0 )
			{
				perror("Ocurrio un problema en el envio de la muestra al cliente");
				exit(EXIT_FAILURE);
		   	}
		}
	//	if( !banDevListo ) break;
	}
	//Termina el cliente
	muestraFinal = -1;	   	
	if( write (cliente_sockfd, &muestraFinal, sizeof(int)) < 0 )
	{
		perror("Ocurrio un problema en el envio de la muestra al cliente");
		exit(EXIT_FAILURE);
	}

	close (cliente_sockfd);

//	printf("Saliendo del hilo servidor \n");
	close (sockfd);
	pthread_exit( id );
}

/*
 * DESCRIPCION: Esta función se encarga de inicializar el servidor TCP
 *
 * PARAMETROS:
 *	Ninguno
 *
 * RETORNO:
 *	Descriptor del socket
 *****************************************************************************************
 */
int iniServidor( void )
{
   	struct sockaddr_in direccion_servidor; //Estructura de la familia AF_INET, que almacena direccion

   	//Se configura la direccion IPv4 para configurar el socket
   	memset (&direccion_servidor, 0, sizeof (direccion_servidor));	//se limpia la estructura con ceros
   	direccion_servidor.sin_family 		= AF_INET;
   	direccion_servidor.sin_port 		= htons(PUERTO);
   	direccion_servidor.sin_addr.s_addr 	= INADDR_ANY;

	//Creacion de las estructuras necesarias para el manejo de un socket
	//AF_INET - protocolos de Internet
	//SOCK_STREAM - Protocolo orientado a conexión
//   	printf("Creando Socket ....\n");
   	if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Ocurrio un problema en la creacion del socket");
		exit(1);
   	}

   	//Configuracion del socket mediante la direccion IPv4
//   	printf("Configurando socket ...\n");
   	if( bind(sockfd, (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor)) < 0 )
	{
		perror ("Ocurrio un problema al configurar el socket");
		exit(1);
   	}

   	//Define el socket listo para aceptar peticiones
//   	printf ("Estableciendo la aceptacion de clientes...\n");
	if( listen(sockfd, COLA_CLIENTES) < 0 )
	{
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
		exit(1);
   	}

	return sockfd;
}
/*
 * DESCRIPCION: Esta función se encarga de esperar la ejecución del hilo que se encarga de  
 * ejecutar el servidor
 *
 * PARAMETROS:
 *	Ninguno
 *
 * RETORNO:
 *	Ninguno
 *****************************************************************************************
 */
void waitHiloServidor( pthread_t idHiloServidor )
{
	int *salida, error;

   	error = pthread_join( idHiloServidor, (void **)&salida );
	if( error )
	{
		perror("Error al esperar el hilo");
		exit(1);
	}		
	printf("Hilo Servidor %d terminado...\n", *salida);
}

/*
 * DESCRIPCION: Esta función se encarga de crear el hilo que se encarga de lanza al servidor 
 *
 * PARAMETROS:
 *	Ninguno
 *
 * RETORNO:
 *	Ninguno
 *****************************************************************************************
 */
void forkHiloServidor( int *id, pthread_t *idHiloServidor )
{
	int error;

  	error = pthread_create( idHiloServidor, NULL, hiloServidor, id );
	if( error )
	{
		perror("Error al crear el hilo");
		exit(EXIT_FAILURE);
	}
	printf("Hilo %d creado\n", *id);
}




