#!/bin/bash

#La tarjeta BeagleBone tiene 4 leds nombrados USER0, USER1, USER2 y USER3

cd /sys/class/leds/beaglebone:green:usr0	#El archivo que hace referencia al led USR0 se encuentra en esta ruta 
echo timer > trigger						#Se activa el modo de temporizador en el led USR0

