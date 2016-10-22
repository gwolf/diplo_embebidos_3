#!/bin/sh
####
# Script that reads from a GPIO analog values and write 1 or 0
# to another GPIO that writes analog values (but we write high
# voltage or low voltage).
#
# I tested it with a rotation sensor as input and a buzzer as
# output, the script writes 1 to the buzzer if the input value
# is greater than 1000 as voltage input (actually 1V)
#
# This script only works the GPIOs of the intel galileo gen 2
#
# Victor Martinez Sanchez
###

OUTPUT=3

# Validate input between 0 and 5
validate_number() {

	if [ "$1" -lt 0 -o "$1" -gt 5 ] ; then
		echo "The input must be between 0 and 5, because it is the analog input GPIO"
		exit 1
	fi

}

validate_number "$OUTPUT"

# The GPIOs numbers of the analog input are:
# A0 = 48
# A1 = 50
# A2 = 52
# A3 = 54
# A4 = 56
# A5 = 58
# NOTE: We use $1 because of the " the operation fails,
#   but before we ensure the argument is given and it is
#   number
GPIO_OUT_NUMBER=$(($OUTPUT * 2 + 48))
# Path where the GPIOs are managed
GPIO_PATH="/sys/class/gpio"
# Path where we can obtain the value from the GPIO as 
#  voltage
VOLTAGE_PATH="/sys/bus/iio/devices/iio:device0"

# unexport if the directory exists then export the
# GPIO number to use it
if [ -d "$GPIO_PATH"/gpio"$GPIO_OUT_NUMBER" ] ; then
	echo "$GPIO_OUT_NUMBER" > "$GPIO_PATH"/unexport
	sleep 1
fi
echo "$GPIO_OUT_NUMBER" > "$GPIO_PATH"/export

# Is needed to set the direction of the GPIO
echo "out" > "$GPIO_PATH"/gpio"$GPIO_OUT_NUMBER"/direction

# Catch the signals HUP, INT or TERM to stop to script
trap "echo 'Exit' ; exit 1" SIGHUP SIGINT SIGTERM

# Get the value and validate it
while true ; do
	read VALUE
	VOLTAGE=$(echo "$VALUE" | awk '$1=="##TEMP" {print $3}')
	if [ ! -z "$VOLTAGE" ] ; then
		logger "Voltage: $VOLTAGE"
		if [ "$VOLTAGE" -gt 1000 ] ; then
			echo 1 > "$GPIO_PATH"/gpio"$GPIO_OUT_NUMBER"/value
		else
			echo 0 > "$GPIO_PATH"/gpio"$GPIO_OUT_NUMBER"/value
		fi
	fi
	sleep 1
done
