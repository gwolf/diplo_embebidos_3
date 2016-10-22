#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "defs.h"

extern int pulsoCardiaco[N], rxx[N];
extern int muestraFinal;

/*
 *	DESCRIPCION: Esta función coloca la aplicacion como un demonio
 *
 *	PARAMETROS: NINGUNO
 *
 * 	RETORNO: NINGUNO
 *****************************************************************************************
 */
void iniDemonio( void )
{
	FILE *apArch;

    pid_t pid = 0;
    pid_t sid = 0;
    int counter = 0;
// Se crea el proceso hijo
    pid = fork();
    if( pid == -1 )
    {
		perror("Error al crear el primer proceso hijo\n");
		exit(EXIT_FAILURE);
    }
// Se termina Proceso padre.
    if( pid )
    {
		//printf("Se termina proceso padre, PID del proceso hijo %d \n", pid);
		exit(0);
    }
// Se restablece el modo de archivo
    umask(0);
//se inicia una nueva sesion
    sid = setsid();
    if( sid < 0 )
    {
		perror("Error al iniciar sesion");
		exit(EXIT_FAILURE);
    }
// Se realiza un segundo fork para separarnos completamente de la sesion del padre
    pid = fork( );
    if( pid == -1 )
    {
		perror("Error al crear el segundo proceso hijo\n");
		exit(EXIT_FAILURE);
    }
    if( pid )
    {
		//printf("PID del segundo proceso hijo %d \n", pid);
		apArch = fopen("/home/proyecto.pid", "w");
		if( apArch == NULL )
		{
			perror("Error al abrir el archivo proyecto.pid\n");
			exit(EXIT_FAILURE);
		}
		
		fprintf(apArch, "%d", pid);
		fclose(apArch);

		exit(0);
    }
// Se cambia el directorio actual por root.
    chdir("/");
// Se cierran los flujos de entrada y salida: stdin, stdout, stderr
    close( STDIN_FILENO  );
    close( STDOUT_FILENO );
    close( STDERR_FILENO );
}

/*
 *	DESCRIPCION: Esta función la ejecutan los procesos hijos  
 *	cada proceso hijo calcula un elemento de la función de autocorrelación
 *	de forma alternada. 
 *	se usa la propiedad de simetria rxx(n) = rxx(-n) para evaluar la parte positiva
 *							  N-1
 *							  _____
 *	Matemáticamente: rxx(l) = \	   x(n)x(n-l)
 *							  /____ 
 *								n = l
 * 	La frecuencia fundamental se encuentra en el primer máximo después del origen
 *	PARAMETROS: 
 * 		id, identificador del proceso
 *		pipefd, Descriptor de tuberia usada para comunicación con el proceso padre
 * 	RETORNO:
 * 		Ninguno
 *****************************************************************************************
 */

void codigoProcesoHijo( int id, int pipefd[] )
{
	register int n, l;
	int fun_creciente = 0;
	int muestra = 0, umbral;

//	printf("Proceso %d, ejecutado\n", id);
	for( l = id; l < L; l += NUM_PROC )
	{		
		rxx[l] = 0;
		for( n = l; n < N; n++ )
		{
			rxx[l] += pulsoCardiaco[n] * pulsoCardiaco[n-l];  
		}
		if( (rxx[l] > rxx[l-NUM_PROC]) && l > NUM_PROC )
		{
			fun_creciente = 1;
		}else if( (rxx[l] < rxx [l-NUM_PROC]) && fun_creciente )
		{	
			fun_creciente = 0;
			umbral = rxx[id] << 3;
			umbral = umbral / 10;
			if( rxx[l] >  umbral )
			{
				muestra = l-NUM_PROC;
				close( pipefd[0] );
				write( pipefd[1], &muestra, sizeof(int) ); 	
				close( pipefd[1] );

	//			printf("Muestra: %d, Frecuencia: %f, Pulsos por minuto: %f\n ", l-NUM_PROC, FS / (l-NUM_PROC), FS / (l-NUM_PROC) * 60 );
				exit(id);
			}
		}
	}
// Cuando no hay señal ....
	close( pipefd[0] );
	write( pipefd[1], &muestra, sizeof(int) ); 	
	close( pipefd[1] );
	exit(id);
}
/*
 *	DESCRIPCION: Esta función ejecuta el código del Proceso Padre, 
 *	espera a que terminen de ejecutarse los procesos hijos y determina
 * 	cual es la muestra correcta que contiene la frecuencia fundamental
 *	PARAMETROS: 
 *		pipefd, Descriptor de tuberia usada para comunicación con los procesos hijos
 * 	RETORNO:
 * 		Ninguno
 *****************************************************************************************
 */

void codigoProcesoPadre( int pipefd[] )
{
	register int i;
	int pid, salida, muestra;

	muestraFinal = 0;

	close( pipefd[1] );
	for( i = 0; i < NUM_PROC; i++ )
	{
		read( pipefd[0], &muestra, sizeof(int) );
		pid = wait( &salida );		
		if( muestra > muestraFinal )
			muestraFinal = muestra;		
//		printf("Muestra: %d Proceso %d con ID: %d terminado\n", muestra, pid, salida>>8);		
	}
//	if( muestraFinal ) //Si hay señal...
//		printf("Frecuencia: %f, Pulsos por minuto: %f\n ", FS / muestraFinal, FS / muestraFinal * 60 );

	close( pipefd[0] );
}

