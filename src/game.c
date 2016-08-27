#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include "surface_hashmap.h"
#include "util.h"
#include "player.h"
#include "map.h"
#include "game.h"


int init(SDL_Window** window, SDL_Surface** screen, SDL_Renderer** renderer);

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Surface* screen = NULL;
	SDL_Renderer* renderer = NULL;	

	SDL_Event e;	
	Uint8* currentKeyStates=SDL_GetKeyboardState(NULL);

	int running = 0;
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	//Loads of window and screen (graphics stuff)
	running = init(&window, &screen, &renderer); 

	SurfaceHashmap* surface_hashmap = load_SurfaceHashMap(screen);		
	//printmap(surface_hashmap);				
	printf("Images initialized\n");

	//Game Variables
	Player* player = load_player(surface_hashmap);
	Map* map = load_map("test", surface_hashmap);
	
	printf("Game Variables loaded, Running game loop!\n");
	while(running)//Main Loop
	{
		//Events
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
				running=0;
		}
		//Inputs
		currentKeyStates = SDL_GetKeyboardState(NULL);
		if(currentKeyStates[SDL_SCANCODE_UP])
			player->pos->y--;
		if(currentKeyStates[SDL_SCANCODE_DOWN])
			player->pos->y++;

		//Entity Updates
		update_player(player, currentKeyStates);

		//Bliting|Rendering
		SDL_BlitSurface(map->background, NULL, screen, NULL);
		SDL_BlitSurface(player->sprite, NULL, screen, player->pos);
		SDL_UpdateWindowSurface(window);				
	}

	//Free up stuffs on exit
	free_player(player);
	free_map(map);
	free_SurfaceHashMap(surface_hashmap);

	SDL_DestroyRenderer(renderer);
	renderer=NULL;

	SDL_DestroyWindow(window);
	window=NULL;

	IMG_Quit();
	SDL_Quit();
	printf("Game Closing\n");
	return 0;
}

int init(SDL_Window** window, SDL_Surface** screen, SDL_Renderer** renderer)
{
	int running = 1;
	if(SDL_Init(SDL_INIT_VIDEO < 0))
	{
		printf("SDL Error: %s\n", SDL_GetError());
		running=0;
	}
	if( !(IMG_Init(imgFlags) & imgFlags))
	{
		printf( "SDL_image could not be initilized. SDL Image Error: %s\n",IMG_GetError());
		running=0;
	}
	printf("SDL and SDL_IMG initialized\n");
	if(running)
	{
		window* = SDL_CreateWindow("Instrumentality", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window* == NULL)
		{
			printf("Window could not be created. SDL Error: %s\n",SDL_GetError());
			running = 0;
		}else	//GUI Properly Loaded
		{
			renderer* = SDL_CreateRenderer(window*, -1, SDL_RENDERER_ACCELERATED);
			if(renderer*==NULL)
			{
				printf("Renderer could not be created. SDL Error:%s\n", SDL_GetError());
				//running = 0; Developing on a computer that cannot support hardware rendering.... ;_;
			}

			screen* = SDL_GetWindowSurface(window);
			if(SDL_SetSurfaceBlendMode(screen*, SDL_BLENDMODE_BLEND))
				printf("SDL Error: %s\n", SDL_GetError());
			
			printf("Window and Screen initialized\n");
		}
	}
	return running;
}
