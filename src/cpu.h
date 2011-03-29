#ifndef _WIN32
	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
#else
	#ifndef _MINGW
		#pragma comment(lib, "SDL.lib")
		#pragma comment(lib, "SDLmain.lib")
		#pragma comment(lib, "SDL_image.lib")
	#endif
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#define ROM_SIZE 0xFA00
#define MEM_SIZE 0x10000

#define STACK_BEGIN 0xff

#define TICK_INTERVAL 2

#define SCREENW 512
#define SCREENH 512
#define GRIDSIZE 32
#define TILESIZE 16

#define FALSE 0
#define TRUE 1

typedef unsigned char byte;
typedef unsigned short int word;

struct {
	byte reg_a, reg_x, reg_y;
	word pc;
	byte sp;
	int st_carry, st_zero, st_int, st_dec, st_neg, st_overflow, 
		st_unused, st_brk;
	int verbose;
	int running;
} cpu;


SDL_Surface *screen;
SDL_Event event;

int done;
Uint32 next_time;

void cpu_init();
inline void cpu_step();
inline int readmem(unsigned short int loc);
inline void writemem(unsigned short int loc, unsigned char val);
