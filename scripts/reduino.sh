#!/bin/bash
#
# Reset the Arduino - good thing to do during restart process.
#
#pulse GPIO16 to reset Arduino
[ ! -d /sys/class/gpio/gpio16 ] && echo 16 >/sys/class/gpio/export
echo out >/sys/class/gpio/gpio16/direction
echo 1 >/sys/class/gpio/gpio16/value
#
sleep 1
echo 0 >/sys/class/gpio/gpio16/value
sleep .05
echo 1 >/sys/class/gpio/gpio16/value
#
sleep 3
