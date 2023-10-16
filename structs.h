#include <SDL2/SDL.h>

#pragma once
typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

#pragma once
typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	int up;
	int down;
	int left;
	int right;
	int fire;
} App;

#pragma once
typedef struct {
	int x;
	int y;
	int dx;
	int dy;
	int health;
	SDL_Texture *texture;
} Entity;