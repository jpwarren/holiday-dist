#!/usr/bin/python
#
"""
Button handling for the Holiday
Reads named pipe and does something meaningful with the output, basically.
Finally all lovely and modular making it easy to add new button apps.

Homepage and documentation: http://dev.moorescloud.com/

Copyright (c) 2013, Mark Pesce.
License: MIT (see LICENSE for details)
"""

__author__ = 'Mark Pesce'
__version__ = '0.01-dev'
__license__ = 'MIT'

import sys, subprocess
import apps.colorwheelapp, apps.rainbowapp, apps.nrlapp, apps.aflapp, apps.clearapp, apps.blinkyapp

applist = [ apps.clearapp.Clearapp(), apps.colorwheelapp.Colorwheelapp(), 
apps.rainbowapp.Rainbowapp(), apps.nrlapp.Nrlapp(), apps.aflapp.Aflapp(), apps.blinkyapp.Blinkyapp() ]

def do_button():

# Handle the button presses.
# Opens the named pipe, and loops, reading things out, 
# As keystrokes come out of the named pipe, we do stuff. And things.

    global appcounter, on

    try:
        pb = open("/run/pipebuttons.fifo", "r")
        print ("Pipe opened")
    except:
        print("Couldn't open the named pipe.")
        sys.exit(-1)

    # The readline call is going to block.  We're ok with that, for now.
    while (True):
        rl = pb.readline()
        cmd  = rl[0:1]      # Get the command
        
        if cmd == 'M':      # do Mode button press

            if (on == False):
                on = True
                # just restart the current mode
                applist[appcounter].start()
            else:

                applist[appcounter].stop()         # First stop the current mode
                appcounter += 1                    # Increment the app count
                if (appcounter == len(applist)):
                    appcounter = 0                 # Wrap counter
                applist[appcounter].start()         # And start the new mode

        elif cmd == "O":
            on = False
            applist[appcounter].stop()      # stop the existing app
            subprocess.call(['/home/holiday/art/clearall.sh'], shell=False)

        elif cmd == "+": # do the plus button
            applist[appcounter].up()

        elif cmd == "-":  # do the minus button
            applist[appcounter].down()

        else:
            print("This should never happen")


if __name__ == '__main__':

    # When we start, clear the string
    subprocess.call(['/home/holiday/art/clearall.sh'], shell=False)
    appcounter = 0

    on = True       # The string is on, technically

    # Start the first app, if you please
    applist[appcounter].start()

    # And now read the button input....
    do_button()
