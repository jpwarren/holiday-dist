/*
 * Read the buttons on the Holiday
 * Do a bit of processing on them,
 * Place the cooked output on /run/pipebuttons.fifo
 * So that other programs can avail themselves of the button functionality
 *
 * This program will eventually be running as a startup daemon
 * So it really shouldn't put anything on stdout unless utterly necessary
 *
 * Mark D. Pesce, May 2013
 * Copyright (c) MooresCloud Pty Ltd, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/types.h>
#include <time.h>
#include <string.h>
#include "gpio-mmap.h"

#define FIFO_ENABLED

#define NUM_BUTTONS 3

// Array definitions
#define MODE 0
#define PLUS 1
#define MINUS 2

// GPIO definitions
#define MODE_BUTTON 1
#define PLUS_BUTTON 2
#define MINUS_BUTTON 3

#define BUTTON_UP 1
#define BUTTON_DOWN 0

#define FALLING 1
#define RISING 2

// Button timing values
#define MIN_DOWN 50000		// 50 msec minimum for debounce
#define POWER_OFF 5000000	// 5 seconds for power off

// Pipe messages
#define POWER_OFF_MSG 'O'
#define PLUS_MSG '+'
#define MINUS_MSG '-'
#define MODE_MSG 'M'

struct tracker {
	struct timeval down;		// timestamp when button pressed
	struct timeval up;			// timestamp when button released
};

struct button {
	int state;					// state of the button
	int the_gpio;				// address of button
	struct tracker times;		// timestamp of button
	long int presstime;			// Downtime in microseconds
	int acted;					// We've acted on the press
};

struct button buttons[3];
FILE* fifo = NULL;

static char* pipename = "/run/pipebuttons.fifo";

// Return the current time in microseconds
unsigned long currtime() {
	struct timeval now;
	unsigned long retval;

	gettimeofday(&now, NULL);		// Get current time
	retval = (now.tv_sec * 1000000) + now.tv_usec;	// Convert to usec
	return retval;
}

// Push a character out the named pipe
unsigned long pipeout(char to_emit) {

#ifdef FIFO_ENABLED
	fprintf(fifo, "%c\n", to_emit);
	fflush(fifo);
#else
	printf("%c\n", to_emit);
#endif
}

// Initialize the GPIO and the data structure for tracking button presses
void init_button(int index, int gpio_num) {

	gpio_input(gpio_num,0);   	// bank 0 bit 1  = GPIO1
	buttons[index].state = BUTTON_UP;	// We assume button not pressed when starting up
	buttons[index].the_gpio = gpio_num;	// We keep this around for when we need it
	buttons[index].acted = 0;			// Haven't acted yet on the press
	return;
}

// Read the button, do interesting things if required.
int read_button(int index) {
	int readval;
	signed long int diff_secs, diff_usecs;

	readval = GPIO_READ_PIN(buttons[index].the_gpio);	// Read the pin
	//printf("readval %d state %d\n", readval, buttons[index].state);
	if (readval != buttons[index].state) {				// Has there been a state change?
		buttons[index].state = readval;					// Record the state change
		if (readval == BUTTON_DOWN) {					// Going down, take a timestamp
			gettimeofday(&buttons[index].times.down, NULL);
			return FALLING;
		} else {
			gettimeofday(&buttons[index].times.up, NULL);	// Coming up, take a timestamp

			// Calculate the number of microseconds of downtime
			diff_secs = buttons[index].times.up.tv_sec - buttons[index].times.down.tv_sec;
			diff_usecs = buttons[index].times.up.tv_usec - buttons[index].times.down.tv_usec;
			buttons[index].presstime = (diff_secs * 1000000) + diff_usecs;
			return RISING;
		}
	}
	return 0;			// return False if not a state change
}

int process_mode() {
	int bstate;
	unsigned long since;

	// Do all the necessary processing for the mode button
	// Which could include, well, we'll just see, won't we?

	// First, read the button
	bstate = read_button(MODE);
	//printf("bstate %d\n", bstate);

	// Now do some sort of state machine thingy
	switch (bstate) {
		case 0:

			// No change, so if the button is down, how long has it been down for?
			if (buttons[MODE].state == BUTTON_DOWN) {
				since = currtime() - ((buttons[MODE].times.down.tv_sec * 1000000) - buttons[MODE].times.down.tv_usec);	// How long down?
				if (since > POWER_OFF) {
					if (buttons[MODE].acted == 0) {
						pipeout(POWER_OFF_MSG);		// Send a message to the pipe
						buttons[MODE].acted = 1;	// We've acted on the button
					}
				}
			}

			break;

		case FALLING:
			// Not sure there's anything to do in this case
			break;

		case RISING:
			// OK, how long has the button been down
			// If longer than POWER_OFF, we ignore it
			// Otherwise, we send a mode button message to the pipe
			if (buttons[MODE].acted == 0) {
				//printf("presstime %d\n", buttons[MODE].presstime);
				if (buttons[MODE].presstime < POWER_OFF) {
					if (buttons[MODE].presstime > MIN_DOWN) {		// Debounce
						pipeout(MODE_MSG);
					}
				} else {
					pipeout(POWER_OFF_MSG);
				}
			} else {
				buttons[MODE].acted = 0;		// Clear the acted flag
			}
			break;
	}
	return 0;
}

int process_plus() {
	int bstate;
	unsigned long since;

	// Do all the necessary processing for the mode button
	// Which could include, well, we'll just see, won't we?

	// First, read the button
	bstate = read_button(PLUS);
	//printf("bstate %d\n", bstate);

	// Now do some sort of state machine thingy
	switch (bstate) {
		case 0:

			// No change, so ignore it for now
			if (buttons[PLUS].state == BUTTON_DOWN) {
				since = currtime() - ((buttons[PLUS].times.down.tv_sec * 1000000) - buttons[PLUS].times.down.tv_usec);	// How long down?
				if (since > MIN_DOWN) {
					if (buttons[PLUS].acted == 0) {
						pipeout(PLUS_MSG);		// Send a message to the pipe
						buttons[PLUS].acted = 1;	// We've acted on the button
					}
				}
			}

			break;

		case FALLING:
			// Not sure there's anything to do in this case
			break;

		case RISING:
			// OK, how long has the button been down
			// If longer than POWER_OFF, we ignore it
			// Otherwise, we send a mode button message to the pipe
			if (buttons[PLUS].acted == 0) {
				//printf("presstime %d\n", buttons[MODE].presstime);
				if (buttons[PLUS].presstime > MIN_DOWN) {		// Debounce
						pipeout(PLUS_MSG);
				}
			} else {
				buttons[PLUS].acted = 0;		// Clear the acted flag
			}
			break;
	}
	return 0;
}

int process_minus() {
	int bstate;
	unsigned long since;

	// Do all the necessary processing for the mode button
	// Which could include, well, we'll just see, won't we?

	// First, read the button
	bstate = read_button(MINUS);
	//printf("bstate %d\n", bstate);

	// Now do some sort of state machine thingy
	switch (bstate) {
		case 0:

			// No change, so ignore it for now
			if (buttons[MINUS].state == BUTTON_DOWN) {
				since = currtime() - ((buttons[MINUS].times.down.tv_sec * 1000000) - buttons[MINUS].times.down.tv_usec);	// How long down?
				if (since > MIN_DOWN) {
					if (buttons[MINUS].acted == 0) {
						pipeout(MINUS_MSG);		// Send a message to the pipe
						buttons[MINUS].acted = 1;	// We've acted on the button
					}
				}
			}

			break;

		case FALLING:
			// Not sure there's anything to do in this case
			break;

		case RISING:
			// OK, how long has the button been down
			// If longer than POWER_OFF, we ignore it
			// Otherwise, we send a mode button message to the pipe
			if (buttons[MINUS].acted == 0) {
				//printf("presstime %d\n", buttons[MODE].presstime);
				if (buttons[MINUS].presstime > MIN_DOWN) {		// Debounce
						pipeout(MINUS_MSG);
				}
			} else {
				buttons[MINUS].acted = 0;		// Clear the acted flag
			}
			break;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int retuid;
	int err;
	int j;

	// Try to get some privleges here
	retuid = setuid(0);		// root me!
	if (retuid == -1) {
		perror("Could not setuid");
		exit(-10);
	}

	gpio_map();

	init_button(MODE, MODE_BUTTON);
	init_button(PLUS, PLUS_BUTTON);
	init_button(MINUS, MINUS_BUTTON);

#ifdef FIFO_ENABLED

	// Create the named pipe, set permissions
	err = mkfifo(pipename, 0666);
	if (err != 0) {
		perror("Could not create pipe");
		exit(-100);
	}
	err = chmod(pipename, 0666);
	if (err != 0) {
		perror("Could not change pipe permissions");
		exit(-101);
	}

	// So here's the interesting bit.  We expect to get passed stuff on our named FIFO pipe.
	// So let's open that puppy up, shall we?
	printf("opening fifo...");
	fflush(NULL);
	fifo = fopen(pipename, "w");
	printf("fifo opened\n");
	fflush(NULL);
#endif

	// Every line should be a value, there should be 50 lines for 50 bulbs
	// Then we will display the lot.
	// We block while we're waiting for values.  As you do.
	while (1) {		// We are going to do this forever and ever and ever and ever etc

		// Walk through and read the buttons
		process_mode();
		process_plus();
		process_minus();

		//printf("%1X%1X%1X:\n", read_button(MODE_BUTTON), read_button(PLUS_BUTTON), read_button(MINUS_BUTTON));
		usleep(10000);		// 100 hz read rate
	}

	//fclose(fifo);

	return 0;
}
