CC=gcc
INDIR=Resources/include
sdlflgs=$(shell sdl2-config --libs --cflags)
CFLAGS=-lm -I$(INDIR) $(sdlflgs)
objects=main.o clamp.o frame.o
bin=Resources/bin

all : $(objects)
	$(CC) $(objects) -o pong $(CFLAGS)

main.o : clamp.o frame.o

.PHONY : clean
.PHONY : tidy

clean : tidy
	-rm pong

tidy :
	-rm $(objects)
