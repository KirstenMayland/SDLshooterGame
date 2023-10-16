#include <SDL2/SDL.h>
#include "defs.h"

#pragma once
typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

#pragma once
typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
} App;


#pragma once
typedef struct Entity{
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int health;
	int reload;
	int side;
	SDL_Texture *texture;
	struct Entity *next;
} Entity;

#pragma once
typedef struct {
	Entity fighterHead, *fighterTail;
	Entity bulletHead, *bulletTail;
} Stage;