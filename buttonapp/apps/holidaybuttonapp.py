#!/usr/bin/python
#
"""
Holiday Button App class implementation for Holiday by Moorescloud

Homepage and documentation: http://dev.moorescloud.com/

Copyright (c) 2013, Mark Pesce.
License: MIT (see LICENSE for details)
"""

__author__ = 'Mark Pesce'
__version__ = '1.0b4'
__license__ = 'MIT'

import sys, os

class Holidaybuttonapp:

	NUM_GLOBES = 50

	# Storage for all 50 globe values
	# 
	globes = [ [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00],
	[ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00],
	[ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00],
	[ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00],
	[ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00],
	[ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00],
	[ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00],
	[ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00],
	[ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00],
	[ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00], [ 0x00, 0x00, 0x00] ]

	def __init__(self):
		self.pid = os.getpid()			# Must pass PID to compose
		self.pipename = '/run/compose.fifo'
		try:
			self.pipe = open(self.pipename,"wb")
		except:
			print "Couldn't open the pipe, there's gonna be trouble!"
			self.pipe = None
		return

	def setglobe(self, globenum, r, g, b):
		"""Set a globe"""
		if (globenum < 0) or (globenum >= self.NUM_GLOBES):
			return
		self.globes[globenum][0] = r
		self.globes[globenum][1] = g
		self.globes[globenum][2] = b

	def getglobe(self, globenum):
		"""Return a tuple representing a globe's RGB color value"""
		if (globenum < 0) or (globenum >= self.NUM_GLOBES):
			return False
		return (self.globes[globenum][0], self.globes[globenum][1], self.globes[globenum][2])

	def chase(self, direction="True"):
		"""Rotate all of the globes around - up if TRUE, down if FALSE"""
		return

	def rotate(self, newr, newg, newb, direction="True", ):
		"""Rotate all of the globes up if TRUE, down if FALSE
		   Set the new start of the string to the color values"""
		return

	def render(self):
		"""The render routine varies depending on where it's running.
		It's running locally on a Holiday uses composed to send globe values out directly."""
		rend = []
		rend.append("0x000010\n")		# clear flag set for now 
		pid_str = "0x%06x\n" % self.pid
		rend.append(pid_str)
		#print pid_str
		#compositor_str = compositor_str + pid_str		# First two lines are placeholders for now, will be meaningful
		ln = 0
		while (ln < self.NUM_GLOBES):
			tripval = (self.globes[ln][0] * 65536) + (self.globes[ln][1] * 256) + self.globes[ln][2]
			rend.append("0x%06X\n" % tripval)
			ln = ln+1
		self.pipe.write(''.join(rend))
		self.pipe.flush()
		return

if __name__ == '__main__':
	hol = Holiday(remote=False)
	print hol
	hol.render()

