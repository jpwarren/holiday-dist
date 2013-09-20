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

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define NUM_GLOBES 50

static void pabort(const char *s)
{
	perror(s);
	abort();
}

static const char *device = "/dev/spidev0.0";
static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 500000;
static uint16_t delay;
uint8_t* txbuf;			// Global frame buffer


long sync_time = 0;

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

static void send_frame(int fd, uint8_t txbuf[], int buffsize)
{
	int ret;
	int j  = 0;
	int offset;
	uint8_t rx[385] = { 0, };
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)txbuf,
		.rx_buf = (unsigned long)rx,
		.len = buffsize,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};
	
	//printf("buffsize %d\n", buffsize);
	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
		pabort("can't send spi message");

}


void set_pixel(int pixnum, uint8_t r, uint8_t g, uint8_t b) {
	int offset;
	
	// Need to check for out-of-bounds here, but meh.
	//printf("col %d row %d offset %d\n", col, row, (*climap + col)[row]);
	// Calculate the offset into the buffer
	offset = pixnum * 3;		// Get the correct offset from the map
	txbuf[offset] = r;
	txbuf[offset+1] = g;
	txbuf[offset+2] = b;

}

#include "rainbow.c"

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd, ss, sp, j;
	
	since_start();			// initialize the count of when we started execution
	
	// Read the size of our LED string
	// Use the correct map for the string size
	ss = NUM_GLOBES;
	sp = ss * 3;			// Number of color units in string

	// Allocate space for the frame transmit buffer
	txbuf = malloc(sp + 3);
	txbuf[sp+1] = txbuf[sp+2] = txbuf[sp] = 0x00;		// Last byte always null for end of sequence signalling

	fd = open(device, O_RDWR);
	if (fd < 0)
		pabort("can't open device");

	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		pabort("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
		pabort("can't get spi mode");

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't get bits per word");

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't get max speed hz");

	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

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
	close(fd);

	return 0;
}
