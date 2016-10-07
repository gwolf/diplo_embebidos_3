#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <syslog.h>

#define EVER 1
#define N 	20

int main(int argc, char *argv[])
{
	FILE *apArch;

	char cad[N];
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
		printf("Se termina proceso padre, PID del proceso hijo %d \n", pid);
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
		printf("PID del segundo proceso hijo %d \n", pid);
		apArch = fopen("/run/demonio.pid", "w");
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
// Se abre un archivo log en modo de escritura.
    openlog( "demonio", LOG_NDELAY | LOG_PID, LOG_LOCAL0 );

    for( ;EVER; ) 
    {
//No bloquea el cambio de contexto, Solo se duerme al proceso por algún tiempo
		sleep(1);
// Codigo del demonio ......
		if( argc == 2 )
		{
			if( !strcmp( argv[1], "start" ) )
				syslog(LOG_INFO, "Demonio inicializado %d", counter++ );
			else if( !strcmp( argv[1], "stop" ) )
			{
				syslog(LOG_INFO, "Demonio detenido %d", counter++ );
				sleep(1);
				apArch = fopen("/run/demonio.pid", "r");
				fscanf(apArch, "%d", &pid );
				fclose(apArch);
				kill( pid, SIGTERM );
				break;
			}
			else if( !strcmp( argv[1], "reload" ) )
			{	
				apArch = fopen("/home/victor/config/mi_demonio.conf", "r");
				fgets(cad, N, apArch);
				syslog(LOG_INFO, "Demonio configurado: %s", cad );
				sleep(1);
				fclose(apArch);
			}
		}else
			syslog(LOG_INFO, "formato: mi_demonio [start|stop|reload]");
    }
    closelog( );

    return 0;
}


