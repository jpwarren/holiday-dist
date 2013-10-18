#!/usr/bin/python
#
# A very simple app creates random colours and sends them to the string.
# You can change the frequency with the up and down buttons
#
import subprocess, holidaybuttonapp, time, threading, random

class Blinkyapp:

    def __init__(self):
        """Do some initialization here if required"""
        #self.holiday = holidaybuttonapp.Holidaybuttonapp()
        self.freq = 1.0
        return

    def start(self):
        """Do whatever is needed to invoke the app"""
        self.blinkyappthread = Blinkyappthread()
        self.blinkyappthread.setFreq(self.freq)
        self.blinkyappthread.start()
        return

    def stop(self):
        """Stop execution of the app"""
        self.blinkyappthread.terminate = True
        return

    def up(self):
        """Process a press of the up button -- makes things faster"""
        f = self.freq - 0.2
        if (f < 0.2):
            return
        self.freq = f
        self.blinkyappthread.setFreq(self.freq)
        return

    def down(self):
        """Process a press of the down button -- makes things slower"""
        f = self.freq + 0.2
        if (f > 15):
            return
        self.freq = f
        self.blinkyappthread.setFreq(self.freq)
        return

# Here's a thread that handles the blink-making while other things go on.
#
class Blinkyappthread(threading.Thread):

    def run(self):
        """Gonna make some pretty pretty colours here"""
        self.terminate = False
        self.holiday = holidaybuttonapp.Holidaybuttonapp()
        while True:
            if self.terminate:
                return
            ln = 0
            while (ln < self.holiday.NUM_GLOBES):
                r = random.randint(0, 255)
                g = random.randint(0, 255)
                b = random.randint(0, 255)
                # Now based on another random value, squash one of these values
                cn = random.randint(0,2)
                if (cn == 0):
                    r = 0
                elif (cn == 1):
                    g = 0
                else:
                    b = 0
                self.holiday.setglobe(ln, r, g, b)
                ln = ln+1            
            #print "blink"
            self.holiday.render()       # Send the colours out
            time.sleep(self.freq)       # And finally, wait.

    def setFreq(self, freq):
        self.freq = freq
        return

    def randcv(self):
        """Return a random colour value"""

# ZOMFG LET'S DO SOME TESTING
#
if __name__ == '__main__':
    app = Blinkyapp()
    app.start()
    app.up()
    app.up()
    time.sleep(5)
    app.stop()
