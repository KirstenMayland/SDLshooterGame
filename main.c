#include "main.h"

// TODO: 
// include wasd
// increase directions bullets can be shot from
// have acorns be shot from the bear's paws
// fine tune bear where bear can go
// add bullet, death, and startup sounds

// enemies move on y axis? (prevent them from leaving top and bottom of screen)
// change spawn rate

/**************** file-local global variables ****************/
App* app;
Stage* stage;
Mix_Music* music;
SDL_Texture* background;

/**************** local functions ****************/
void cleanup(void);
static void capFrameRate(long *then, float *remainder);

int main(int argc, char *argv[])
{
	long then;
	float remainder;

	app = malloc(sizeof(App));
	memset(app, 0, sizeof(App));

	initSDL(app);
	initStage(app);

	atexit(cleanup);

	then = SDL_GetTicks();
	remainder = 0;

	background = loadTexture(BACKGROUND_IMAGE, app);

	music = loadMusic(BACKGROUND_MUSIC);
	playMusic(music, -1);

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
	// free audio
	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}
	Mix_CloseAudio();
	Mix_Quit();

	// free gameplay
	cleanupStage(returnStage());
	SDL_DestroyTexture(background);
	if (app != NULL) {
		if (app->renderer != NULL){
			SDL_DestroyRenderer(app->renderer);
		}
		if (app->window != NULL){
			SDL_DestroyWindow(app->window);
		}
		free(app);
	}
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