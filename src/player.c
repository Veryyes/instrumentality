#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "util.h"
#include "surface_hashmap.h"
#include "map.h"
#include "player.h"

extern SDL_Surface* screen;
extern SurfaceHashMap* surface_hashmap;
extern Map* map;
extern int Gravity;

Player* load_player()
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
	player->sprite = get_surface("./res/miro/idle_R.png", surface_hashmap);
	//load_surface("./res/miro/idle_R.png", screen);	

	SDL_Rect* pos = malloc(sizeof(SDL_Rect));
	if(pos == NULL)
	{
		printf("Unable to malloc memory for player position!\n");
		exit(1);
	}
	pos->x = 64;
	pos->y = 32;
	player->pos = pos;

	player->xVel = 0;
	player->yVel = 0;
	player->xAccel = 0;
	player->yAccel = 0;

	player->state = 0;

	return player;
}

void update_player(Player* player, Uint8* keystates)
{
	player->state &= ~15;
//	player->yVel=0;
	//Key Strokes
	if(keystates[SDL_SCANCODE_LEFT])
	{
		player->state |= 1 << LEFT;
	}
	if(keystates[SDL_SCANCODE_RIGHT])
	{
		player->state |= 1 << RIGHT;
	}
	if(keystates[SDL_SCANCODE_UP])
	{
		player->state |= 1 << UP;	
	}
	if(keystates[SDL_SCANCODE_DOWN])
	{
		player->state |= 1 << DOWN;
	}
	player->xVel = (-4 * (((player->state)>>LEFT)&1)) + (4 * (((player->state)>>RIGHT)&1));


	Wall* below;
	int nextX = player->pos->x + player->xVel;
	int nextY = player->pos->y + player->yVel;
	
	if(nextX + (int)(.5*player->pos->w) > -1 && nextX + (int)(.5*player->pos->w) < SCREEN_WIDTH && nextY + player->pos->h && nextY + player->pos->h < SCREEN_HEIGHT)
	{	
		below = (Wall*)quadtree_search(map->wall_tree, nextX + (int)(.5*player->pos->w),nextY + player->pos->h);
		if(below==NULL)
			player->state |= (1<<FALLING);
		else
			player->state &= ~(1<<FALLING);
		below = NULL;
		int count = 0;
		while(below == NULL && nextY+player->pos->h+count*32 < SCREEN_HEIGHT){
			printf("Looking for a wall %d\n", count);
			printf("\t\n");
			
			below = (Wall*)quadtree_search(map->wall_tree, nextX + (int)(.5*player->pos->w), nextY + player->pos->h + 32*count);
			count++;
			if(below!=NULL){
				printf("%d, %d, %d, %d\n",below->pos->x,below->pos->y,below->pos->w,below->pos->h);
				SDL_FillRect(screen,below->pos,0);
			}
			usleep(100000);
		}
		if(below == NULL)
			printf("Player off Screen\n");
		else if(nextY > below->pos->y)
		{
			
			player->state &= ~(1<<FALLING);
			player->pos->y = below->pos->y;
		}
	}

	if(player->state&(1<<FALLING))//if airborne
	{
		player->yAccel = Gravity;
	}else
	{
		player->yAccel = 0;
		player->yVel = 0;
	}
//	printf("State: %d\n",player->state);
	//Physics
	
	player->pos->x += player->xVel;
	player->pos->y += player->yVel;
	player->xVel += player->xAccel;
	player->yVel += player->yAccel;

//	printf("Player(<%d,%d>,<%d,%d>,<%d,%d>)\n",player->pos->x,player->pos->y,player->xVel,player->yVel,player->xAccel,player->yAccel);
}

void blit_player(Player* player)
{
	SDL_BlitSurface(player->sprite, NULL, screen, player->pos);
}

void free_player(Player* player)
{	
	player->sprite = NULL;

	free(player->pos);
	player->pos = NULL;

	free(player);
}
