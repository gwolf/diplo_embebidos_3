#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PUERTO 		5000
#define TAM_BUFFER 	100
#define DIR_IP 		"192.168.3.56"
//#define DIR_IP 		"127.0.0.1"
#define FS 			512.0				//Frecuencia de muestreo

//numero de puerto asignado al servidor
//Dirección del servidor

int main(int argc, char **argv)
{
	int sockfd, muestraFinal, i = 0;
	struct sockaddr_in direccion_servidor;
	char leer_mensaje[TAM_BUFFER];

	//Se configura la direccion IPv4 del servidor a donde se va a
	//establecer la conexion
	memset (&direccion_servidor, 0, sizeof (direccion_servidor));
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(PUERTO);

	//Convierte direcciones de texto IPv4 en forma binaria
	if( inet_pton(AF_INET, DIR_IP, &direccion_servidor.sin_addr) <= 0 )
	{
		perror("Ocurrio un error al momento de asignar la direccion IP");
		exit(EXIT_FAILURE);
	}

	//Creacion de las estructuras necesarias para el manejo de un socket
	printf("Creando Socket ....\n");
	if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Ocurrio un problema en la creacion del socket");
		exit(EXIT_FAILURE);
	}

	//Inicia el establecimiento de una conexion mediante una apertura
	//activa con el servidor
	printf ("Estableciendo conexion ...\n");
	if( connect(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor) ) < 0) 
	{
		perror ("Ocurrio un problema al establecer la conexion");
		exit(EXIT_FAILURE);
	}
	while( 1 )
	{
		printf ("Recibiendo contestacion del servidor ...\n");
		if( read (sockfd, &muestraFinal, sizeof(int)) < 0 )
		{
			perror ("Ocurrio algun problema al recibir datos del cliente");
			exit(EXIT_FAILURE);
		}

		if( muestraFinal > 0 ) //Si hay señal...
			printf("%d - Frecuencia: %f, Pulsos por minuto: %f\n ", i++, FS / muestraFinal, FS / muestraFinal * 60 );
		else if( muestraFinal == -1 )
			break;
	}
	printf ("Terminando cliente...\n");
	//Cierre de la conexion
	close(sockfd);

	return 0;
}

