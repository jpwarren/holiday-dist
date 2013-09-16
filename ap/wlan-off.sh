#!/bin/bash
#
# Join a WLAN.  Well, if you can.
# If we do, exit 0.  If not, exit 1.
#
# This is not particularly safe but it is needed.
#
if [ -e /run/wpa_supplicant.pid ]
then
    echo ":: WPA_Supplicant shutting down"
    kill `cat /run/wpa_supplicant.pid`
    rm /run/wpa_supplicant.pid
fi
#
# Kill DHCP Client if running
#
echo ":: Shutting down DHCP Client"
if [ -e /run/dhcpcd-wlan0 ]
then
    dhcpcd -k wlan0
fi 
#
# Turn the link off
#
echo ":: wlan0 going down"
ip link set down wlan0
sleep 1
#
echo ":: WLAN off"

