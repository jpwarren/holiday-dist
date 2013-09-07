#!/bin/bash
#
#TRUTHY=`ifconfig wlan0 | egrep ether`
#MACADDR=`echo $TRUTHY | egrep -o '..:..:..:..:..:..'`
#echo $MACADDR
MACADDR=`cat /sys/class/net/wlan0/address`
echo $MACADDR
