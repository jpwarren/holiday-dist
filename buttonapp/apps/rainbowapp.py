#!/usr/bin/python
#
# A very simple app that simply clears the string.
#
import subprocess

from api.base import ButtonApp
from registry import appregistry

class Rainbowapp(ButtonApp):

    name = 'rainbow'
    
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

appregistry.register(Rainbowapp)
