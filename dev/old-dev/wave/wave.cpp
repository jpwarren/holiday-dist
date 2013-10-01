// Set up a waving motion using fixed-point trigonometry
#define PI 3.1415926

fix16_t wavey;
int interval = 0;   // Which bulb are we starting with?

void setup(int argc, char *argv[]) {
fix16_t fx;
int x;
float f = PI;

  // Set up the wavey and the interval for the wavey
  // And the number for the wavey
  wavey = fix16_div(fix16_from_float(f), NUM_GLOBES);
  //wavey = fix16_div(wavey, NUM_GLOBES);

  //Clear out the LED array
  for(x = 0 ; x < NUM_GLOBES ; x++) {
    set_pixel(x, 0x00, 0x00, 0x00);   // Clear string  
  }
}
  
int loop(long since) {
int x, valr, valg, valb;
int cnt = 0;
fix16_t cur;

  // OK, so based on the position in the wave, we'll set the color
  // Ranging from zero to PI
  for (x=interval; x < NUM_GLOBES; x++) {
    cur = fix16_mul(wavey,cnt++);
    valr = fix16_to_int(fix16_mul(fix16_tan(cur),fix16_from_int(64)));
    valg = fix16_to_int(fix16_mul(fix16_sin(cur),fix16_from_int(64)));
    valb = fix16_to_int(fix16_mul(fix16_cos(cur),fix16_from_int(64)));
    //printf("%f %f %d \n", fix16_to_float(cur), fix16_to_float(fix16_sin(cur)), val);
    set_pixel(x, valr, valg, valb);

  }
  for (x=0; x < interval; x++) {
    cur = fix16_mul(wavey,cnt++);
    valr = fix16_to_int(fix16_mul(fix16_tan(cur),fix16_from_int(64)));
    valg = fix16_to_int(fix16_mul(fix16_sin(cur),fix16_from_int(64)));
    valb = fix16_to_int(fix16_mul(fix16_cos(cur),fix16_from_int(64)));
    //printf("%f %f %d \n", fix16_to_float(cur), fix16_to_float(fix16_sin(cur)), val);
    set_pixel(x, valr, valg, valb);
  }

  if (++interval == NUM_GLOBES) {
    interval = 0;
  }
  return false;
}
