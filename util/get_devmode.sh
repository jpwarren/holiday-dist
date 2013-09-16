#!/bin/bash
#
# get_devmode returns 0 if sshd is running (from PID file), 1 otherwise
#
if [ -e /run/sshd.pid ]
then
    exit 0
else
    exit 1
fi