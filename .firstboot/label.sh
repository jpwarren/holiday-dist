#!/bin/bash
# 
# Now that we've passed the networking tests
# We need to ship some data over to the label printer.
#
SERIAL_NUMBER=`/home/holiday/.firstboot/serial_number.sh`
MAC_ADDR=`/home/holiday/.firstboot/mac_addr.sh`
echo $SERIAL_NUMBER
echo $MAC_ADDR
JSON1='{"serial":"' 
JSON2='","mac_addr":"'
JSON3='"}'
JSON_DATA=$JSON1$SERIAL_NUMBER$JSON2$MAC_ADDR$JSON3
echo $JSON_DATA > json.dat
cat json.dat
curl -s -f -X PUT -d @json.dat http://moorescloud.local:2343/firstboot/label
if [ $? == 0 ]
then
	echo ":: Label data successfully transmitted"
	rm json.dat
	exit 0
else
	echo ":: Label data tranmission FAILURE"
	/home/holiday/bin/cliclr 0x7f7f00
	rm json.dat
	exit 1
fi

