#!/bin/bash
if [ "$1" -eq 1]; then
  echo "$1" >> /tmp/beaglebone1.txt
logger "Se ha conectado la USB de Samuel"
else
  echo "$1" >> /tmp/beaglebone1.txt
   logger " No se ha conectado la USB de Samuel"
fi


