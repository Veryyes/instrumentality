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

SDL_Texture* load_texture(char* path, SDL_Renderer* renderer)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* loaded_surface = IMG_Load(path);
	if(loaded_surface==NULL)
	{
		printf("Unable to load image %s, SDL Image Error:%s\n",path,IMG_GetError());
	}else{
		texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
		if(texture == NULL)
		{
			printf("Unable to create texture from %s, SDL Erorr:%s\n", path, SDL_GetError());
		}
		SDL_FreeSurface(loaded_surface);
	}
	
	return texture;
}
