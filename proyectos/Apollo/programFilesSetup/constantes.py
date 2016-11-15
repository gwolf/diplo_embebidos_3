#!/usr/nin/python
# -*- coding: utf-8 -*-

class constants(object):
																	# MAPA DE DIRECCIONES DE REGISTROS
    MAX7219_REG_NOOP = 0x0   					
    MAX7219_REG_DIGIT0 = 0x1
    MAX7219_REG_DIGIT1 = 0x2
    MAX7219_REG_DIGIT2 = 0x3
    MAX7219_REG_DIGIT3 = 0x4
    MAX7219_REG_DIGIT4 = 0x5
    MAX7219_REG_DIGIT5 = 0x6       
    MAX7219_REG_DIGIT6 = 0x7
    MAX7219_REG_DIGIT7 = 0x8
    MAX7219_REG_DECODEMODE = 0x9  # MODO DE DECODIFICACION DE DATOS
    MAX7219_REG_INTENSITY = 0xA		# REGISTRO DE CONTROL DE INTENSIDAD
    MAX7219_REG_SCANLIMIT = 0xB		# LIMITE DE DIGITOS PRESENTADOS
    MAX7219_REG_SHUTDOWN = 0xC		# MODO SHUTDOWN (APAGADO AUTOMATICO)
    MAX7219_REG_DISPLAYTEST = 0xF	# MODO DE PRUEBA DEL DISPLAY 