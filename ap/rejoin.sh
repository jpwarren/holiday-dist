#!/bin/bash
#
# Rejoin the last network we were on, if possible.
# Uses wpa_supplicant - so be careful about that.
#
cp /home/holiday/ap/wpa_supplicant.conf.last /home/holiday/ap/wpa_supplicant.conf
cat /home/holiday/ap/wpa_supplicant.conf
#exit 0
/home/holiday/ap/wlan-off.sh
/home/holiday/ap/wlan-on.sh
if [ $? -eq "0" ]
then
	echo "Rejoined former wireless network"
	exit 0
else
	echo "Could not rejoin network $1"
	exit 1
fi
