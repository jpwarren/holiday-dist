#!/bin/bash
#
# set_devmode sets the developer mode on or off, depending on the value passed in $1
# If the mode is already set correctly, it does nothing.
#
NEWSTATE=$1
echo $NEWSTATE
#
if [ $NEWSTATE -eq "True" ]
then
    # Let's turn the sshd on
    if [ -e /run/sshd.pid ]
    then
        echo ":: sshd already on, not changing state."
        exit 0
    else
        echo ":: starting sshd..."
        sudo /etc/rc.d/sshd start
        exit 0
    fi
else
    # Let's turn the sshd off
    if [ -e /run/sshd.pid ]
    then
        echo ":: stopping sshd..."
        sudo /etc/rc.d/sshd stop
        exit 0
    else
        echo ":: sshd already stopped, not changing state."
        exit 0
    fi
fi