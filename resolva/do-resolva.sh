#!/bin/bash
#
# Send the resolva query out
# Get the serial number of the Holiday
#
SERIAL_NUM=`/home/holiday/util/serial_number.sh`
#echo $SERIAL_NUM
#
JSON1='{"serial":"'$SERIAL_NUM'"}'
echo $JSON1
echo $JSON1 > /home/holiday/resolva/request.json
#
# And send it off to the resolva via cURL
#
curl -f -X POST -d @/home/holiday/resolva/request.json http://resolva.moorescloud.com/resolva/resolve
if [ $? -eq 0 ]
then
	echo ":: resolva request succeeded"
	rm /home/holiday/resolva/request.json
	exit 0
else
	echo ":: resolva request FAILED"
	exit 1
fi
