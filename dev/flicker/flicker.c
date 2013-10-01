// This part is specific to the procedural animation.
#define BASE_BRIGHTNESS 0;		// How bright is the bottom of the range?
#define TOTAL_RANGE 25				// And the difference between minimum and maximum?  
#define CHANGES_PER 3			// How many lights to change per pass through

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

static struct pixel flamecolor = { 0x8F, 0x6F, 0x00 };			// The yellow of the flame

// Here's where we set it up
void setup() {
int i, retval;
struct timespec ts;
unsigned int curr;

	for (i=0; i < NUM_GLOBES; i++) {
		hol.values[i].r = 0x00;
		hol.values[i].g = 0x00;
		hol.values[i].b = 0x00;
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
float redf, greenf, bluef;
uint8_t red, green, blue;
float divisand;

	// For each bulb, generate a random brightness value
	// That brightness value will then be used to set the bulb brightness
	// By multiplying it against the RGB components
	for (i = 0; i < CHANGES_PER; i++) {

		globe_val = rand() % NUM_GLOBES;

		int j = rand();
		j = (j % TOTAL_RANGE) + BASE_BRIGHTNESS;
		divisand = j / 100.0;

		redf = ((float) flamecolor.r) * divisand;
		greenf = ((float) flamecolor.g) * divisand;
		bluef = ((float) flamecolor.b) * divisand;

		set_pixel(globe_val, ((uint8_t) redf), ((uint8_t) greenf), ((uint8_t) bluef));
	}
	

	return;
}
