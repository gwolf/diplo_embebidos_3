#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
from conf_accM import bus
from lib_m8x8 import device  

device = device()
device.brightness(15)
x_Axis = 0
y_Axis = 0


while True:

    data = bus.read_i2c_block_data(0x1D, 0x00, 7)

    # Convert the data
    xAccl = (data[1] * 256 + data[2]) / 16
    if xAccl > 2047 :
            xAccl -= 4096

    if (-750 > xAccl):
        x_Axis = 0
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
        y_Axis = 0
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
        y_Axis = 7
        print "Imprime: %d" %y_Axis

    
##    device.pixel(4, 0, 1, redraw=False)
##    device.flush()
##    time.sleep(1)
##    device.pixel(4, 0, 0, redraw=False)
##    device.flush()
##    time.sleep(1)
##    device.pixel(0, 4, 0, redraw=False)
##    device.flush()
##    time.sleep(1)
##    device.pixel(0, 4, 1, redraw=False)
##    device.flush()
##    time.sleep(1)
##        
                
    device.pixel( x_Axis , y_Axis , 1, redraw=False)
    device.pixel( x_Axis -1 , y_Axis  , 1, redraw=False)
    device.pixel( x_Axis, y_Axis +1 , 1, redraw=False)
    device.pixel( x_Axis, y_Axis -1 , 1, redraw=False)
    device.flush()
    time.sleep(0.01)
    device.pixel( x_Axis , y_Axis, 0, redraw=False)
    device.pixel( x_Axis -1, y_Axis, 0, redraw=False)
    device.pixel( x_Axis, y_Axis +1, 0, redraw=False)
    device.pixel( x_Axis, y_Axis -1 ,0, redraw=False)
    device.flush()
    time.sleep(0.01)  
    

