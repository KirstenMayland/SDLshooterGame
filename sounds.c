#include "sounds.h"

Mix_Chunk* sounds[SND_MAX];
Mix_Music* music;

void initSounds(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);

	music = NULL;

	loadSounds();
}

static void loadSounds(void)
{
	sounds[SND_PLAYER_FIRE] = Mix_LoadWAV("audio/player_throw.wav");
	sounds[SND_ENEMY_FIRE] = Mix_LoadWAV("sound/196914__dpoggioli__laser-gun.ogg");
	sounds[SND_PLAYER_DIE] = Mix_LoadWAV("sound/245372__quaker540__hq-explosion.ogg");
	sounds[SND_ENEMY_DIE] = Mix_LoadWAV("audio/enemy_death.wav");
}

Mix_Music* loadMusic(char *filename)
{
	// Mix_Music* m;
	// if (m != NULL)
	// {
	// 	Mix_HaltMusic();
	// 	Mix_FreeMusic(m);
	// 	m = NULL;
	// }

	return Mix_LoadMUS(filename);
	
}

void playMusic(Mix_Music* music, int loop)
{
	//Mix_PlayMusic(music, (loop) ? -1 : 0);
	if (music == NULL) {
		printf("null2\n");
	}
	int error = Mix_FadeInMusicPos(music, loop, 0.1, 0.0);
	if (error == -1) {
		printf("error\n");
	}
	
	printf("%s\n", Mix_GetError());
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}