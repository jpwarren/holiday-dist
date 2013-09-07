#!/bin/bash
#
# Make the color spinner spin for a given number of seconds
#
COUNTDOWN=$1
SPIN0="$2
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

SPIN1="$3
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

SPIN2="$4
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

SPIN3="$5
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

SPIN4="$6
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
	echo "$SPIN0">/run/pipelights.fifo
	sleep .1
	echo "$SPIN1">/run/pipelights.fifo
	sleep .1
	echo "$SPIN2">/run/pipelights.fifo
	sleep .1
	echo "$SPIN3">/run/pipelights.fifo
	sleep .1
	echo "$SPIN4">/run/pipelights.fifo
	sleep .1
	echo "$SPIN0">/run/pipelights.fifo
	sleep .1
	echo "$SPIN1">/run/pipelights.fifo
	sleep .1
	echo "$SPIN2">/run/pipelights.fifo
	sleep .1
	echo "$SPIN3">/run/pipelights.fifo
	sleep .1
	echo "$SPIN4">/run/pipelights.fifo
	sleep .1

	COUNTDOWN=$[COUNTDOWN-1]
	#echo $COUNTDOWN" seconds left"
done
