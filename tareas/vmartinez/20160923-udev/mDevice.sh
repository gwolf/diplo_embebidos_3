#!/bin/bash

# Example of params
# 0 /sys /devices/pci0000:00/0000:00:1d.0/usb2/2-1/2-1.2/2-1.2:1.0/host6/target6:0:0/6:0:0:0/block/sdb sdb

## ACTION = 0 if is device is add 1 is it is removed
## SYSFS = SysFS mount point
## DEVPATH = path where we can get some information from the device
## SD = Name given to the device (KERNEL in udev)
## LOGFILE = absolute path to the file that will serve us as output
ACTION="$1"
SYSFS="$2"
DEVPATH="$3"
SD="$4"
LOGFILE="/tmp/udev_test.txt"

# Close STDOUT
exec 1<&-
# Close STDERR
exec 2<&-
# Open STDOUT and STDERR as $LOG_FILE
exec 1<>"$LOGFILE"
exec 2<>"$LOGFILE"

# truncate LOGFILE
:> "$LOGFILE"

# Absolute path to the device
SDPATH="$SYSFS$DEVPATH"

# Verify the Action
if [ "$ACTION" -ne 1 ] ; then
    echo "The device has been desconnected"
    exit 0
fi
echo "The device has been connected"

# Verify if the device exist
if [ ! -e "/dev/$SD" ] ; then
    echo "The device doesnt exist"
    exit 0
fi

# Verify if the directory exist
if [ ! -d "$SDPATH" ] ; then
    echo "The directory $SDPATH doesnt exist"
    exit 0
fi

# If the file and directory exist we print some information
echo "Location in /dev: "
echo "/dev/$SD"

echo "Number of Partitions: "
echo `ls $SDPATH/ | grep -e 'sdb.' | wc -w`

echo "Vendor: "
echo `cat $SDPATH/device/vendor`

echo "Model: "
echo `cat $SDPATH/device/model`

echo "Stat: "
echo `cat $SDPATH/stat`

echo "Size: "
echo `cat $SDPATH/size`
