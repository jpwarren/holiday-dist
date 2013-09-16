#!/bin/bash
#
# Join ssid $1 with password $2
# Uses wpa_supplicant - so be careful about that.
#
WPA_HEADER="ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=wheel 
fast_reauth=1"
WPA_BODY="
network={
	ssid=\"$1\"
	psk=\"$2\"	
	priority=2
}"
cp /home/holiday/ap/wpa_supplicant.conf /home/holiday/ap/wpa_supplicant.conf.last
echo "$WPA_HEADER""$WPA_BODY" >/home/holiday/ap/wpa_supplicant.conf
cat /home/holiday/ap/wpa_supplicant.conf
#exit 0
/home/holiday/ap/wlan-off.sh
/home/holiday/ap/wlan-on.sh
if [ $? -eq "0" ]
then
	echo "Joined network $1"
	exit 0
else
	echo "Did not join network $1"
	exit 1
fi
