#!/bin/sh

### BEGIN INIT INFO
#
# Provides:          Station X
# Should-Start:
# Required-Start:    
# Required-Stop:     
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Demonio para la BeagleBone Black
# Description:       Script de inicio para Debian para ejecutar Station X
#
### END INIT INFO


. /lib/lsb/init-functions

DAEMON=/readADC.py
NOMBRE=readADC
LOGFILE=/var/log/readADC.log
ERRFILE=/var/log/readADC.err
DESCRIPCION="Station X"

test -x $DAEMON || exit 0

set -e

case "$1" in

    start) 
        log_daemon_msg "Arrancando $DESCRIPCION" "$NOMBRE"
        start-stop-daemon --start --background --pidfile /var/run/$NOMBRE.pid --make-pidfile --quiet --startas /bin/bash -- -c "exec $DAEMON >$LOGFILE 2>$ERRFILE"
        log_end_msg $?
        ;;
    stop)
        log_daemon_msg "Parando $DESCRIPCION" "$NOMBRE"
        start-stop-daemon --stop --oknodo --quiet --pidfile /var/run/$NOMBRE.pid
        log_end_msg $?
        ;;
    restart)
        log_daemon_msg "Reiniciando $DESCRIPCION" "$NOMBRE"
        start-stop-daemon --stop --oknodo --quiet --pidfile /var/run/$NOMBRE.pid
        sleep 1
        start-stop-daemon --start --background --pidfile /var/run/$NOMBRE.pid --make-pidfile --quiet --startas /bin/bash -- -c "exec $DAEMON >$LOGFILE 2>$ERRFILE"
        log_end_msg $?
        ;;
    force-reload)
        restart
        ;;
    *)
        log_failure_msg "Uso: /etc/init.d/$NOMBRE {start|stop|restart|force-reload}"
esac

exit 0
