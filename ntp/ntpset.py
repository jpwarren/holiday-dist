#!/usr/bin/python2
#
import ntplib
import time
import subprocess

c = ntplib.NTPClient()
resp = c.request('au.pool.ntp.org', version=3)
txt = resp.tx_time
ts = time.ctime(txt) 
#print ts
cmd = ['date', '-s', ts ]
retval = subprocess.check_output(cmd)
print "NTP: %s" % (retval,)

