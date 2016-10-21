#!/bin/bash

# The GPIO number of reset pin
# D7 = 38
GPIO_NUMBER=38
# Path where the GPIOs are managed
GPIO_PATH="/sys/class/gpio"

# unexport if the directory exists then export the
# GPIO number to use it
if [ -d "$GPIO_PATH"/gpio"$GPIO_NUMBER" ] ; then
	echo "$GPIO_NUMBER" > "$GPIO_PATH"/unexport
	sleep 1
fi
echo "$GPIO_NUMBER" > "$GPIO_PATH"/export

# Is needed to set the direction of the GPIO
echo "out" > "$GPIO_PATH"/gpio"$GPIO_NUMBER"/direction

echo 1 > "$GPIO_PATH"/gpio"$GPIO_NUMBER"/value
echo 0 > "$GPIO_PATH"/gpio"$GPIO_NUMBER"/value
