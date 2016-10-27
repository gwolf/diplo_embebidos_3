echo -n "28" > /sys/class/gpio/unexport
echo -n "32" > /sys/class/gpio/unexport
echo -n "45" > /sys/class/gpio/unexport

echo -n "28" > /sys/class/gpio/export
echo -n "32" > /sys/class/gpio/export
echo -n "45" > /sys/class/gpio/export
echo -n "out" > /sys/class/gpio/gpio28/direction
echo -n "out" > /sys/class/gpio/gpio32/direction
echo -n "out" > /sys/class/gpio/gpio45/direction
echo -n "0" > /sys/class/gpio/gpio28/value
echo -n "1" > /sys/class/gpio/gpio32/value
echo -n "1" > /sys/class/gpio/gpio45/value
stty -F /dev/ttyS0 19200 
echo -n "value" > /dev/ttyS0 
