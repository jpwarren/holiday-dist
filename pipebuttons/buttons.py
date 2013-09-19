#!/usr/bin/python
#
"""
Button handling for the Holiday
Reads named pipe and does something meaningful with the output, basically.

Homepage and documentation: http://dev.moorescloud.com/

Copyright (c) 2013, Mark Pesce.
License: MIT (see LICENSE for details)
"""

__author__ = 'Mark Pesce'
__version__ = '0.01-dev'
__license__ = 'MIT'

import sys, subprocess

modelist = [ [ 'colorwheel', [ '/home/holiday/art/cliclr.sh', '0x000000'], False ],
['rainbow', ['/home/mpesce/holiday/rainbow &'], True ], 
[ 'NRL', ['/home/mpesce/sport/nrl', '1'], False ] ,
[ 'AFL', ['/home/mpesce/sport/afl', '1'], False ], 
[ 'clear', [ '/home/holiday/art/clearall.sh' ], False ] ]

modekill = [ [ 'colorwheel', ['echo'] ], 
['rainbow', ['sudo', 'killall', 'rainbow'] ], 
[ 'NRL', ['echo'] ] ,
[ 'AFL', ['echo'] ],
[ 'clear', ['echo'] ] ]

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

wheel_index = len(wheel_colors) >> 1 	# Initial value, middle of wheel

def do_button():

# Handle the button presses.
# Opens the named pipe, and loops, reading things out, 
# As keystrokes come out of the named pipe, we do stuff. And things.

	global wheel_index, wheel_colors
	modeval = 0
	teamcounter = 1
	maxnrl = 16
	maxafl = 18

	try:
		pb = open("/run/pipebuttons.fifo", "r")
	except:
		print("Couldn't open the named pipe.")
		sys.exit(-1)


	# The readline call is going to block.  We're ok with that, for now.
	while (True):
		rl = pb.readline()
		cmd  = rl[0:1]		# Get the command
		
		if cmd == 'M':
			# do Mode thingy
			# First terminate the current mode
			#print modekill[modeval][1]
			subprocess.call(modekill[modeval][1])
			modeval = modeval + 1
			if (modeval == len(modelist)):
				modeval = 0 				# Wrap counter
			#print modelist[modeval][1]
			subprocess.call(modelist[modeval][1], shell=modelist[modeval][2])
			teamcounter = 1
		elif cmd == "O":
			# turn off
			continue
		elif cmd == "+":
			# do the plus thingy
			# Examine the mode value and act accordingly
			if (modelist[modeval][0] == 'NRL'):
				teamcounter = teamcounter + 1
				if (teamcounter > maxnrl):
					teamcounter = 1
				cli = modelist[modeval][1]
				cli[1] = str(teamcounter)
				subprocess.call(cli)
			elif (modelist[modeval][0] == 'AFL'):
				teamcounter = teamcounter + 1
				if (teamcounter > maxafl):
					teamcounter = 1
				cli = modelist[modeval][1]
				cli[1] = str(teamcounter)
				subprocess.call(cli)
			elif (modelist[modeval][0] == 'colorwheel'):
				wheel_index = wheel_index + 1
				if (wheel_index >= len(wheel_colors)):
					wheel_index = 0	
				cli = modelist[modeval][1]
				color_value = (wheel_colors[wheel_index][0] << 16) + (wheel_colors[wheel_index][1] << 8) + wheel_colors[wheel_index][2]
				cli[1] = "0x%06X" % color_value
				#print cli
				subprocess.call(cli)
		elif cmd == "-":
			# do the minus thingy
			# Examine the mode value and act accordingly
			if (modelist[modeval][0] == 'NRL'):
				teamcounter = teamcounter - 1
				if (teamcounter < 1):
					teamcounter = maxnrl
				#print ("teamcounter %d" % teamcounter)
				cli = modelist[modeval][1]
				cli[1] = str(teamcounter)
				subprocess.call(cli)
			elif (modelist[modeval][0] == 'AFL'):
				teamcounter = teamcounter - 1
				if (teamcounter < 1):
					teamcounter = maxafl
				#print ("teamcounter %d" % teamcounter)
				cli = modelist[modeval][1]
				cli[1] = str(teamcounter)
				subprocess.call(cli)
			elif (modelist[modeval][0] == 'colorwheel'):
				wheel_index = wheel_index - 1
				if (wheel_index < 0):
					wheel_index = len(wheel_colors) - 1	
				cli = modelist[modeval][1]
				color_value = (wheel_colors[wheel_index][0] << 16) + (wheel_colors[wheel_index][1] << 8) + wheel_colors[wheel_index][2]
				cli[1] = "0x%06X" % color_value
				#print cli
				subprocess.call(cli)
		else:
			print("This should never happen")


if __name__ == '__main__':

	# When we start, clear the string
	subprocess.call(['/home/holiday/art/clearall.sh'], shell=False)

	# If starting up from here, we want to start with the wheel color
	cli = modelist[0][1]
	color_value = (wheel_colors[wheel_index][0] << 16) + (wheel_colors[wheel_index][1] << 8) + wheel_colors[wheel_index][2]
	cli[1] = "0x%06X" % color_value
	#print cli
	subprocess.call(cli)
	do_button()
