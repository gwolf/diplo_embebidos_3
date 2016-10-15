PIO's Raspberry Pi 3 para la lectura del acelerometro ADXL345
+
+
+
+En esta practica, se implementa la lectura de los valores del eje x y eje y del acelerometro ADXL345 de sparkfun, a los puertos GPIO’s de una Raspberry Pi 3.
+
+Analizando cada una de las funciones de cada GPIO(1) y el datasheet del acelerometro (2) podemos,  definir las terminales GPIO que utilizaremos.
+Ya que el sensor se comunica por medio de protocolo i2c utilizaremos:
+
+http://www.myelectronicslab.com/wp-content/uploads/2016/06/raspbery-pi-3-gpio-pinout-40-pin-header-block-connector-1-1.png
+
Raspberry GPIO pin 	ADXL345 pin
			GND 	GND
			3V 		3V
			SDA 	SDA
			SCL 	SCL
+
+Para su comunicación utilizaremos python-smbus y i2c-tool ($ sudo apt-get install python-smbus i2c-tools); su configuracion abriendo el canal de comunicación desde la configuracion de la raspberry ($ sudo raspi-config) y agregar las siguientes lineas en el archivo /etc/modules :
+
+ i2c-bcm2708
+ i2c-dev
+
+Con el comando 
+
+$ sudo i2cdetect -y 1 
+
+Obtenemos la direccion de nuestro dispositivo que en este caso es “0x53”
+
+Una vez echo lo anterior, podemos hacer uso de el sensor con el archivo python.
+
+
+Referencias:
+
+http://www.anstack.com/blog/2016/07/05/accelerometer-intro.html
https://www.sparkfun.com/datasheets/Sensors/Accelerometer/ADXL345.pdf
