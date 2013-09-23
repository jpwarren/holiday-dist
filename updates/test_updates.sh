#!/bin/bash
#
# Test for the pacman updates, 
# Can we do them?
# Is there anything to update?
#
# Try to distinguish by exit code.
#
pacman -Suypq
RESULT=$?
echo $RESULT
if [ $RESULT -eq "1" ] 
then
	echo "Update test failed."
	exit 1
else
	exit 0
fi

