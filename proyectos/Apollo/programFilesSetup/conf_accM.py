#!/usr/bin/python

import smbus


bus = smbus.SMBus(1)										#OBTENEMOS BUS DE PROTOCOLO I2C 

bus.write_byte_data(0x1D, 0x2A, 0x00)		# MMA8452Q CON DIRECCION DE IDENTIFICACION, 0x1D
																				# SELECT CONTROL REGISTER, 0x2A(42)
																				#		0x00(00)	STANDBY MODE

bus.write_byte_data(0x1D, 0x2A, 0x01)		
																				# SELECT CONTROL REGISTER , 0x2A(42)
																				#		0x01(01)	ACTIVE MODE
bus.write_byte_data(0x1D, 0x0E, 0x00)
																				# SELECT CONFIGURATION REGISTER, 0x0E(14)
																				#		0x00(00)	SET RANGE +/- 2g


