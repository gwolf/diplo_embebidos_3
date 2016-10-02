#!/bin/bash
#: Title	: test1.sh 
#: Date		: 2016-08-26
#: Author	: "Felix Ruiz"
#: Version	: 1.0
#: Description	: Define una secuencia en la tarjeta BB
#: Options	: None
#: vars		: Action status: 1 connected, 0 disconnected

ACTION="$1"
if [ "$1" -eq 1]; then
  echo "$1" >> /tmp/beaglebone1.txt
logger "Defined USB Key connected"
else
  echo "$1" >> /tmp/beaglebone1.txt
   logger "Incorrect USB key connected"
fi

exit 0 # Everything is correct

