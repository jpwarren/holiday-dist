#!/bin/bash
#
# Join a WLAN.  Well, if you can.
# If we do, exit 0.  If not, exit 1.
#
# This is not particularly safe but it is needed.
#
echo ":: Starting WPA_Supplicant"
wpa_supplicant -B -iwlan0 -c/home/holiday/ap/wpa_supplicant.conf 
#
echo ":: Waiting 10 seconds to join any available wireless network"
/home/holiday/art/cspinner.sh 10 0x001080 0x002080 0x0040a0 0x1080c0 0x20a0ff
# 
# At this point we could probably test to see if we have a good network
# Not quite sure how to do this, just yet, so we'll leave it be.
# Instead, we'll try to use dhcpcd to acquire an address from somewhere.
#
echo ":: Acquiring Address - will take another 10 seconds..."
dhcpcd wlan0
/home/holiday/art/cspinner.sh 10 0x200080 0x400080 0x6000a0 0x8010c0 0xa020ff
#
# Ok, do we have a gateway? 
#
TESTY=`route -n | egrep UG`
ISGATEWAY=$?
if [ $ISGATEWAY == 0 ]
then
	echo ":: WLAN connectivity established"
	# And restart avahi-daemon
	/etc/rc.d/avahi-daemon restart
	# Update the resolva in the background
	/home/holiday/resolva/update-resolva.sh &
	exit 0
else
	echo ":: NO WLAN CONNECTIVITY!"
	exit 1
fi

