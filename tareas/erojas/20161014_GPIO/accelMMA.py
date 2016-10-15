#!/usr/bin/env python

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)
#MMA8452Q direccion 0x1D
# Select Control register: 0x2A
#		0x00(00)	Modo StandBy 
bus.write_byte_data(0x1D, 0x2A, 0x00)
# Control register: 0x2A
#		0x01(01)	Modo activo
bus.write_byte_data(0x1D, 0x2A, 0x01)
# Configuration register: 0x0E
#		0x00(00)	Ajusta el rango  +/- 2g
bus.write_byte_data(0x1D, 0x0E, 0x00)
time.sleep(0.1)

# Leemos los datos de 0x00(0), en bloques de 7 bytes
# Status register: X-Axis MSB, X-Axis LSB, Y-Axis MSB, Y-Axis LSB, Z-Axis MSB, Z-Axis LSB
while True:
    data = bus.read_i2c_block_data(0x1D, 0x00, 7)
    xAccl = (data[1] * 256 + data[2]) / 16
    
		if xAccl > 2047 :
            xAccl -= 4096

    yAccl = (data[3] * 256 + data[4]) / 16
    if yAccl > 2047 :
            yAccl -= 4096

   #Imprime los valores

    print "Acceleration in X-Axis : %d" %xAccl
    print "Acceleration in Y-Axis : %d" %yAccl
    time.sleep(1)
    
