#!/usr/bin/python
#
# A very simple app that simply clears the string.
#
import subprocess

class Clearapp:
    def __init__(self):
        """Do some initialization here if required"""
        return

    def start(self):
        """Do whatever is needed to invoke the app"""
        try:
            subprocess.call(['/home/holiday/art/clearall.sh'])
        except:
            print "clearall.sh failed"
        return

    def stop(self):
        """Stop execution of the app"""
        return

    def up(self):
        """Process a press of the up button"""
        return

    def down(self):
        """Process a press of the down button"""
        return