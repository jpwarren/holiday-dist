#!/bin/bash
#
# Theoretically this will run at the top of rc.sysint
# And take the Holiday into/out of firstboot mode
#
MODE="/sys/class/gpio/gpio1/value"
DOWN="/sys/class/gpio/gpio3/value"
#echo `cat $MODE`
#echo `cat $DOWN`
if [ `cat $MODE` -eq 0 ]
then
	if [ `cat $DOWN` -eq 0 ]
	then
		echo ":: Firstboot reset"
		if [ -f /home/holiday/.firstboot/is_firstboot ]
		then
			rm /home/holiday/.firstboot/is_firstboot
			echo ":: Exiting Firstboot"
		else
			touch /home/holiday/.firstboot/is_firstboot
			echo ":: Entering Firstboot"
		fi
	fi
fi

