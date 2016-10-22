#!/bin/ash

MI_PID=$(cat /home/proyecto.pid)

logger "FTDI conectado con $MI_PID"

if [ -d /proc/$MI_PID ] ; then
	kill -USR1 $MI_PID
	logger "Señal USR1 enviada" 
	exit 0
fi

logger "Señal no enviada"
exit 0
