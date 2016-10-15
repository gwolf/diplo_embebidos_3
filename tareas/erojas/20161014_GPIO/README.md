
GPIO's Raspberry Pi 3 para la lectura del acelerometro MMA8452


https://cdn.sparkfun.com//assets/parts/9/5/1/5/12756-00.jpg

En esta practica, se implementa la lectura de los valores del eje x y eje y del acelerometro MMA8452 de sparkfun, a los puertos GPIO’s de una Raspberry Pi 3.

Analizando cada una de las funciones de cada GPIO(1) y el datasheet del acelerometro (2) podemos,  definir las terminales GPIO que utilizaremos.
Ya que el sensor se comunica por medio de protocolo i2c utilizaremos:

http://www.myelectronicslab.com/wp-content/uploads/2016/06/raspbery-pi-3-gpio-pinout-40-pin-header-block-connector-1-1.png

Accelerometer	Name	Remarks		Rpi Pin		Rpi Function
	1	     	VCC		+3.3v		  01	   	    3.3v
	2	     	GND		Ground        06		    GND
	3	     	SDA		Data in	      03			SDA1
	4 	   		SCL		Clock	      05            SCL1

Para su comunicación utilizaremos python-smbus y i2c-tool ($ sudo apt-get install python-smbus i2c-tools); su configuracion abriendo el canal de comunicación desde la configuracion de la raspberry ($ sudo raspi-config) y agregar la siguiente linea en el archivo /etc/modules :

 i2c-bcm2708

Con el comando 

$ sudo i2cdetect -y 1 

Obtenemos la direccion de nuestro dispositivo que en este caso es “1D”

Una vez echo lo anterior, podemos hacer uso de el sensor con el archivo python, referenciado a leer el datasheet para ajustar los parametros de los registros principales por default.


Regferencias:

http://www.anstack.com/blog/2016/07/05/accelerometer-intro.html
http://cache.nxp.com/files/sensors/doc/data_sheet/MMA8452Q.pdf






