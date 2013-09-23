#!/bin/bash
#
# Here are the scripts that are necessary to start Holiday up
#
# First, we reboot the Arduino
#echo ":: Rebooting AVR328Mega"
#sudo /home/holiday/scripts/reduino.sh
#
# We start the pipelights server, as much depends on this.
#
#echo ":: Starting pipelights"
#sudo killall pipelights
#sudo rm /run/pipelights.fifo
#nohup /home/holiday/pipelights/pipelights >> /dev/null &
#
#
# Then we start up IoTAS, which activates the pipelights FIFO
#
#echo ":: Starting IoTAS"
#nohup sudo /home/holiday/iotas/iotas.py >> /dev/null &
#
#
# Then we start up the pipebuttons, which reads the controller buttons
#
#echo ":: Starting pipebuttons"
#sudo killall pipebuttons
#sudo rm /run/pipebuttons.fifo
#nohup /home/holiday/pipebuttons/pipebuttons >> /dev/null &
#
# Next, we reboot the Arduino
#echo ":: Rebooting AVR328Mega"
#sudo /home/holiday/scripts/reduino.sh
#/home/holiday/bin/cliclr 0x000000
#sleep .1
#/home/holiday/bin/cliclr 0xFFFFFF
#sleep .1
#/home/holiday/bin/cliclr 0x000000
#
# 
# And finally we start up the button process, to do things on button presses
#
#echo ":: Starting button process"
#nohup /home/holiday/pipebuttons/buttons.py >> /dev/null &
#
# And that is all
#
