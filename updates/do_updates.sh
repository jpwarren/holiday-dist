#!/bin/bash
#
# Perform pacman updates, 
# Try to distinguish by exit code.
#
pacman -Suy --noconfirm --noprogressbar --quiet
RESULT=$?
echo $RESULT
if [ $RESULT -eq "1" ] 
then
    echo "Update failed."
    exit 1
else
    exit 0
fi