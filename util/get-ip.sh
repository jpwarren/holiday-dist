#!/bin/bash
#
# Send the resolva message out
#
# First, get the local IP address for the Holiday
#
LOCAL_IP=`ifconfig wlan0 | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1'`
echo $LOCAL_IP
