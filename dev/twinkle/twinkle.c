// This part is specific to the procedural animation.
#define BASE_BRIGHTNESS 32		// How bright is the background of the range?
#define TOTAL_RANGE 16			// And the difference between minimum and maximum?  
#define CHANGES_PER 1			// How many lights to change per pass through

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

static struct pixel flamecolor = { 0x00, 0x00, 0xFF };			// The blue of the sky

// Here's where we set it up
void setup() {
int i, retval;
struct timespec ts;
unsigned int curr;

	for (i=0; i < NUM_GLOBES; i++) {
		hol.values[i].r = flamecolor.r;
		hol.values[i].g = flamecolor.g;
		hol.values[i].b = flamecolor.b;
	}

	// And seed the random number generator with the current time
	retval = clock_gettime(CLOCK_REALTIME, &ts);
	curr = ts.tv_nsec / 1000000;	// Convert to msec
	curr = (ts.tv_sec * 1000) + curr;
	srand(curr);
	return;
}

// And we try to call this fairly often - every 20 milliseconds or thereabouts
//
void loop() {
int i, j, globe_val;
uint8_t blue;
long delta;

	// For each bulb, generate a random brightness value
	// That brightness value will then be used to set the bulb brightness
	// By multiplying it against the RGB components
	for (i = 0; i < CHANGES_PER; i++) {

		globe_val = rand() % NUM_GLOBES;

		j = rand();
		delta = j % TOTAL_RANGE;
		if (j > (RAND_MAX / 2)) {
			//printf("%02x %02x\n", BASE_BRIGHTNESS, delta);
			blue = BASE_BRIGHTNESS - ((uint8_t) delta);
		} else {
			blue = BASE_BRIGHTNESS + ((uint8_t) delta);
		}
		//printf("%d %d %02x\n", j, delta, blue);
		set_pixel(globe_val, 0, 0, blue);
	}
	return;
}
