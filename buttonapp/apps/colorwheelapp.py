#!/usr/bin/python
#
# A very simple app that simply clears the string.
#
import subprocess

from api.base import ButtonApp
from registry import appregistry

wheel_colors = [ [ 0xFF, 0x00, 0x00 ],  
[ 0xEF, 0x0F, 0x00 ],   
[ 0xDF, 0x1F, 0x00 ],
[ 0xCF, 0x2F, 0x00 ],
[ 0xBF, 0x3F, 0x00 ],   
[ 0xAF, 0x4F, 0x00 ],
[ 0x9F, 0x5F, 0x00 ],
[ 0x8F, 0x6F, 0x00 ],
[ 0x7F, 0x7F, 0x00 ],
[ 0x6F, 0x8F, 0x00 ],   
[ 0x5F, 0x9F, 0x00 ],
[ 0x4F, 0xAF, 0x00 ],
[ 0x3F, 0xBF, 0x00 ],
[ 0x2F, 0xCF, 0x00 ],
[ 0x1F, 0xDF, 0x00 ],   
[ 0x0F, 0xEF, 0x00 ],
[ 0x00, 0xFF, 0x00 ],   
[ 0x00, 0xF0, 0x0F ],
[ 0x00, 0xE1, 0x1E ],
[ 0x00, 0xD2, 0x2D ],   
[ 0x00, 0xC3, 0x3C ],
[ 0x00, 0xB4, 0x4B ],
[ 0x00, 0xA5, 0x5A ],
[ 0x00, 0x96, 0x69 ],
[ 0x00, 0x87, 0x78 ],   
[ 0x00, 0x78, 0x87 ],
[ 0x00, 0x69, 0x96 ],
[ 0x00, 0x5A, 0xA5 ],
[ 0x00, 0x4B, 0xB4 ],
[ 0x00, 0x3C, 0xC3 ],   
[ 0x00, 0x2D, 0xD2 ],
[ 0x00, 0x1E, 0xE1 ],
[ 0x00, 0x0F, 0xF0 ],
[ 0x00, 0x00, 0xFF ],  
[ 0x0F, 0x00, 0xF0 ],   
[ 0x1E, 0x00, 0xE1 ],
[ 0x2D, 0x00, 0xD2 ],
[ 0x3C, 0x00, 0xC3 ],
[ 0x4B, 0x00, 0xB4 ],
[ 0x5A, 0x00, 0xA5 ],   
[ 0x69, 0x00, 0x96 ],
[ 0x78, 0x00, 0x87 ],
[ 0x87, 0x00, 0x78 ],
[ 0x96, 0x00, 0x69 ],
[ 0xA5, 0x00, 0x5A ],   
[ 0xB4, 0x00, 0x4B ],
[ 0xC3, 0x00, 0x3C ],
[ 0xD2, 0x00, 0x2D ],
[ 0xE1, 0x00, 0x1F ],
[ 0xF0, 0x00, 0x0F ] ]

wheel_index = 0

class Colorwheelapp(ButtonApp):

    name = 'colorwheel'

    def __init__(self):
        """Do some initialization here if required"""
        global wheel_index, wheel_colors
        wheel_index = len(wheel_colors) >> 1    # Initial value, middle of wheel
        return

    def start(self):
        """Do whatever is needed to invoke the app"""
        global wheel_index, wheel_colors
        colorstr = '0x%02x%02x%02x' % (wheel_colors[wheel_index][0], wheel_colors[wheel_index][1], wheel_colors[wheel_index][2]) 
        try:
            subprocess.call(['/home/holiday/art/cliclr.sh', colorstr ])
        except:
            print "cliclr.sh failed"
        return

    def stop(self):
        """Stop execution of the app"""
        return

    def up(self):
        """Process a press of the up button"""
        global wheel_index, wheel_colors
        wheel_index += 1
        if (wheel_index >= len(wheel_colors)):
            wheel_index = 0 
        colorstr = '0x%02x%02x%02x' % (wheel_colors[wheel_index][0], wheel_colors[wheel_index][1], wheel_colors[wheel_index][2]) 
        try:
            subprocess.call(['/home/holiday/art/cliclr.sh', colorstr ])
        except:
            print "cliclr.sh failed"
        return

    def down(self):
        """Process a press of the down button"""
        global wheel_index, wheel_colors
        wheel_index -= 1
        if (wheel_index < 0):
            wheel_index = len(wheel_colors) -1 
        colorstr = '0x%02x%02x%02x' % (wheel_colors[wheel_index][0], wheel_colors[wheel_index][1], wheel_colors[wheel_index][2]) 
        try:
            subprocess.call(['/home/holiday/art/cliclr.sh', colorstr ])
        except:
            print "cliclr.sh failed"
        return

appregistry.register(Colorwheelapp)
