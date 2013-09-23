#!/usr/bin/python
#
# A very simple app that simply clears the string.
#
import subprocess

maxnrl = 16
curnrl = 1

class Nrlapp:
    def __init__(self):
        """Do some initialization here if required"""
        curnrl = 1
        return

    def start(self):
        """Do whatever is needed to invoke the app"""
        global curnrl
        try:
            subprocess.call(['/home/holiday/bin/nrl', '%d' % curnrl])
        except:
            print "nrl failed"
        return

    def stop(self):
        """Stop execution of the app"""
        return

    def up(self):
        """Process a press of the up button"""
        global curnrl, maxnrl
        curnrl += 1
        if (curnrl > maxnrl):
            curnrl = 1 
        try:
            subprocess.call(['/home/holiday/bin/nrl', '%d' % curnrl])
        except:
            print "nrl failed"
        return

    def down(self):
        """Process a press of the down button"""
        global curnrl, maxnrl
        curnrl -= 1
        if (curnrl == 0):
            curnrl = maxnrl  
        try:
            subprocess.call(['/home/holiday/bin/nrl', '%d' % curnrl])
        except:
            print "nrl failed"
        return