#!/bin/bash
#
# Test for a duplicate hostname -- we may need to change ours
#
OLD_HOSTNAME=`hostname`
TEMP_HOSTNAME="holiday-"$RANDOM
#
# Change the hostname for the test
#
echo ":: Changing hostname to "$TEMP_HOSTNAME
hostname $TEMP_HOSTNAME
#
# Reload avahi-daemon
#
/etc/rc.d/avahi-daemon restart
/home/holiday/art/spinner.sh 5
#
echo ":: Looking for host with same name..."
ping -c 3 $OLD_HOSTNAME
if [ $? -eq 0 ]
then
	echo ":: We found a host with our name!"
	exit 1
else
	echo ":: No host with our name, restoring"
	hostname $OLD_HOSTNAME
	/home/rc.d/avahi-daemon restart
	/home/holiday/art/spinner.sh 5
	exit 0
fi
