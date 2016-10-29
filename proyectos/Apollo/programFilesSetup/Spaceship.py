#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
from conf_accM import bus
from lib_m8x8 import device  

device = device()					#Creacion de un objeto que instancia la funcion device()
device.brightness(15)  					#Seleccion del brillo de los leds
x_Axis = 0
y_Axis = 0


while True:

    data = bus.read_i2c_block_data(0x1D, 0x00, 7)	#Se almacena en data la lectura del bus i2c (giroscopio)

    xAccl = (data[1] * 256 + data[2]) / 16		#Se hace una transformacion de los valores que manda el acelerometro
    if xAccl > 2047 :					#en valores entre 1000 y 1000, tanto eje x como eje y					
            xAccl -= 4096
							#Se divide nuestros 2000 valores en 8 rangos, correspondiente a la 	
							#coordenada que se mapeara en la matriz de leds
    if (-750 > xAccl):
        x_Axis = 1
        print "Imprime: %d" %x_Axis
    elif( -500 > xAccl and xAccl > -749):
        x_Axis = 1
        print "Imprime: %d" %x_Axis
    elif( -250 > xAccl and xAccl > -499):
        x_Axis = 2
        print "Imprime: %d" %x_Axis
    elif( 0 > xAccl and xAccl > -249):
        x_Axis = 3
        print "Imprime: %d" %x_Axis
    elif( 0 < xAccl and xAccl < 250):
        x_Axis = 4
        print "Imprime: %d" %x_Axis
    elif( 251 < xAccl and xAccl < 500):
        x_Axis = 5
        print "Imprime: %d" %x_Axis
    elif( 501 < xAccl and xAccl < 750):
        x_Axis = 6
        print "Imprime: %d" %x_Axis
    elif xAccl > 750:
        x_Axis = 7
        print "Imprime: %d" %x_Axis
    
    
    yAccl = (data[3] * 256 + data[4]) / 16
    if yAccl > 2047 :
            yAccl -= 4096

    if (-750 > yAccl):
        y_Axis = 1
        print "Imprime: %d" %y_Axis
    elif( -500 > yAccl and yAccl > -749):
        y_Axis = 1
        print "Imprime: %d" %y_Axis
    elif( -250 > yAccl and yAccl > -499):
        y_Axis = 2
        print "Imprime: %d" %y_Axis
    elif( 0 > yAccl and yAccl > -249):
        y_Axis = 3
        print "Imprime: %d" %x_Axis
    elif( 0 < yAccl and yAccl < 250):
        y_Axis = 4
        print "Imprime: %d" %y_Axis
    elif( 251 < yAccl and yAccl < 500):
        y_Axis = 5
        print "Imprime: %d" %y_Axis
    elif( 501 < yAccl and yAccl < 750):
        y_Axis = 6
        print "Imprime: %d" %y_Axis
    elif yAccl > 750:
        y_Axis = 6
        print "Imprime: %d" %y_Axis
							#Se mandan los valores de las coordenadas al buffer para poder dibujar el led 
							#en la posicion deseada
    
    device.pixel( x_Axis , y_Axis , 1, redraw=False)
    device.pixel( x_Axis -1 , y_Axis  , 1, redraw=False)
    device.pixel( x_Axis, y_Axis +1 , 1, redraw=False)
    device.pixel( x_Axis, y_Axis -1 , 1, redraw=False)
    device.flush()					#Manda a llamar el write de spi para escribir la informacion contenida en el buffer		
    time.sleep(0.01)
    device.pixel( x_Axis , y_Axis, 0, redraw=False)	#Apaga los leds para poder esperar nueva informacion sin perder la forma de la nave
    device.pixel( x_Axis -1, y_Axis, 0, redraw=False)
    device.pixel( x_Axis, y_Axis +1, 0, redraw=False)
    device.pixel( x_Axis, y_Axis -1 ,0, redraw=False)   
    device.flush()
    time.sleep(0.01)  					#Los sleeps sirven para dar tiempo entre nuevas posiciones.
    

