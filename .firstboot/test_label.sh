#!/bin/bash
#
# Test for the presence of the label server
#
ping -q -c 5 moorescloud.local
echo $?
if [ $? != "0" ] 
  then
	echo ":: moorescloud.local not found, trying again..."
	ping -q -c 10 moorescloud.local
	if [ $? != "0" ]
	  then
		echo ":: moorescloud.local still not found, last try..."
		ping -q -c 15 moorescloud.local
		if [ $? != "0" ] 
		  then
			exit 1
		fi
	fi
fi
exit 0
