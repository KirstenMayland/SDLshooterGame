#include "stage.h"

/**************** file-local global variables ****************/
App* app;
Stage* stage;
Entity* player;

SDL_Texture* bulletTexture;
SDL_Texture* enemyTexture;
SDL_Texture* enemyBulletTexture;
SDL_Texture* playerTexture;
SDL_Texture* explosionTexture;

int enemySpawnTimer;
int stageResetTimer;

Leaf leaves[MAX_LEAVES];

int leaves_c[3][3] = {{111, 29, 27}, {67, 40, 24}, {153, 88, 42}}; // red brown, rick dark brown, burnt orange

/**************** local functions ****************/
static void resetStage(void);

static void logic(void);
static void initPlayer(void);
static void doPlayer(void);
static void clipPlayer(void);

static void doFighters(void);
static void doEnemies(void);
static void spawnEnemies(void);

static void initLeaves(void);
static void doLeaves(void);

static void doBullets(void);
static void fireBullet(void);
static void fireEnemyBullet(Entity *e);
static int bulletHitFighter(Entity *b);

static void draw(void);
static void drawPlayer(void);
static void drawBullets(void);
static void drawFighters(void);
static void drawLeaves(void);


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
    enemyTexture = loadTexture(ENEMY_IMAGE, app);
    enemyBulletTexture = loadTexture(BULLET_IMAGE, app);
	playerTexture = loadTexture(PLAYER_IMAGE, app);
	explosionTexture = loadTexture(EXPLOSION_IMAGE, app);

	enemySpawnTimer = 0;

    // return stage, player;

	resetStage();
}

static void initPlayer(void)
{
    player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage->fighterTail->next = player;
	stage->fighterTail = player;

	player->x = PLAYER_X_START;
	player->y = PLAYER_Y_START;

	//player->texture = loadTexture(PLAYER_IMAGE, app);
	player->texture = playerTexture;
    player->w = PLAYER_WIDTH;
    player->h = PLAYER_HEIGHT;
	//SDL_QueryTexture(player->texture, NULL, NULL, &p_width, &p_height);

    player->side = SIDE_PLAYER;
	player->health = 1;
    // return player;
}

static void initLeaves(void)
{
	int i;

	for (i = 0 ; i < MAX_LEAVES ; i++)
	{
		leaves[i].x = rand() % SCREEN_WIDTH;
		leaves[i].y = rand() % SCREEN_HEIGHT;
		//leaves[i].speed = 1 + rand() % 8;
		leaves[i].speed = 1;
	}
}

static void resetStage(void)
{
	Entity *e;

	while (stage->fighterHead.next)
	{
		e = stage->fighterHead.next;
		stage->fighterHead.next = e->next;
		free(e);
	}

	while (stage->bulletHead.next)
	{
		e = stage->bulletHead.next;
		stage->bulletHead.next = e->next;
		free(e);
	}

	stage = malloc(sizeof(Stage));
	memset(stage, 0, sizeof(Stage));
	stage->fighterTail = &stage->fighterHead;
	stage->bulletTail = &stage->bulletHead;

	initPlayer();
	initLeaves();

	enemySpawnTimer = 0;

	stageResetTimer = FPS * 2; // used to be times 2
}

static void logic(void)
{
	doLeaves();

	doPlayer();

	doEnemies();

    doFighters();

	doBullets();

    spawnEnemies();

	clipPlayer();

	if (player == NULL && --stageResetTimer <= 0)
	{
		resetStage();
	}

}

static void doPlayer(void)
{
	if (player != NULL && player->health == 0){
		player = NULL;
	}

    if (player != NULL)
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
		if (app->keyboard[SDL_SCANCODE_LCTRL] && player->reload <= 0)
		{
			playSound(SND_PLAYER_FIRE, CH_PLAYER);
		}

        player->x += player->dx;
        player->y += player->dy;
    }
}

static void doEnemies(void)
{
	Entity *e;

	for (e = stage->fighterHead.next ; e != NULL ; e = e->next)
	{
		if (e != player && player != NULL && --e->reload <= 0)
		{
			fireEnemyBullet(e);
			playSound(SND_ENEMY_FIRE, CH_ENEMY_FIRE);
		}
	}
}

static void fireEnemyBullet(Entity *e)
{
	Entity *bullet;

	bullet = malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));
	stage->bulletTail->next = bullet;
	stage->bulletTail = bullet;

	bullet->x = e->x;
	bullet->y = e->y;
	bullet->health = 1;
	bullet->texture = enemyBulletTexture;
	bullet->side = SIDE_ENEMY;

	bullet->w = BULLET_WIDTH; 
	bullet->h = BULLET_HEIGHT;
	//SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	bullet->x += (e->w / 2) - (bullet->w / 2);
	bullet->y += (e->h / 2) - (bullet->h / 2);

	calcSlope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &bullet->dx, &bullet->dy);

	bullet->dx *= ENEMY_BULLET_SPEED;
	bullet->dy *= ENEMY_BULLET_SPEED;

	e->reload = (rand() % FPS * 2);
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
    bullet->side = SIDE_PLAYER;
    
	bullet->texture = bulletTexture;
    bullet->w = BULLET_WIDTH;
    bullet->h = BULLET_HEIGHT;
	//SDL_QueryTexture(bullet->texture, NULL, NULL, &b_width, &b_height);

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

		if (bulletHitFighter(b) || b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT)
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

static int bulletHitFighter(Entity *b)
{
	Entity *e;

	for (e = stage->fighterHead.next ; e != NULL ; e = e->next)
	{
		if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
		{
			b->health = 0;
			e->health = 0;

			if (e == player)
			{
				playSound(SND_PLAYER_DIE, CH_PLAYER);
			}
			else
			{
				playSound(SND_ENEMY_DIE, CH_ANY);
			}

			return 1;
		}
	}

	return 0;
}

static void doFighters(void)
{
	Entity *e, *prev;

	prev = &stage->fighterHead;

	// for every fighter
	for (e = stage->fighterHead.next ; e != NULL ; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;


		// if that fighter is not the player and 
		if (e != player && (e->x < -e->w || e->health == 0))
		{
			if (e == stage->fighterTail)
			{
				stage->fighterTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

static void spawnEnemies(void)
{
	Entity *enemy;

	if (--enemySpawnTimer <= 0)
	{
		enemy = malloc(sizeof(Entity));
		memset(enemy, 0, sizeof(Entity));
		stage->fighterTail->next = enemy;
		stage->fighterTail = enemy;

		enemy->x = SCREEN_WIDTH;
		enemy->y = rand() % SCREEN_HEIGHT;
        enemy->side = SIDE_ENEMY;
        enemy->health = 1;

        enemy->texture = enemyTexture;
		enemy->w = ENEMY_WIDTH;
		enemy->h = ENEMY_HEIGHT;
		//SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

		enemy->dx = -(2 + (rand() % 4));

		enemySpawnTimer = 30 + (rand() % 60);

        enemy->reload = FPS * (1 + (rand() % 3));
	}
}

static void doLeaves(void)
{
	int i;

	for (i = 0 ; i < MAX_LEAVES ; i++)
	{
		leaves[i].x -= leaves[i].speed;

		if (leaves[i].x < 0)
		{
			leaves[i].x = SCREEN_WIDTH + leaves[i].x;
		}
	}
}

static void draw(void)
{
	drawPlayer();

	drawBullets();

    drawFighters();

	drawLeaves();
}

static void drawPlayer(void)
{
    if (player != NULL) 
    {
		blit(player->texture, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT, app);
    }
}

static void drawBullets(void)
{
	Entity *b;

	for (b = stage->bulletHead.next ; b != NULL ; b = b->next)
	{
		blit(b->texture, b->x, b->y, BULLET_WIDTH, BULLET_HEIGHT, app);
	}
}

// as should theroretically be okay
static void drawFighters(void)
{
	Entity *e;

	for (e = stage->fighterHead.next ; e != NULL ; e = e->next)
	{
		if (e != player) {
			blit(e->texture, e->x, e->y, ENEMY_WIDTH, ENEMY_HEIGHT, app);
		}
	}
}

static void drawLeaves(void)
{
	int i, l;

	for (i = 0 ; i < MAX_LEAVES ; i++)
	{
		l = rand() % 3;

		SDL_SetRenderDrawColor(app->renderer, leaves_c[l][0], leaves_c[l][1], leaves_c[l][2], 50);

		SDL_RenderDrawLine(app->renderer, leaves[i].x, leaves[i].y, leaves[i].x + 2, leaves[i].y);
	}
}

static void clipPlayer(void)
{
	if (player != NULL)
	{
		if (player->x < 0)
		{
			player->x = 0;
		}

		if (player->y < 0)
		{
			player->y = 0;
		}

		if (player->x > SCREEN_WIDTH / 2)
		{
			player->x = SCREEN_WIDTH / 2;
		}

		if (player->y > SCREEN_HEIGHT - player->h)
		{
			player->y = SCREEN_HEIGHT - player->h;
		}
	}
}