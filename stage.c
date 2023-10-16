#include "stage.h"

/**************** file-local global variables ****************/
App* app;
Stage* stage;
Entity* player;
SDL_Texture* bulletTexture;

/**************** local functions ****************/
static void initPlayer();
static void logic(void);
static void draw(void);
static void doPlayer(void);
static void fireBullet(void);
static void doBullets(void);
static void drawPlayer(void);
static void drawBullets(void);

void initStage(App* app_param)
{
    app = app_param;

    Entity* fhead;
    Entity* bhead;

	app->delegate.logic = *logic;
	app->delegate.draw = *draw;

    stage = malloc(sizeof(Stage));
    memset(stage, 0, sizeof(Stage));

    fhead = &stage->fighterHead;
    bhead = &stage->bulletHead;
	stage->fighterTail = fhead;
	stage->bulletTail = bhead; 

	initPlayer();

	bulletTexture = loadTexture(BULLET_IMAGE, app);

    // return stage, player;
}

static void initPlayer()
{
    player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage->fighterTail->next = player;
	stage->fighterTail = player;

	player->x = PLAYER_X_START;
	player->y = PLAYER_Y_START;
	player->texture = loadTexture(PLAYER_IMAGE, app);
    int p_width = PLAYER_WIDTH;
    int p_height = PLAYER_HEIGHT;
	SDL_QueryTexture(player->texture, NULL, NULL, &p_width, &p_height);

    // return player;
}

static void logic(void)
{
    printf("logic\n");
	doPlayer();

	doBullets();
}

static void doPlayer(void)
{
	player->dx = player->dy = 0;

	if (player->reload > 0)
	{
		player->reload--;
	}

	if (app->keyboard[SDL_SCANCODE_UP])
	{
		player->dy = -PLAYER_SPEED;
	}

	if (app->keyboard[SDL_SCANCODE_DOWN])
	{
		player->dy = PLAYER_SPEED;
	}

	if (app->keyboard[SDL_SCANCODE_LEFT])
	{
		player->dx = -PLAYER_SPEED;
	}

	if (app->keyboard[SDL_SCANCODE_RIGHT])
	{
		player->dx = PLAYER_SPEED;
	}

	if (app->keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0)
	{
		fireBullet();
	}

	player->x += player->dx;
	player->y += player->dy;
}

static void fireBullet(void)
{
	Entity *bullet;

	bullet = malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));
	stage->bulletTail->next = bullet;
	stage->bulletTail = bullet;

	bullet->x = player->x;
	bullet->y = player->y;
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = bulletTexture;
    
    int b_width = BULLET_WIDTH;
    int b_height = BULLET_HEIGHT;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &b_width, &b_height);

	bullet->y += (player->h / 2) - (bullet->h / 2);

	player->reload = 8;
}

static void doBullets(void)
{
	Entity *b, *prev;

	prev = &stage->bulletHead;

	for (b = stage->bulletHead.next ; b != NULL ; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;

		if (b->x > SCREEN_WIDTH)
		{
			if (b == stage->bulletTail)
			{
				stage->bulletTail = prev;
			}

			prev->next = b->next;
			free(b);
			b = prev;
		}

		prev = b;
	}
}

static void draw(void)
{
    printf("draw\n");
	drawPlayer();

	drawBullets();
}

static void drawPlayer(void)
{
	blit(player->texture, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT, app);
}

static void drawBullets(void)
{
	Entity *b;

	for (b = stage->bulletHead.next ; b != NULL ; b = b->next)
	{
		blit(b->texture, b->x, b->y, BULLET_WIDTH, BULLET_HEIGHT, app);
	}
}