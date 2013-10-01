/*
 * Sing is the Processing-like framework for CloudLight procedural animation
 * After the Processing language by Tom Igoe
 * 
 * For the moment, the user procedural file is simply included
 * And everything is connected together at compile time
 * 
 * The user procedural file should define:
 *
 * void setup(void*)
 * void loop(void*)
 *
 * And leave everything else to this framework. Hopefully.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <time.h>

#define NUM_GLOBES 50

uint8_t* txbuf;			// Global frame buffer


long sync_time = 0;

#include "spi.h"			// SPI code for Pi or Olimex support

void synchronize(long since) {
struct timespec ts;
int retval;
long curr;
int waiting = 1;

	// synchronize will exit at least since nanoseconds after the last time sync exited
	// will try to be as close as possible, given the vagaries of multitasking
	// The first time through, it will exit immediately as it has not been initialized
	// So call synchronize(1) during initialization to set things up appropriately
	//
	while (1) {
		retval = clock_gettime(CLOCK_REALTIME, &ts);
		curr = ts.tv_nsec;
		if (ts.tv_nsec < sync_time) {		// Handle wraps gracefully
			curr += 1000000000;
		}
		//printf("curr %d sync_time %d diff %d\n", curr, sync_time, curr-sync_time);  
		if ((curr - sync_time) >= since) {
			sync_time = ts.tv_nsec;
			return;
		} else {
			usleep(100);		// Sleep for 200 microseconds
		} 			
	}
}

long started = 0;

long since_start(void) {
struct timespec ts;
int retval;
long curr;

	// Return the number of milliseconds since the process began execution
	// First call returns zero, but initializes values
	//
	retval = clock_gettime(CLOCK_REALTIME, &ts);
	curr = ts.tv_nsec / 1000000;	// Convert to msec
	curr = (ts.tv_sec * 1000) + curr;
	if (started == 0) {
		started = curr;
		return 0;
	} 
	return curr - started;
}

// Wrapper function to keep this code consistent
static void send_frame(int fd, uint8_t txbuf[], int buffsize) {
	spi_send(txbuf, buffsize);			
}

void set_pixel(int pixnum, uint8_t r, uint8_t g, uint8_t b) {
	int offset;

#ifdef PREPROTO
	// Make sure everything stays within the appropriate limits
	r = r / 2;
	g = g / 2;
	b = b / 2;
#endif
	
	// Need to check for out-of-bounds here, but meh.
	//printf("col %d row %d offset %d\n", col, row, (*climap + col)[row]);
	// Calculate the offset into the buffer
	offset = pixnum * 3;		// Get the correct offset from the map
#ifdef PROTO
	txbuf[offset] = g;
	txbuf[offset+1] = r;		// GGRRBB
#else
	txbuf[offset] = r;
	txbuf[offset+1] = g;
#endif
	txbuf[offset+2] = b;

}

#include "flicker.c"

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd, ss, sp, j;

#ifdef IMX
	int retuid;
	retuid = setuid(0);     // root me!
    if (retuid == -1) {
        exit(-10);
    }
#endif

	since_start();			// initialize the count of when we started execution
	spi_open();				// Setup SPI
	
	// Read the size of our LED string
	// Use the correct map for the string size
	ss = NUM_GLOBES;
	sp = ss * 3;			// Number of color units in string

	// Allocate space for the frame transmit buffer
	txbuf = malloc(sp + 3);
	txbuf[sp+1] = txbuf[sp+2] = txbuf[sp] = 0x00;		// Last byte always null for end of sequence signalling

	// Ok, we're ready to start, so call the setup
	setup();
	synchronize(1);	// And setup the sync function

	while (1) {
		//memset((void*) txbuf, (int) 0x80, (size_t) sp);  // Clear the string quickly
		loop(since_start());
		synchronize(20000000);					// 50 fps or 20 msec/frame
		send_frame(fd, txbuf, (sp + 1));		// Try to transmit the frame
	}
	free(txbuf);		// Always clean up after yourself!
	spi_close();

	return 0;
}
