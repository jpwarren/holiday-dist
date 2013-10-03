#!/bin/bash
#
# Start the app described by the path in $1 $2 $3 $4...
# Run it in the background, and create a PID file for it
# Then exit
#
echo "Starting $1 $2 $3 $4 $5 $6 $7 $8 $9"
#
$1 $2 $3 $4 $5 $6 $7 $8 $9 >> /dev/null &
echo $! > /run/iotas-app.pid
exit 0
