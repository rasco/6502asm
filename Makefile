# Makefile for windows
# Compile with MinGW
# (set PATH in your console to mingw's /bin directory)

all:
	gcc -Wall src/*.c -c -IMinGWSDL\include -D_MINGW 
	gcc -o 6502 *.o	-LMinGWSDL\lib -lmingw32 -lSDLmain -lSDL -lSDL_image 

mac:
	echo test2

