#! /usr/bin/python
print 'ACTIVATED' # Este mensaje solo lo coloco para validar que se esta ejecutando

import RPi.GPIO as GPIO # Se importa la libreria para el uso de los GPIO de la Raspberry
GPIO.setmode(GPIO.BCM)  # Se indica el metodo de identificación de los pines 

# Se declaran las variables a utilizar y el numro de pin de acuerdo al metodo BCM

led=5
boton1=15
boton2=18

# Se declara el modo de uso de los pines y sus variables para saber si seran Entrada o Salida

GPIO.setup(boton1, GPIO.IN, GPIO.PUD_UP)
GPIO.setup(boton2, GPIO.IN, GPIO.PUD_DOWN)
GPIO.setup(led, GPIO.OUT)

# Bucle para estar ejecutandose

while true:

  if GPIO.input(boton1) == False:
    # Mensaje de Encendido  
     print("Led Encendido")
     GPIO.output(led, 1)

  if GPIO.input(boton2) == True:
    # Mensaje de Apagado
     print("Led Apagado")
     GPIO.output(led,0)

# Funcion que reinicia los GPIO
GPIO.cleanup


