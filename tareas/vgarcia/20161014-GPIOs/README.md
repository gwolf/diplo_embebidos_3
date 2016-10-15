# Practica de manejo de GPIOs usando la Raspberry PI 3

En esta practica se implementa un contador hexadecimal decodificado 
a un display de siete segmentos de cátodo común.

Se utiliza la libreria wiringPI para configurar los GPIOs.

Se configuran 7 terminales como salida para controlar cada segmento
de display.

Se configura 1 terminal de entrada con una resistencia de PULL-UP
como señal de control (CTRL) del contador. Con esta señal se manejan
dos operaciones:

CTRL = 1, conteo ascendente
CTRL = 0, conteo descendente


