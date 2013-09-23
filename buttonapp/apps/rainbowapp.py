#!/usr/bin/python
#
# A very simple app that simply clears the string.
#
import subprocess

class Rainbowapp:
    def __init__(self):
        """Do some initialization here if required"""
        return

    def start(self):
        """Do whatever is needed to invoke the app"""
        try:
            subprocess.call(['/home/holiday/bin/rainbow &'], shell=True)
        except:
            print "rainbow failed"
        return

    def stop(self):
        """Stop execution of the app"""
        try:
            subprocess.call(['sudo', 'killall', 'rainbow'])
        except subprocess.CalledProcessError:
            print "termination of rainbow failed"
        return

    def up(self):
        """Process a press of the up button"""
        return

    def down(self):
        """Process a press of the down button"""
        return