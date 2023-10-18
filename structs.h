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

typedef struct Explosion {
	float x;
	float y;
	float dx;
	float dy;
	int r, g, b, a;
	struct Explosion *next;
} Explosion;

typedef struct Debris {
	float x;
	float y;
	float dx;
	float dy;
	SDL_Rect rect;
	SDL_Texture *texture;
	int life;
	struct Debris *next;
} Debris;

typedef struct {
	int x;
	int y;
	int speed;
} Leaf;

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
	Explosion explosionHead, *explosionTail;
	Debris debrisHead, *debrisTail;
} Stage;