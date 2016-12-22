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
__version__ = '1.1b1'
__license__ = 'MIT'

import sys, subprocess
from collections import OrderedDict

from apps.api.base import ButtonApp
from apps.registry import appregistry

applist = appregistry.values()
        
def do_button():
    """
    Handle the button presses.

    Opens the named pipe, and loops, reading things out, 
    As keystrokes come out of the named pipe, we do stuff. And things.
    """

    try:
        pb = open("/run/pipebuttons.fifo", "r")
        print ("Pipe opened")
    except:
        print("Couldn't open the named pipe.")
        sys.exit(-1)

    # We are on
    on = True
    
    # Start an app when we begin.
    appidx = 0
    currentapp = applist[appidx]
    currentapp.start()
        
    # The readline call is going to block.  We're ok with that, for now.
    while (True):
        rl = pb.readline()
        cmd  = rl[0:1]      # Get the command
        if cmd == 'M':      # do Mode button press

            if (on == False):
                on = True
                # just restart the current mode
                currentapp.start()
            else:
                currentapp.stop() 
                appidx += 1       
                # Wrap counter
                if (appidx == len(applist)):
                    appidx = 0

                currentapp = applist[appidx]
                currentapp.start()

        elif cmd == "O":
            on = False
            currentapp.stop()      # stop the existing app
            try:
                subprocess.call(['/home/holiday/art/clearall.sh'], shell=False)
            except OSError, e:
                print "Can't call clearall", e

        elif cmd == "+": # do the plus button
            currentapp.up()

        elif cmd == "-":  # do the minus button
            currentapp.down()

        elif cmd == "R":  # Run a specific app
            print "Running an app"
            appname = rl[1:].rstrip()
            try:
                newapp = appregistry[appname]
                currentapp.stop()
                currentapp = newapp
                currentapp.start()
            except KeyError:
                print "No such app: %s" % appname

        else:
            #print("This should never happen")
            pass

if __name__ == '__main__':

    # When we start, clear the string
    try:
        subprocess.call(['/home/holiday/art/clearall.sh'], shell=False)
    except OSError, e:
        print "Can't call clearall", e

    do_button()
