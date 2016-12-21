#!/bin/bash
#
# This script is only called on first boot at the factory
# Or when specifically reset to this state.
# It does some checks, logs onto WiFi, transmits serial number & mac
# Then indicates all has gone well.
#
# Written by Mark Pesce, September 2013
#
chmod 666 /dev/mem
echo ":: Entering Firstboot tests"
#
# Stop the buttonapd so we don't fight over the buttons
#
/etc/rc.d/buttonappd stop
#
# We should send the latest firmware to the AVR here
# If it fails after 10 repeated tries, we have a problem, Houston.
#
pushd .
cd /home/holiday/dev/holidayduino
python holidayduino_update.py
popd
#
# Before anything else, change the hostname based on the MAC address
# Set the name of this Holiday
#
newname=holiday-`/home/holiday/util/wlan_mac_addr.sh`
echo ":: Setting hostname to "$newname
hostname $newname
echo $newname > /etc/hostname
sync
#
# Next, bring up the wlan interface
# And try to join a network that shoud in theory be there to join
#
echo ":: Joining MooresTest wlan -- will take 10 seconds..."
wpa_supplicant -B -iwlan0 -c/home/holiday/.firstboot/wpa_firstboot.conf 
#
/home/holiday/art/clearall.sh
/home/holiday/art/cspinner.sh 10 0x001080 0x002080 0x0040a0 0x1080c0 0x003080
#
echo ":: Acquiring Address -- will take a few more seconds..."
dhcpcd wlan0
/home/holiday/art/clearall.sh
/home/holiday/art/cspinner.sh 10 0x008020 0x008040 0x008060 0x10c080 0x008050
#
# Ok, we should have connectivity, so test it.
#
#sudo /home/mpesce/scripts/reduino.sh
echo ":: Testing wlan connectivity..."
#
/home/holiday/.firstboot/test_wlan.sh
if [ $? == 0 ]
then
	echo ":: Networking tests passed!"
	/home/holiday/bin/cliclr 0x00FF00
else
	echo ":: Networking tests FAILED"
	/home/holiday/bin/cliclr 0xFF0000
	exit 1
fi
# 
# Now that we've passed the networking tests
# register our serial number
# not critical if it fails, as long as the label print works
#
/home/holiday/.firstboot/register.sh
#
# Check buttons - only exits when all three buttons have been pressed
#
/home/holiday/.firstboot/checkbuttons.sh
#
# Finally, send label print request
#
/home/holiday/.firstboot/label.sh
if [ $? == 0 ]
then
	echo ":: Label transmission successful, exiting firstboot mode."
	rm /home/holiday/.firstboot/is_firstboot
	sync	# In case they're too quick on the gun.
	/home/holiday/bin/cliclr 0x008000
	exit 0
else
	echo ":: Label transmission FAILED, remaining in firstboot mode."
	/home/holiday/bin/cliclr 0x808000
	exit 1
fi 

