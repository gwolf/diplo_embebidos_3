#!/bin/bash
#Command for turning led0 "On"
echo 1 > /sys/class/leds/beaglebone::usr0/brightness
