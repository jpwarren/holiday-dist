#!/bin/bash
#
# Check buttons all work
#
echo ":: Waiting for press on all three buttons"

/home/holiday/bin/cliclr 0x004040

MODE="/sys/class/gpio/gpio1/value"
DOWN="/sys/class/gpio/gpio2/value"
UP="/sys/class/gpio/gpio3/value"

# first, make sure none are down
while [ `cat $MODE` -eq 0 -o `cat $DOWN` -eq 0 -o `cat $UP` -eq 0 ]
do
	/home/holiday/bin/cliclr 0xFF0000
	sleep .1
	/home/holiday/bin/cliclr 0x004040
	sleep .1
done

GOTMODE=0
GOTDOWN=0
GOTUP=0

while true
do
	#echo `cat $MODE`
	#echo `cat $DOWN`
	#echo `cat $UP`
	if [ `cat $MODE` -eq 0 -a $GOTMODE -eq 0 ]
	then
		echo ":: Got MODE"
		GOTMODE=1
		/home/holiday/bin/cliclr 0x00FF00
		sleep .1
		/home/holiday/bin/cliclr 0x004040
	fi
	if [ `cat $DOWN` -eq 0 -a $GOTDOWN -eq 0 ]
	then
		echo ":: Got DOWN"
		GOTDOWN=1
		/home/holiday/bin/cliclr 0x00FF00
		sleep .1
		/home/holiday/bin/cliclr 0x004040
	fi
	if [ `cat $UP` -eq 0 -a $GOTUP -eq 0 ]
	then
		echo ":: Got UP"
		GOTUP=1
		/home/holiday/bin/cliclr 0x00FF00
		sleep .1
		/home/holiday/bin/cliclr 0x004040
	fi
	if [ $GOTMODE -eq 1 -a $GOTDOWN -eq 1 -a $GOTUP -eq 1 ]
	then
		echo ":: Seen all buttons"
		sleep .1
		/home/holiday/bin/cliclr 0x00FF00
		sleep .1
		/home/holiday/bin/cliclr 0x000080
		sleep .1
		/home/holiday/bin/cliclr 0x00FF00
		sleep .1
		/home/holiday/bin/cliclr 0x000080
		exit 0
	fi
done

