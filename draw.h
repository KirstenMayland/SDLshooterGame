#include "common.h"

/*prepareScene*/
void prepareScene(App* app);

/*presentScene*/
void presentScene(App* app);

SDL_Texture *loadTexture(char *filename, App* app);

void blit(SDL_Texture *texture, int x, int y, int w, int h, App* app);