#!/bin/bash
#
# This script sets the hostname to the name provided as $1
#
# It should work perfectly, and if not, exits with a 1
#
sudo hostname $1
RES=$?
if [ $RES -eq "0" ] 
then
    # We need to restart the avahi-daemon for the new hostname, I should think.
    sudo /etc/rc.d/avahi-daemon restart
    exit 0
else
    exit 1
fi