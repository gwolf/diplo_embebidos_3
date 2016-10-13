#!/bin/bash
#
# Rojas Ortega Esaú
# Equipo n.1

####Cargamos el path del Led correspondiente al usr0 o led0
cd /sys/class/leds/beaglebone:green:usr0
####Comenzamos la rutina para hacer parpadear el led cada segundo
while true; do echo 255 > brightness; sleep 1; echo 0 > brightness;
sleep 1; done;								
