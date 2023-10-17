# A simple Makefile for compiling small SDL projects
# Modified from: https://www.geeksforgeeks.org/sdl-library-in-c-c-with-examples/

# set the compiler
CC := clang

# name of executable
EXEC := shooter
# add header files here
HDRS := SDL2/SDL.h common.h defs.h structs.h util.h draw.h init.h input.h stage.h main.h
# generate object files
OBJS := util.o draw.o init.o input.o stage.o main.o

# compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm -g
# valgrind flags
VFLAGS = --leak-check=full --show-leak-kinds=all

# -------------------------- #

# make all
all: $(EXEC)

# -------------------------- #

util.o: SDL2/SDL.h util.h
draw.o: SDL2/SDL.h structs.h draw.h
init.o: SDL2/SDL.h defs.h structs.h init.h 
input.o: SDL2/SDL.h structs.h input.h
stage.o: SDL2/SDL.h util.h stage.h
main.o: SDL2/SDL.h init.h draw.h input.h stage.h main.h

# -------------------------- #

.PHONY: all clean set

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

valgrind: $(EXEC)
	valgrind $(VFLAGS) ./$(EXEC)

set:
	make clean
	make all
