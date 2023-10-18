#include "common.h"

/*prepareScene*/
void prepareScene(App* app, SDL_Texture* background);

/*presentScene*/
void presentScene(App* app);

SDL_Texture *loadTexture(char *filename, App* app);

void blit(SDL_Texture *texture, int x, int y, int w, int h, App* app);

void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y, App* app);