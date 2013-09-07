#!/bin/bash
#
# Exit 0 if resolva.moorescloud.com can be seen
# Exit 1 if it can't
#
RESOLVA="resolva.moorescloud.com"
ping -c 3 $RESOLVA >> /dev/null

if [ $? -eq 0 ]
then
	echo ":: resolva server found"
	exit 0
else
	echo ":: resolva server NOT FOUND"
	exit 1
fi
