#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "errors.h"


size_t loadrom(char *filename);


int writes = 0;

SDL_Surface pix;

struct {
	byte mem[MEM_SIZE];
} machine;


Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

Uint32 colors[16];

inline void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}





int main(int argc, char **argv)
{
	int count = 0;
	int i = 0;
	done = FALSE;

	if ( SDL_Init(SDL_INIT_VIDEO) < 0) {
		exit(ERR_SDLVIDEO);
	}
	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(SCREENW, SCREENH, 32, SDL_HWSURFACE
		|SDL_ANYFORMAT|SDL_DOUBLEBUF);//|SDL_FULLSCREEN|SDL_DOUBLEBUF);

	if ( !screen ) {
		exit(ERR_SDLSURFACE);
	}
	
	if ( argc > 2 )
	{
		cpu.verbose = 1;
	}
	else
		cpu.verbose = 0;
	
	if ( argc < 2 )
	{
		printf("Error: please specify a rom\n");
		exit(1);
	}
	
	loadrom(argv[1]);
	
	cpu_init();
	
	
	#include "colors.h"
	
	printf("starting...\n-----------------------------------------\n");
	
	cpu.running=1;
	
	while (done != TRUE)
	{
		
		for ( i = 0; i < 50; i++ )
			cpu_step();
		SDL_Delay(time_left());
		next_time += TICK_INTERVAL;

		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT: 
					done = TRUE;
					break;
				case SDL_MOUSEBUTTONDOWN:
					done = TRUE;
					break;
			}
		}
	}
	return 0;
}

/* loads a program from a file
 */
size_t loadrom(char *filename)
{
	int bytes = 0; 
	FILE *romfile = fopen(filename, "rb");
	if ( romfile != NULL ) {
		bytes = fread((void*)(machine.mem + MEM_SIZE-ROM_SIZE), 
			1, ROM_SIZE, romfile);
		fclose(romfile);
		printf("rom loaded. %d bytes\n", bytes);
	}
	else 
		exit(ERR_LOADROM);
	
	return bytes;
}

/* read from internal memory
 */
inline int readmem(unsigned short int loc)
{
	
	if ( loc == 0xFE )
	{
		unsigned char s = rand()%255;
		machine.mem[0xFE] = s;
		return s;
	}

		return machine.mem[loc];

}

/* write to internal memory
 */
inline void writemem(unsigned short int loc, unsigned char val)
{
	int j;
	machine.mem[loc] = val;

	if ( loc >= 0x200 && loc <= 0x5ff )
	{
		int temp = (loc - 0x200) % GRIDSIZE, temp2 = loc - 0x200;
		if ( val > 0x10 )
			return;
		for (j = 0; j<TILESIZE*TILESIZE; j+=2) { 
			putpixel(screen, (j%TILESIZE)+temp*TILESIZE , 
				(j-j%TILESIZE)/TILESIZE+(temp2 - temp)
				/GRIDSIZE *TILESIZE , colors[val]);
		}
		
		if ( writes++ > 20 ) {
			SDL_Flip(screen);
			writes = 0;
		}
	}
}
