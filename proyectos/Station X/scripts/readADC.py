#!/usr/bin/python
# librerias a utilizar:  convertidor ADC
# Control LCD
# Math
import Adafruit_BBIO.ADC as ADC
import Adafruit_CharLCD as LCD
import time
import math


# Definiendo GPIO como sensor adc
sensor = "P9_40"
#lcd part
lcd_rs = 'P8_8'
lcd_en = 'P8_10'
lcd_d4 = 'P8_18'
lcd_d5 = 'P8_16'
lcd_d6 = 'P8_14'
lcd_d7 = 'P8_12'
lcd_backLight = 'P8_7'#columnas LCD
lcd_columns = 16
lcd_rows = 1

#Inicio del display LCD
lcd = LCD.Adafruit_CharLCD(lcd_rs,lcd_en,lcd_d4,lcd_d5,lcd_d6,lcd_d7,lcd_columns,lcd_rows,lcd_backLight)
#inicio del convertidor ADC
ADC.setup()

# Lectura initerrumpida del sensor de temperatura
while True:
    reading = ADC.read(sensor)
    lcd.message('Iniciando')
    #Tiempo de interrupción entre lecturas
    time.sleep(5.0)
    # Factor de corrección del LM35
    temp = 115*reading
    time.sleep(1)
    #Mensaje en terminal
    print "La temperatura es: " + str(temp) + " C"
    #Mensaje en el LCD
    lcd.message('Temp. : ' + str(temp))
    time.sleep(2)
    #  Limpia display lcd
    lcd.clear()
