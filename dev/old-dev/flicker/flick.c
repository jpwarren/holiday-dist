/*

Test output some Perlin noise to the LED string. Maybe.

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
#include <linux/spi/spidev.h>
#include <time.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define NUM_BULBS 50

static void pabort(const char *s)
{
  perror(s);
  abort();
}

static const char *device = "/dev/spidev0.0";
static uint32_t speed = 500000;
static uint8_t mode;
static uint16_t delay;

static uint8_t bits = 8;
uint8_t* txbuf;     // Global frame buffer
int string_size = 0;
#define MAX_LEDS NUM_BULBS

// Perlin noise global variables:
//float x1,y1,x2,y2;
float pval[MAX_LEDS][4];

// Set up Perlin globals:
//persistence affects the degree to which the "finer" noise is seen
float persistence = 0.1;
//octaves are the number of "layers" of noise that get computed
int octaves = 3;
// Simplex noise global variables:
int i, j, k, A[] = {0, 0, 0};
float u, v, w, s;
static float onethird = 0.333333333;
static float onesixth = 0.166666667;
int T[] = {0x15, 0x38, 0x32, 0x2c, 0x0d, 0x13, 0x07, 0x2a};

int SDI = 2; //Red wire (not the red 5V wire!)
int CKI = 3; //Green wire

#define STRIP_LENGTH 50
long strip_colors[STRIP_LENGTH];

void setup()
{
int x;

  //Serial.begin(9600);
  //pinMode(SDI, OUTPUT);
  //pinMode(CKI, OUTPUT);
  //pinMode(ledPin, OUTPUT);

  //persistence affects the degree to which the "finer" noise is seen
  persistence = 0.25;
  //octaves are the number of "layers" of noise that get computed
  octaves = 3;

  //Clear out the LED array
  for(x = 0 ; x < NUM_BULBS ; x++)
    set_pixel(x, 0x00, 0x00, 0x00);   // Clear string  
  }
}

/*unsigned long randClr() {
  unsigned long rand_r = random(0, 24);
  byte rand_g = random(0, 24);
  byte rand_b = random(0, 24);
  switch (random(0,3)) {
     case 0:
       rand_r = 0;
       break;
     case 1:
       rand_g = 0;
       break;
     case 2:
     default:
       rand_b = 0;
  }
  unsigned long retval = (rand_r << 16) + (rand_g << 8) + rand_b;
  return retval;
}*/

void loop()
{   
long m;
int n;
int i;

  for (i=0; i < MAX_LEDS; i++) {
    //pval[i][0] = float(millis())/100.0f;
    pval[i][0] = rand();
    pval[i][1] = 10.0f;
    //pval[i][2] = float(millis())/100.0f;
    pval[i][2] = rand();
    pval[i][3] = 11.0f;
  
    //PerlinNoise2 results in a float between -1 and 1
    //below we convert to a n int between 0 and 255
    //float mf = PerlinNoise2(x1,y1,persistence,octaves);
    m = PerlinNoise2(pval[i][0],pval[i][1],persistence,octaves)*128+128;  
    n = PerlinNoise2(pval[i][2],pval[i][3],persistence,octaves)*128+128;
    n = n >> 2;
    //float nf = PerlinNoise2(x2,y2,persistence,octaves);
    strip_colors[i] = (m << 16) + (n << 8);
    //strip_colors[1] = n & 0xFF00;

  }
  send_frame();
  //delay(25);
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
  usleep(500);      // Necessary pause to latch data
}


//Takes the current strip color array and pushes it out
/*void post_frame (void) {
  //Each LED requires 24 bits of data
  //MSB: R7, R6, R5..., G7, G6..., B7, B6... B0 
  //Once the 24 bits have been delivered, the IC immediately relays these bits to its neighbor
  //Pulling the clock low for 500us or more causes the IC to post the data.

  for(int LED_number = 0 ; LED_number < STRIP_LENGTH ; LED_number++) {
    long this_led_color = strip_colors[LED_number]; //24 bits of color data

    for(byte color_bit = 23 ; color_bit != 255 ; color_bit--) {
      //Feed color bit 23 first (red data MSB)

      digitalWrite(CKI, LOW); //Only change data when clock is low

      long mask = 1L << color_bit;
      //The 1'L' forces the 1 to start as a 32 bit number, otherwise it defaults to 16-bit.

      if(this_led_color & mask) 
        digitalWrite(SDI, HIGH);
      else
        digitalWrite(SDI, LOW);

      digitalWrite(CKI, HIGH); //Data is latched when clock goes high
    }
  }

  //Pull clock low to put strip into reset/post mode
  digitalWrite(CKI, LOW);
  delayMicroseconds(500); //Wait for 500us to go into reset
}*/

/*****************************************************************************/
// Simplex noise code:
// From an original algorythm by Ken Perlin.
// Returns a value in the range of about [-0.347 .. 0.347]
float SimplexNoise(float x, float y, float z) {
  // Skew input space to relative coordinate in simplex cell
  s = (x + y + z) * onethird;
  i = pn_fastfloor(x+s);
  j = pn_fastfloor(y+s);
  k = pn_fastfloor(z+s);
   
  // Unskew cell origin back to (x, y , z) space
  s = (i + j + k) * onesixth;
  u = x - i + s;
  v = y - j + s;
  w = z - k + s;;
   
  A[0] = A[1] = A[2] = 0;
   
  // For 3D case, the simplex shape is a slightly irregular tetrahedron.
  // Determine which simplex we're in
  int hi = u >= w ? u >= v ? 0 : 1 : v >= w ? 1 : 2;
  int lo = u < w ? u < v ? 0 : 1 : v < w ? 1 : 2;
   
  return k_fn(hi) + k_fn(3 - hi - lo) + k_fn(lo) + k_fn(0);
}


int pn_fastfloor(float n) {
  return n > 0 ? (int) n : (int) n - 1;
}


float k_fn(int a) {
  s = (A[0] + A[1] + A[2]) * onesixth;
  float x = u - A[0] + s;
  float y = v - A[1] + s;
  float z = w - A[2] + s;
  float t = 0.6f - x * x - y * y - z * z;
  int h = shuffle(i + A[0], j + A[1], k + A[2]);
  A[a]++;
  if (t < 0) return 0;
  int b5 = h >> 5 & 1;
  int b4 = h >> 4 & 1;
  int b3 = h >> 3 & 1;
  int b2 = h >> 2 & 1;
  int b = h & 3;
  float p = b == 1 ? x : b == 2 ? y : z;
  float q = b == 1 ? y : b == 2 ? z : x;
  float r = b == 1 ? z : b == 2 ? x : y;
  p = b5 == b3 ? -p : p;
  q = b5 == b4 ? -q: q;
  r = b5 != (b4^b3) ? -r : r;
  t *= t;
  return 8 * t * t * (p + (b == 0 ? q + r : b2 == 0 ? q : r));
}


int shuffle(int i, int j, int k) {
  return b(i, j, k, 0) + b(j, k, i, 1) + b(k, i, j, 2) + b(i, j, k, 3) + b(j, k, i, 4) + b(k, i, j, 5) + b(i, j, k, 6) + b(j, k, i, 7);
}


int b(int i, int j, int k, int B) {
  return T[b(i, B) << 2 | b(j, B) << 1 | b(k, B)];
}


int b(int N, int B) {
  return N >> B & 1;
}


/*****************************************************************************/
// Perlin noise code:
// using the algorithm from http://freespace.banned.net/hugo.elias/models/m_perlin.html
// thanks to hugo elias
float Noise2(float x, float y)
{
  long noise;
  noise = x + y * 57;
  noise = (noise << 13) ^ noise;
  return ( 1.0 - ( long(noise * (noise * noise * 15731L + 789221L) + 1376312589L) & 0x7fffffff) / 1073741824.0);
}

float SmoothNoise2(float x, float y)
{
  float corners, sides, center;
  corners = ( Noise2(x-1, y-1)+Noise2(x+1, y-1)+Noise2(x-1, y+1)+Noise2(x+1, y+1) ) / 16;
  sides   = ( Noise2(x-1, y)  +Noise2(x+1, y)  +Noise2(x, y-1)  +Noise2(x, y+1) ) /  8;
  center  =  Noise2(x, y) / 4;
  return (corners + sides + center);
}

float InterpolatedNoise2(float x, float y)
{
  float v1,v2,v3,v4,i1,i2,fractionX,fractionY;
  long longX,longY;

  longX = long(x);
  fractionX = x - longX;

  longY = long(y);
  fractionY = y - longY;

  v1 = SmoothNoise2(longX, longY);
  v2 = SmoothNoise2(longX + 1, longY);
  v3 = SmoothNoise2(longX, longY + 1);
  v4 = SmoothNoise2(longX + 1, longY + 1);

  i1 = Interpolate(v1 , v2 , fractionX);
  i2 = Interpolate(v3 , v4 , fractionX);

  return(Interpolate(i1 , i2 , fractionY));
}

float Interpolate(float a, float b, float x)
{
  //cosine interpolations
  return(CosineInterpolate(a, b, x));
}

float LinearInterpolate(float a, float b, float x)
{
  return(a*(1-x) + b*x);
}

float CosineInterpolate(float a, float b, float x)
{
  float ft = x * 3.1415927;
  float f = (1 - cos(ft)) * .5;

  return(a*(1-f) + b*f);
}

float PerlinNoise2(float x, float y, float persistance, int octaves)
{
  float frequency, amplitude;
  float total = 0.0;

  for (int i = 0; i <= octaves - 1; i++)
  {
    frequency = pow(2,i);
    amplitude = pow(persistence,i);

    total = total + InterpolatedNoise2(x * frequency, y * frequency) * amplitude;
  }
  return(total);
}

int main(argv, argc) {
  setup();
  while (true) {
    loop();
  }
}