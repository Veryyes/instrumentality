#include <stdio.h>
#include <SDL2/SDL.h>

#include "quadtree.h"
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
	FILE* map_file = fopen(path, "r");
	if(map_file == NULL)
	{
		printf("Cannot open file %s for reading\n",path);
		exit(1);
	}
	char buff[128];

	//Level
	fgets(buff, 4, map_file);
	new_map -> level = atoi(buff);
	
	//Background Image
	fgets(buff, 128, map_file);
	buff[strlen(buff)-1] = '\0';
	new_map->background = get_surface(buff, hashmap);

	//Level Data
	char** map_data = malloc(BLOCK_HEIGHT * sizeof(char*));
	int i;
	for(i = 0; i < BLOCK_HEIGHT; i++)
	{
		fgets(buff,BLOCK_WIDTH+2, map_file);
		map_data[i] = malloc((BLOCK_WIDTH+2) * sizeof(char*));
		buff[strlen(buff)-1] = '\0';
		strcpy(map_data[i], buff);
		printf("%s\n", buff);
	}
	new_map -> walls = gen_tree(map_data);
	for(i = 0; i< BLOCK_HEIGHT; i++)
	{
		free(map_data[i]);
	}
	free(map_data);	

	fclose(map_file);

	return new_map;
}

void free_map(Map* map)
{
	map->level=0;
	map->background=NULL;
	free(map);
}
