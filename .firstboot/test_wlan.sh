#!/bin/bash
#
# Testing for the wireless LAN
# We don't test for global connectivity
# We do test for the label server, which we need to complete firstboot.
#
/home/holiday/.firstboot/test_network.sh
if [ $? == 0 ]
then
	echo ":: Local networking test PASSED"
	/home/holiday/.firstboot/test_label.sh
	if [ $? == 0 ]
	then
		echo ":: Connectivity test PASSED"
		/home/holiday/bin/cliclr 0x00FF00	
		exit 0
	else
		echo ":: Connectivity test FAILED"
		/home/holiday/bin/cliclr 0xFF3F00	
		exit 2
	fi
else
	echo ":: Local networking test FAILED"
	/home/holiday/bin/cliclr 0xFF0000
	exit 1
fi
