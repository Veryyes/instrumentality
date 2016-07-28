#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <player.h>
#include <util.h>

Player* load_player(SDL_Surface* screen)
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
	player->sprite = load_surface("./res/miro/idle_R.png", screen);
	SDL_Rect* pos = malloc(sizeof(SDL_Rect));
	if(pos == NULL)
	{
		printf("Unable to malloc memory for player position!\n");
		exit(1);
	}
	pos->x = 0;
	pos->y = 0;
	player->pos = pos;
	return player;
}

void free_player(Player* player)
{	
	SDL_FreeSurface(player->sprite);
	player->sprite = NULL;

	free(player->pos);
	player->pos = NULL;

	free(player);
}
