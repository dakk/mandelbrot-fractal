CFLAGS = -D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL

all:
	gcc -c complex.c -o complex.o
	gcc -c fractal.c -o fractal.o
	gcc -c algorithms.c -o algorithms.o
	gcc -c sdlrender.c -o sdlrender.o $(CFLAGS)
	gcc fractal.o complex.o sdlrender.o algorithms.o -o fractal -lSDL -lSDL_ttf -lpthread

