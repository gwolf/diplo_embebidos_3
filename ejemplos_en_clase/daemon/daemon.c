/* Referencias:
 * http://www.thegeekstuff.com/2012/02/c-daemon-process/ 
 * man 3 syslog
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <syslog.h>
int main(int argc, char *argv[])
{
    pid_t process_id = 0;
    pid_t sid = 0;
    int counter = 0;
// Create child process
    process_id = fork();
// Indication of fork() failure
    if (process_id < 0) {
	printf("fork failed!\n");
// Return failure in exit status
	exit(1);
    }
// PARENT PROCESS. Need to kill it.
    if (process_id > 0) {
	printf("process_id of child process %d \n", process_id);
// return success in exit status
	exit(0);
    }
//unmask the file mode
    umask(0);
//set new session
    sid = setsid();
    if (sid < 0) {
// Return failure
	exit(1);
    }
// fork again to ensure completely detaching from parent's session
    process_id = fork();
    if (process_id < 0) {
	printf("second fork failed!\n");
	exit(1);
    }
    if (process_id > 0) {
	printf("process_id of second child process %d \n", process_id);
	exit(0);
    }
// Change the current working directory to root.
    chdir("/");
// Close stdin. stdout and stderr
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
// Open a log file in write mode.
    openlog("demonio", LOG_NDELAY | LOG_PID, LOG_LOCAL0);

    while (1) {
//Dont block context switches, let the process sleep for some time
	sleep(1);
	syslog(LOG_INFO, "%d Logging info...", counter++);
// Implement and call some function that does core work for this daemon.
    }
    closelog();
    return (0);
}
