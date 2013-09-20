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
#define RED { 0xFF, 0x00, 0x00 }
#define YELLOW { 0xFF, 0xFF, 0x00 }
#define GREEN { 0x00, 0xFF, 0x00 }
#define CYAN { 0x00, 0xFF, 0xFF }
#define BLUE { 0x00, 0x00, 0xFF }
#define PURPLE { 0xFF, 0x00, 0xFF }

// Defines for various team colours
#include "afld/blues.h"
#include "afld/magpies.h"
#include "afld/bombers.h"
#include "afld/hawks.h"
#include "afld/crows.h"
#include "afld/cats.h"
#include "afld/swans.h"
#include "afld/giants.h"
#include "afld/kangaroos.h"
#include "afld/saints.h"
#include "afld/lions.h"
#include "afld/eagles.h"
#include "afld/suns.h"
#include "afld/bulldogs.h"
#include "afld/tigers.h"
#include "afld/dockers.h"
#include "afld/power.h"
#include "afld/demons.h"


// An array of teams
void *teams[NUM_TEAMS] = {
	&swans,
	&blues,
	&magpies,
	&bombers,
	&hawks,
	&crows,
	&cats,
	&giants,
	&kangaroos,
	&saints,
	&lions,
	&eagles,
	&suns,
	&bulldogs,
	&tigers,
	&dockers,
	&power,
	&demons
};
