#!/bin/bash
#
# Make the color spinner spin for a given number of seconds
#
COUNTDOWN=$1
PID=$$
PIDX=`printf '0x%06X' $PID`
SPIN0="0x000000
$PIDX
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6"

SPIN1="0x000000
$PIDX
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2"

SPIN2="0x000000
$PIDX
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3"

SPIN3="0x000000
$PIDX
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4"

SPIN4="0x000000
$PIDX
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5
$6
$2
$3
$4
$5"
#
while [ $COUNTDOWN -gt 0 ]
do
	echo "$SPIN0">/run/compose.fifo
	sleep .1
	echo "$SPIN1">/run/compose.fifo
	sleep .1
	echo "$SPIN2">/run/compose.fifo
	sleep .1
	echo "$SPIN3">/run/compose.fifo
	sleep .1
	echo "$SPIN4">/run/compose.fifo
	sleep .1
	echo "$SPIN0">/run/compose.fifo
	sleep .1
	echo "$SPIN1">/run/compose.fifo
	sleep .1
	echo "$SPIN2">/run/compose.fifo
	sleep .1
	echo "$SPIN3">/run/compose.fifo
	sleep .1
	echo "$SPIN4">/run/compose.fifo
	sleep .1

	COUNTDOWN=$[COUNTDOWN-1]
	#echo $COUNTDOWN" seconds left"
done
