#!/bin/bash
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

INPUT=$1
OUTPUT=$2

# Validate if the arguments are given
if [ "$#" -ne 2 ] ; then
	echo "Usage: $0 [1-5] [1-5]"
	exit 1
fi

# Validate input between 0 and 5
validate_number() {

	if [ "$1" -lt 0 -o "$1" -gt 5 ] ; then
		echo "The input must be between 0 and 5, because it is the analog input GPIO"
		exit 1
	fi

}

validate_number "$INPUT"
validate_number "$OUTPUT"

# Input is different from output
if [ "$INPUT" -eq "$OUTPUT" ] ; then
	echo "The arguments must be different"
	exit 1
fi

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
GPIO_IN_NUMBER=$(($INPUT * 2 + 48))
GPIO_OUT_NUMBER=$(($OUTPUT * 2 + 48))
# Path where the GPIOs are managed
GPIO_PATH="/sys/class/gpio"
# Path where we can obtain the value from the GPIO as 
#  voltage
VOLTAGE_PATH="/sys/bus/iio/devices/iio:device0"

# unexport if the directory exists then export the
# GPIO number to use it
if [ -d "$GPIO_PATH"/gpio"$GPIO_IN_NUMBER" ] ; then
	echo "$GPIO_IN_NUMBER" > "$GPIO_PATH"/unexport
	sleep 1
fi
echo "$GPIO_IN_NUMBER" > "$GPIO_PATH"/export

if [ -d "$GPIO_PATH"/gpio"$GPIO_OUT_NUMBER" ] ; then
	echo "$GPIO_OUT_NUMBER" > "$GPIO_PATH"/unexport
	sleep 1
fi
echo "$GPIO_OUT_NUMBER" > "$GPIO_PATH"/export

# Is needed to set the direction of the GPIO
echo "in" > "$GPIO_PATH"/gpio"$GPIO_IN_NUMBER"/direction
echo "out" > "$GPIO_PATH"/gpio"$GPIO_OUT_NUMBER"/direction

# Catch the signals HUP, INT or TERM to stop to script
trap "echo 'Exit' ; exit 1" SIGHUP SIGINT SIGTERM

# Print description
echo "---If the input value is greater than 1000, the output will receive"
echo "---a high level, low level either way"

# Get the value and validate it
while true ; do
	VOLTAGE=$(cat "$VOLTAGE_PATH"/in_voltage"$INPUT"_raw)
	echo "Voltage: $VOLTAGE"
	if [ "$VOLTAGE" -gt 1000 ] ; then
		echo 1 > "$GPIO_PATH"/gpio"$GPIO_OUT_NUMBER"/value
	else
		echo 0 > "$GPIO_PATH"/gpio"$GPIO_OUT_NUMBER"/value
	fi
	sleep 1
done
