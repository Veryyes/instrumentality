#include <stdio.h>
#include <SDL2/SDL.h>

#include "map.h"
#include "util.h"

Map* load_map(char* path, SDL_Surface* screen){
	//temp stuff
	Map* new_map = malloc(sizeof(Map));
	if(new_map == NULL)
	{
		printf("Could not malloc space for map: %s\n", path);
		exit(1);
	}
	new_map->level = 1;
	new_map->background = load_surface("res/background/back1.png", screen);
	return new_map;
}

void free_map(Map* map){
	map->level=0;
	SDL_FreeSurface(map->background);
	map->background=NULL;
	free(map);
}
