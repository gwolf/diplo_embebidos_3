#!/bin/bash
####
# Este script lee una entrada Analogica de la tarjeta Intel-Galileo,
# Necesitamos como argumento la entrada analogica que deseamos leer de 0 a 5.
### 

INPUT="$1"

# Validamos si es dada
if [ -z "$INPUT" ] ; then
        echo "Usage: $0 [1-5]"
        exit 1
fi

# Validamos entre 0 y 5
if [ "$INPUT" -lt 0 -o "$INPUT" -gt 5 ] ; then
        echo "The input must be between 0 and 5, because it is the analog input GPIO"
        exit 1
fi

# Los GPIOs  de entrada analogica son:
# A0 = 48
# A1 = 50
# A2 = 52
# A3 = 54
# A4 = 56
# A5 = 58
# Dependiendo del GPIO se coloca el numero
GPIO_NUMBER=$(($1 * 2 + 48))
# la direccion manejada
GPIO_PATH="/sys/class/gpio"
# La direccion que contiene el valor del voltaje en Int
#  voltage
VOLTAGE_PATH="/sys/bus/iio/devices/iio:device0"

# quitamos la variable y la volvemos a exportar para el correcto funcionamiento
echo "$GPIO_NUMBER" > "$GPIO_PATH"/unexport
sleep 1
echo "$GPIO_NUMBER" > "$GPIO_PATH"/export

# Necesitamos la direccion del GPIO
# En este caso se asigna entrada
echo "in" > "$GPIO_PATH"/gpio"$GPIO_NUMBER"/direction

# colocamos los manejadores del script
trap "exit 1" SIGHUP SIGINT SIGTERM

while true ; do
        echo $(cat "$VOLTAGE_PATH"/in_voltage"$INPUT"_raw)
        sleep 1
done

