#!/usr/bin/python
#
# A very simple app that simply clears the string.
#
import subprocess

from api.base import ButtonApp
from registry import appregistry

class Clearapp(ButtonApp):

    name = 'clear'

    def start(self):
        """Do whatever is needed to invoke the app"""
        try:
            subprocess.call(['/home/holiday/art/clearall.sh'])
        except:
            print "clearall.sh failed"
        return

appregistry.register(Clearapp)
