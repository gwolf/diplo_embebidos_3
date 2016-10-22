#!/bin/sh
####
# This script reads from the inte galileo analog input,
# we need as argument the analog input number.
### 

INPUT=0

# Validate if is given
if [ -z "$INPUT" ] ; then
        echo "Usage: $0 [1-5]"
        exit 1
fi

# Validate input between 0 and 5
if [ "$INPUT" -lt 0 -o "$INPUT" -gt 5 ] ; then
        echo "The input must be between 0 and 5, because it is the analog input GPIO"
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
GPIO_NUMBER=$(($INPUT * 2 + 48))
# Path where the GPIOs are managed
GPIO_PATH="/sys/class/gpio"
# Path where we can obtain the value from the GPIO as
#  voltage
VOLTAGE_PATH="/sys/bus/iio/devices/iio:device0"

# We unexport ant the export the GPIO number to use it
echo "$GPIO_NUMBER" > "$GPIO_PATH"/unexport
sleep 1
echo "$GPIO_NUMBER" > "$GPIO_PATH"/export

# We need to set the direction of the GPIO
# In this case if just for input
echo "in" > "$GPIO_PATH"/gpio"$GPIO_NUMBER"/direction

# Catch the signals HUP, INT or TERM to stop to script
trap "exit 1" SIGHUP SIGINT SIGTERM

while true ; do
        echo $(cat "$VOLTAGE_PATH"/in_voltage"$INPUT"_raw)
        sleep 1
done

