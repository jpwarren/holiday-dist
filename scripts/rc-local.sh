#!/bin/bash
#
# rc-local.sh: Local multi-user start-up script.
#
if [ -e /home/holiday/.firstboot/is_firstboot ]
then
	echo ":: FIRSTBOOT"
	/home/holiday/.firstboot/firstboot.sh
else
	echo ":: Normal Boot"
	chmod 666 /dev/mem
	echo ":: Resetting AVR328Mega"
	/home/holiday/scripts/reduino.sh
	#/home/holiday/bin/cliclr 0x000080
	/home/holiday/ap/wlan-on.sh
	if [ $? == 0 ]
	then
		echo ":: Network up, setting clock..."
		/root/ntp/ntpset.py &
		#/home/holiday/bin/cliclr 0x008000
	else
		echo ":: No network detected, estabilshing Access Point"
		/home/holiday/ap/ap-on.sh
		#/home/holiday/bin/cliclr 0x008080
	fi
	/home/holiday/scripts/start-holiday.sh
fi
# And do some final stuff, whatever that might be
/home/holiday/scripts/finally.sh
