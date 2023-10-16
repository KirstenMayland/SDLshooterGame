#include "main.h"

//TODO: include wasd, increase directions bullets can be shot from

App app;
Entity player;
Entity bullet;
void cleanup(void);

int main(int argc, char *argv[])
{
	memset(&app, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));
	memset(&bullet, 0, sizeof(Entity));

	initSDL(&app);

	// load player
	player.texture = loadTexture("images/rocket.jpg", &app);
	player.x = 500;
	player.y = 500;

	// player specs
	int p_width = 50;
	int p_height = 50;
	int p_speed = 4;

	// load bullets
	bullet.texture = loadTexture("images/acorn.png", &app);

	// bullet specs
	int b_width = 20;
	int b_height = 20;
	int b_speed = 10;

	atexit(cleanup);

	while (1)
	{
		prepareScene(&app);

		doInput(&app);

		// move up until you hit the top of the screen
		if (app.up && player.y > 0)
		{
			player.y -= p_speed;
		}

		// move down until you hit the bottom of the screen
		if (app.down && player.y < (SCREEN_HEIGHT - p_height))
		{
			player.y += p_speed;
		}

		// move left until you hit the edge of the screen
		if (app.left && player.x > 0)
		{
			player.x -= p_speed;
		}

		// move right until you hit the edge of the screen
		if (app.right && player.x < (SCREEN_WIDTH - p_width))
		{
			player.x += p_speed;
		}

		if (app.fire && bullet.health == 0)
		{
			bullet.x = player.x;
			bullet.y = player.y;
			bullet.dx = b_speed;
			bullet.dy = 0;
			bullet.health = 1;
		}

		bullet.x += bullet.dx;
		bullet.y += bullet.dy;

		// bullet keeps hoing until it hits the end of the screen
		if (bullet.x > SCREEN_WIDTH)
		{
			bullet.health = 0;
		}

		blit(player.texture, player.x, player.y, p_width, p_height, &app);

		// if bullet is alive, show it
		if (bullet.health > 0)
		{
			blit(bullet.texture, bullet.x, bullet.y, b_width, b_height, &app);
		}

		presentScene(&app);

		SDL_Delay(16);
	}

	return 0;
}

void cleanup(void) {
	// clean up resources
	SDL_DestroyTexture(player.texture);
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}