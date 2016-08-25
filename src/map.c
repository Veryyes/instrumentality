#include <stdio.h>
#include <SDL2/SDL.h>

#include "util.h"
#include "surface_hashmap.h"
#include "map.h"

Map* load_map(char* path, SurfaceHashMap* hashmap){
	//Malloc space
	Map* new_map = malloc(sizeof(Map));
	if(new_map == NULL)
	{
		printf("Could not malloc space for map: %s\n", path);
		exit(1);
	}
	//Temporary Default Values
	new_map->level = 1;
	new_map->background = get_surface("./res/background/back1.png", hashmap);
	return new_map;
}

void free_map(Map* map)
{
	map->level=0;
	map->background=NULL;
	free(map);
}
