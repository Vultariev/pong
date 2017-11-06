CC=gcc
INDIR=Resources/include
sdlflgs=$(shell sdl2-config --libs --cflags)
CFLAGS=-lm -I$(INDIR) $(sdlflgs)
objects=main.o clamp.o
bin=Resources/bin
.PHONY : clean
clean :
	-rm pong $(objects)

all : $(objects)
	$(CC) $(objects) -o pong $(CFLAGS)
main.o : clamp.o
