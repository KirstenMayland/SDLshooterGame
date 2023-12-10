# A simple Makefile for compiling small SDL projects
# Modified from: https://www.geeksforgeeks.org/sdl-library-in-c-c-with-examples/

# set the compiler
CC := clang
# library
L = SDL2/libSDL2_mixer.a

# compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm -g -I $(L)
# valgrind flags
VFLAGS = --leak-check=full --show-leak-kinds=all


# name of executable
EXEC := shooter
# add header files here
HDRS := SDL2/SDL.h common.h defs.h structs.h util.h draw.h init.h input.h stage.h main.h
# generate object files
OBJS := util.o sounds.o draw.o init.o input.o stage.o main.o

# -------------------------- #

# make all
all: $(EXEC)

# -------------------------- #

util.o: SDL2/SDL.h util.h
sounds.o: SDL2/SDL.h sounds.h
draw.o: SDL2/SDL.h structs.h sounds.h draw.h
init.o: SDL2/SDL.h defs.h sounds.h structs.h init.h 
input.o: SDL2/SDL.h structs.h input.h
stage.o: SDL2/SDL.h util.h sounds.h stage.h
main.o: SDL2/SDL.h init.h sounds.h draw.h input.h stage.h main.h

# -------------------------- #

.PHONY: all clean set

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) 
	$(CC) -o $@ $(OBJS) $(L) $(CFLAGS)

# $(EXEC): $(OBJS) $(HDRS) Makefile

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

valgrind: $(EXEC)
	valgrind $(VFLAGS) --track-origins=yes ./$(EXEC)

set:
	make clean
	make all
