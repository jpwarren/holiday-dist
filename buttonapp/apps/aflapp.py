#!/usr/bin/python
#
# A very simple app that simply clears the string.
#
import subprocess
maxafl = 18
curafl = 1

class Aflapp:
    def __init__(self):
        """Do some initialization here if required"""
        curafl = 1
        return

    def start(self):
        """Do whatever is needed to invoke the app"""
        global curafl
        try:
            subprocess.call(['/home/holiday/bin/afl', '%d' % curafl])
        except:
            print "afl failed"
        return

    def stop(self):
        """Stop execution of the app"""
        return

    def up(self):
        """Process a press of the up button"""
        global curafl, maxafl
        curafl += 1
        if (curafl > maxafl):
            curafl = 1 
        try:
            subprocess.call(['/home/holiday/bin/afl', '%d' % curafl])
        except:
            print "afl failed"
        return

    def down(self):
        """Process a press of the down button"""
        global curafl, maxafl
        curafl -= 1
        if (curafl == 0):
            curafl = maxafl 
        try:
            subprocess.call(['/home/holiday/bin/afl', '%d' % curafl])
        except:
            print "afl failed"