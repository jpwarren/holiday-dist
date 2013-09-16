#!/bin/bash
#
# Try to keep the interface alive. Does this help?
#
HOSTNAME=`cat /etc/hostname`
HOSTLOCAL=$HOSTNAME".local"
echo $HOSTLOCAL
ping -q -c 1 -Iwlan0 $HOSTLOCAL
