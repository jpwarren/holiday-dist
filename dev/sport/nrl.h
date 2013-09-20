// Here's where we keep team-specific data
// Inside of a nice array.
//
// Now -- fun with data structures
struct pixel { 
	unsigned char r; 
	unsigned char g; 
	unsigned char b; 
};

// Convenience definitions
#define WHITE { 0xFF, 0xFF, 0xFF }
#define BLACK { 0x00, 0x00, 0x00 }

// Defines for various team colours
#include "nrld/rabbitohs.h"
#include "nrld/eels.h"
#include "nrld/roosters.h"
#include "nrld/seaeagles.h"
#include "nrld/bulldogs.h"
#include "nrld/broncos.h"
#include "nrld/warriors.h"
#include "nrld/panthers.h"
#include "nrld/storm.h"
#include "nrld/raiders.h"
#include "nrld/sharks.h"
#include "nrld/dragons.h"
#include "nrld/tigers.h"
#include "nrld/knights.h"
#include "nrld/titans.h"
#include "nrld/cowboys.h"


// An array of teams
void *teams[16] = {
	&rabbitohs,
	&eels,
	&roosters,
	&seaeagles,
	&bulldogs,
	&broncos,
	&warriors,
	&panthers,
	&storm,
	&sharks,
	&raiders,
	&dragons,
	&tigers,
	&knights,
	&titans,
	&cowboys
};
