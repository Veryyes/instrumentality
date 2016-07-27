#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Surface* screen = NULL;
	SDL_Event e;	
	
	int running = 1;

	if(SDL_Init(SDL_INIT_VIDEO < 0))
	{
		printf("SDL Error: %s\n", SDL_GetError());
	}else
	{
		window = SDL_CreateWindow("Instrumentality", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if(window==NULL)
		{
			printf("Window could not be created. SDL Error: %s\n",SDL_GetError());
		}else	//GUI Properly Loaded
		{
			screen = SDL_GetWindowSurface(window);
			while(running)
			{
				//Events
				while(SDL_PollEvent(&e) != 0)
				{
					if(e.type == SDL_QUIT)
						running=0;
					else if(e.type == SDL_KEYDOWN)
					{
						switch(e.key.keysym.sym)
						{
							case SDLK_UP:
								printf("up\n");
								break;
							case SDLK_DOWN:
								printf("down\n");
								break;
							case SDLK_LEFT:
								printf("left\n");
								break;
							case SDLK_RIGHT:
								printf("right\n");
								break;
						}
					}
				}
			}		

			/*SDL_Surface* player = loadSurface("./res/miro/idle_R.png",screen);
			SDL_BlitSurface(player, NULL, screen, NULL);
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
			*/
		}
	}
	//Free up stuffs
//	SDL_FreeSurface(player);
//	player=NULL;

	SDL_DestroyWindow(window);
	window=NULL;
	SDL_Quit();
	printf("Game Closing\n");
	return 0;
}

SDL_Surface* loadSurface(char* path, SDL_Surface* screen)
{
	SDL_Surface* optimized = NULL;
	SDL_Surface* loaded = IMG_Load(path);
	
	if(loaded==NULL)
	{
		printf("Unable to load image %s, SDL Image Error:%s\n",path, IMG_GetError());
	}else
	{
		optimized = SDL_ConvertSurface(loaded, screen->format, NULL);
		if(optimized == NULL)
		{

			printf("Unable to optimize image %s, SDL Image Error:%s\n",path, SDL_GetError());
		}
		SDL_FreeSurface(loaded);
	}
	
	return optimized;
}
