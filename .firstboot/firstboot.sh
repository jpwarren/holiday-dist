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
# We should reset the AVR here
#
# First, we reboot the Arduino
sudo /home/holiday/scripts/reduino.sh
#sleep 2
#
#/home/holiday/bin/cliclr 0x000000
#/home/holiday/bin/cliclr 0x800000
#sleep 1
#/home/holiday/bin/cliclr 0x000000
#/home/holiday/bin/cliclr 0x008000
#sleep 1
#/home/holiday/bin/cliclr 0x000000
#/home/holiday/bin/cliclr 0x000080
#sleep 2
#
# First things first, bring up the wlan interface
# And try to join a network that shoud in theory be there to join
#
echo ":: Joining MooresTest wlan -- will take 10 seconds..."
wpa_supplicant -B -iwlan0 -c/home/holiday/.firstboot/wpa_firstboot.conf 
#
# Have a bit of fun
#
/home/holiday/bin/cliclr 0x080808
sleep 1
#
/home/holiday/bin/cliclr 0x101010
sleep 1
#
/home/holiday/bin/cliclr 0x181818
sleep 1
#
/home/holiday/bin/cliclr 0x202020
sleep 1
#
/home/holiday/bin/cliclr 0x282828
sleep 1
#
/home/holiday/bin/cliclr 0x303030
sleep 1
#
/home/holiday/bin/cliclr 0x383838
sleep 1
#
/home/holiday/bin/cliclr 0x404040
sleep 1
#
/home/holiday/bin/cliclr 0x484848
sleep 1
#
/home/holiday/bin/cliclr 0x505050
sleep 1
#
echo ":: Acquiring Address -- will take a few more seconds..."
dhcpcd wlan0
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
# We need to ship some data over to the label printer.
#
# At this point we need to wait for all three buttons to be pushed
# Apparently in any order we please.  Which is interesting.
#
/home/holiday/.firstboot/label.sh
if [ $? == 0 ]
then
	echo ":: Label transmission successful, exiting firstboot mode."
	rm /home/holiday/.firstboot/is_firstboot
	/home/holiday/bin/cliclr 0x008000
	exit 0
else
	echo ":: Label transmission FAILED, remaining in firstboot mode."
	/home/holiday/bin/cliclr 0x808000
	exit 1
fi 
