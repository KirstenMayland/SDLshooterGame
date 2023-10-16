# A simple Makefile for compiling small SDL projects
# Modified from: https://www.geeksforgeeks.org/sdl-library-in-c-c-with-examples/

# set the compiler
CC := clang

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm -g

# add header files here
HDRS := SDL2/SDL.h common.h defs.h structs.h draw.h init.h input.h main.h

# # add source files here
# SRCS := draw.c init.c input.c main.c

# # generate names of object files
# OBJS := $(SRCS:.c=.o)
OBJS := draw.o init.o input.o main.o

draw.o: SDL2/SDL.h structs.h draw.h
init.o: SDL2/SDL.h defs.h structs.h init.h 
input.o: SDL2/SDL.h structs.h input.h
main.o: SDL2/SDL.h main.h init.h

# name of executable
EXEC := shooter

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# # recipe for building object files
# $(OBJS): $(@:.o=.c) $(HDRS) Makefile
# 	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean