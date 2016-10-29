#!/usr/bin/python
#import libraries
# Archivos de prueba del GPIO del beagle bone
import Adafruit_BBIO.GPIO as GPIO
import time

#setup del led
led = "P8_13"

GPIO.setup(led,GPIO.OUT)

#Rutina infiinta de parpadeo
while True:
    GPIO.output(led,GPIO.HIGH)
    time.sleep (1)
    GPIO.output (led,GPIO.LOW)
    time.sleep(1)
