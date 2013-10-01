uint8_t start_r, start_g, start_b, stop_r, stop_g, stop_b;
long steps, count;
float step_r, step_g, step_b;

void setup(int argc, char *argv[]) {
long startclr, stopclr;

	// let's see if we have the required parameters
	if (argc != 4) {
		printf("Usage gradience <start color> <end color> <frames>\n");
		exit(-6);
	}
	
	// Get the arguments
	startclr = strtol(argv[1], NULL, 16);
	stopclr	= strtol(argv[2], NULL, 16);
	steps = atol(argv[3]);
	if ((startclr == 0) || (stopclr == 0) || (steps == 0)) {
		printf("Illegal parameter.\n");
		exit(-7);
	}
	printf("%x %x %d\n", startclr, stopclr, steps);	
	
	start_g = (startclr & 0x7f0000) >> 16;
	start_r = (startclr & 0x7f00) >> 8;
	start_b = startclr & 0x7f;
	
	stop_g = (stopclr & 0x7f0000) >> 16;
	stop_r = (stopclr & 0x7f00) >> 8;
	stop_b = stopclr & 0x7f;

	step_r = ((float) (stop_r - start_r) / steps);
	step_g = ((float) (stop_g - start_g) / steps);
	step_b = ((float) (stop_b - start_b) / steps);
	
	count = 0;
	
}
	
int loop(long since) {
float cur_r, cur_g, cur_b;
int col, row; 
uint8_t r, g, b;
	
	cur_r = ((float) start_r + (step_r * count));
	cur_g = ((float) start_g + (step_g * count));
	cur_b = ((float) start_b + (step_b * count));
	for (col = 0; col < lamp_cols; col++) {
		for (row = 0; row < lamp_rows; row++) {
				r = ((uint8_t) cur_r);
				g = ((uint8_t) cur_g);
				b = ((uint8_t) cur_b);
				//printf("%x ", lastval);
				set_pixel(row, col, r, g, b);
		}
	}

	if (count < steps) {
		count++;
		return 0;
	} else {
		return 1;
	}
}