#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "util.h"
#include "surface_hashmap.h"
#include "player.h"

Player* load_player(SurfaceHashMap* hashmap)
{
	Player* player = malloc(sizeof(Player));
	if(player == NULL)
	{
		printf("Unable to malloc memory for player struct!\n");
		exit(1);
	}
	player->hp = 10;
	player->energy = 10;
	player->lives = 10;
	player->sprite = get_surface("./res/miro/idle_R.png", hashmap);
	//load_surface("./res/miro/idle_R.png", screen);	

	SDL_Rect* pos = malloc(sizeof(SDL_Rect));
	if(pos == NULL)
	{
		printf("Unable to malloc memory for player position!\n");
		exit(1);
	}
	pos->x = 0;
	pos->y = 0;
	player->pos = pos;

	player->xVel = 0;
	player->yVel = 0;

	player->direction = RIGHT;

	return player;
}

void update_player(Player* player, Uint8* keystates)
{
	player->xVel = 0;
	//Key Strokes
	if(keystates[SDL_SCANCODE_LEFT])
	{
		player->xVel = -4;
		player->direction = LEFT;
	}
	if(keystates[SDL_SCANCODE_RIGHT])
	{
		player->xVel = 4;
		player->direction = RIGHT;
	}

	//Physics
	player->pos->x += player->xVel;
	player->pos->y += player->yVel;
}

void free_player(Player* player)
{	
	player->sprite = NULL;

	free(player->pos);
	player->pos = NULL;

	free(player);
}
