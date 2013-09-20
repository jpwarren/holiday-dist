// This part is specific to the procedural animation.
#define NUM_TEAMS 18			// 16 teams
#include "afl.h"

#define CHANGE_AT 50			// Every 5 seconds
int team_counter;
int change_counter;


// Here's where we set it up
// Read in a value off the command line if any
// If none, we go to black
// If value (1 - 18), we display the appropriate team colours
//
void setup(int argc, char *argv[]) {
int tval;
int i;
struct pixel *team;

	if (argc < 2) {
		// No value. Make the string black
		for (i = 0; i < NUM_GLOBES; i++) {
			//set_pixel(i, cowboys[i].r, cowboys[i].g, cowboys[i].b);
			set_pixel(i, 0, 0, 0);
		}		
	} else {
		tval = atoi(argv[1]);	// Convert value to integer
		if ((tval > 0) && (tval <= NUM_TEAMS)) {
			team = teams[tval-1]; 
			for (i = 0; i < NUM_GLOBES; i++) {
				set_pixel(i, team[i].r, team[i].g, team[i].b);
			}			
		} else {
			//Illegal value, do nothing
			tval = -1;
		}
	}

	team_counter = 0;
	change_counter = CHANGE_AT;
	return;
}

// And we try to call this fairly often - every 20 milliseconds or thereabouts
//
int loop() {
int i;
struct pixel *team;

	/*if (++change_counter < CHANGE_AT) 
		return;
	change_counter = 0;

	team = teams[team_counter];		// Get a team
	// Walk through the pattern and put it out to the string
	for (i = 0; i < NUM_GLOBES; i++) {
		set_pixel(i, team[i].r, team[i].g, team[i].b);
	}

	if (++team_counter == NUM_TEAMS) {
		team_counter = 0;
	}*/

	return 0;
}
