#include "main.h"

//TODO: 
// include wasd
// increase directions bullets can be shot from
// have acorns be shot from the bear's paws
// free stage and enemies
// prevent bear from leaving screen

// enemies move on y axis? (prevent them from leaving top and bottom of screen)
// change spawn rate

/**************** file-local global variables ****************/
App* app;
Stage* stage;

/**************** local functions ****************/
void cleanup(void);
static void capFrameRate(long *then, float *remainder);

int main(int argc, char *argv[])
{
	long then;
	float remainder;

	// TODO: app malloc
	app = malloc(sizeof(App));
	memset(app, 0, sizeof(App));

	initSDL(app);

	atexit(cleanup);

	initStage(app);

	then = SDL_GetTicks();

	remainder = 0;

	SDL_Texture* background = loadTexture(BACKGROUND_IMAGE, app);
	playMusic(loadMusic(BACKGROUND_MUSIC), -1);

	//initSounds();

	while (1)
	{
		prepareScene(app, background);

		doInput(app);

		app->delegate.logic();

		app->delegate.draw();

		presentScene(app);

		capFrameRate(&then, &remainder);
	}

	return 0;
}

void cleanup(void)
{
	// clean up resources
	
	// if (music != NULL)
	// {
	// 	Mix_HaltMusic();
	// 	Mix_FreeMusic(music);
	// 	music = NULL;
	// }

	// reset stage (frees fighters & bullets)
	cleanupStage(returnStage());
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
	free(app);
    SDL_Quit();
}

static void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}