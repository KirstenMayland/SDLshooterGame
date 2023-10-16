#include "draw.h"

void prepareScene(App* app)
{
	printf("prepare\n");
	SDL_SetRenderDrawColor(app->renderer, 255, 230, 167, 255);
	SDL_RenderClear(app->renderer);
}

void presentScene(App* app)
{
	SDL_RenderPresent(app->renderer);
}

SDL_Texture *loadTexture(char *filename, App* app)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app->renderer, filename);

	return texture;
}

void blit(SDL_Texture *texture, int x, int y, int w, int h, App* app)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;

	// Automatic determining width and height of texture
	// if (w == NULL || h == NULL) {
	// 	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	// }
	// else { // Manual
		// dest.w = w;
		// dest.h = h;
	// }

	dest.w = w;
	dest.h = h;

	SDL_RenderCopy(app->renderer, texture, NULL, &dest);
}