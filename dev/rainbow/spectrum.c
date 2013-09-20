// This part is specific to the procedural animation.

// Now -- fun with data structures
struct pixel { 
	unsigned char r; 
	unsigned char g; 
	unsigned char b; 
};
struct globes { 
	struct pixel values[NUM_GLOBES]; 
};
struct globes hol;
int color_state, gr, gg, gb;

// Here's where we set it up
void setup() {
int i;

	for (i=0; i < NUM_GLOBES; i++) {
		hol.values[i].r = hol.values[i].g = hol.values[i].b = 0;
	}
	color_state = gr = gr = gb = 0;
	return;
}

// And we try to call this fairly often - every 20 milliseconds or thereabouts
//
void loop() {
int i;

	// Operate the state machine
	switch (color_state) {
		case 0:
		default:
			gr++;
			if (gr == 0xFF) {
				color_state++;
			}
			break;
		case 1:
			gg++;
			if (gg == 0xFF) {
				color_state++;
			}
			break;
		case 2:
			gr--;
			if (gr == 0x00) {
				color_state++;
			}
			break;
		case 3:
			gb++;
			if (gb == 0xFF) {
				color_state++;
			}
			break;
		case 4:
			gg--;
			if (gg == 0x00) {
				color_state++;
			}
			break;
		case 5:
			gr++;
			if (gr == 0xFF) {
				color_state++;
			}
			break;
		case 6:
			gb--;
			if (gb == 0x00) {
				color_state = 1;
			}
			break;
	}


	// Take the structure and write it out.
	for (i = 0; i < NUM_GLOBES; i++) {
		set_pixel(i, gr, gg, gb);
	}
	return;
}
