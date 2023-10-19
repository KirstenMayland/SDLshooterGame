#include "common.h"

void initSounds(void);

static void loadSounds(void);

Mix_Music* loadMusic(char *filename);

void playMusic(Mix_Music* music, int loop);

void playSound(int id, int channel);