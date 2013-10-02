#!/bin/bash
#
# Start the app described by the path in $1 $2 $3 $4
# Run it in the background, and create a PID file for it
# Then exit
#
$1 $2 $3 $4 >> /dev/null &
echo $! > /run/iotas-app.pid
exit 0
