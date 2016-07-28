#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Surface* screen = NULL;

	SDL_Event e;	
	Uint8* currentKeyStates=SDL_GetKeyboardState(NULL);

	int running = 1;
	int imgFlags = IMG_INIT_PNG;	

	if(SDL_Init(SDL_INIT_VIDEO < 0))
	{
		printf("SDL Error: %s\n", SDL_GetError());
	}else if( !(IMG_Init(imgFlags) & imgFlags))
	{
		printf( "SDL_image could not be initilized. SDL Image Error: %s\n",IMG_GetError());
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
				}
				currentKeyStates = SDL_GetKeyboardState(NULL);
				int up = 0;
				int down = 0;
				if(currentKeyStates[SDL_SCANCODE_UP])
					up=1;
				if(currentKeyStates[SDL_SCANCODE_DOWN])
					down=1;
				printf("%d\n",up + down);
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

