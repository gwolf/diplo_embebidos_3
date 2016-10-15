from adxl345 import ADXL345
import time
  
#Funcion para poder obetner la direccion del sensor. Se pone en un try-catch para
#poder reeintentar la lectura del sensor aún cuando pueda existir algún conflicto
#en con el protocolo i2c
def try_io(tries=10):
	assert tries > 0
	error = None
	adxl345 = None
	
	while tries:
	    try:
		adxl345 = ADXL345()
	    except IOError as e:
		error = e
		tries -= 1
	    else:
		break

	if not tries:
	    raise error
	
	return adxl345

#El resto dle programa, utilizado para la lectura consecutiva de los datos de cada eje 
#del acelerometro
while True:    
	x = try_io()

	if x is None:
       		print("result")
	else:
		axes = x.getAxes(False)
       		print "ADXL345 on address 0x%x:" % (x.address)
       		print "   x = %.3f" % ( axes['x'] )
       		#print "   y = %.3f" % ( axes['y'] )
       		#print "   z = %.3f" % ( axes['z'] )
       		time.sleep(1)
