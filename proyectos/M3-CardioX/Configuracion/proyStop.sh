#!/bin/ash

MI_PID=$(cat /home/proyecto.pid)

logger "FTDI conectado con $MI_PID"

if [ -d /proc/$MI_PID ] ; then
	kill -USR2 $MI_PID
	logger "Señal USR2 enviada"
	exit 0
fi

logger "Señal USR2 no enviada"


