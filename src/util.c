#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "util.h"

//Loads surface for bliting on the screen
SDL_Surface* load_surface(char* path, SDL_Surface* screen)
{
	SDL_Surface* optimized = NULL;
	SDL_Surface* crude = IMG_Load(path);
	
	if(crude == NULL)
	{
		printf("Unable to load image %s, SDL Image Error:%s\n", path, IMG_GetError());
	}else
	{
		optimized = SDL_ConvertSurface(crude, screen->format, NULL);
		if(optimized == NULL)
		{
			printf("Unable to optimize image %s, SDL Error: %s\n", path, SDL_GetError());
		}
		SDL_FreeSurface(crude);
	}
	return optimized;
}
