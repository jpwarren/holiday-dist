#!/bin/bash
#
# Update the resolva
#
# Can we see the resolva?
/home/holiday/resolva/test-resolva.sh
if [ $? -eq 1 ]
then
	":: No resolva, aborting"
	exit 1
fi
#
# First, get the local IP address for the Holiday
#
LOCAL_IP=`/home/holiday/util/get-ip.sh`
#
#echo $LOCAL_IP
#
# Get the serial number of the Holiday
#
SERIAL_NUM=`/home/holiday/util/serial_number.sh`
#echo $SERIAL_NUM
#
# Get the MAC address of the Holiday
#
MAC_ADDR=`/home/holiday/util/mac_addr.sh`
#echo $MAC_ADDR
# 
# Format up some JSON
#
JSON1='{"serial":"'$SERIAL_NUM'","mac_addr":"'$MAC_ADDR
JSON2=$JSON1'","local_ip":"'$LOCAL_IP'"}'
echo $JSON2
echo $JSON2 > /home/holiday/resolva/resolva.json
#
# And send it off to the resolva via cURL
#
curl -s -f -X PUT -d @/home/holiday/resolva/resolva.json http://resolva.moorescloud.com/resolva/update
if [ $? -eq 0 ]
then
	echo ":: resolva update succeeded"
	rm /home/holiday/resolva/resolva.json
	exit 0
else
	echo ":: resolva update FAILED"
	exit 1
fi
