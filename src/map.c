#include <stdio.h>
#include <SDL2/SDL.h>

#include "surface_hashmap.h"
#include "quadtree.h"
#include "util.h"
#include "map.h"

extern SDL_Surface* screen;

int Gravity = -10;

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
	new_map -> wall_tree = quadtree_new(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	int i;
	for(i = 0; i < BLOCK_HEIGHT; i++)
	{
		fgets(buff,BLOCK_WIDTH+2, map_file);	
		buff[strlen(buff)-1] = '\0';
		//printf("%s\n", buff);
		int j; 
		int bufflen = strlen(buff);
		for(j = 0; j < bufflen; j++)
		{	
			if(buff[j] == '0'){
				Wall* wall = malloc(sizeof(Wall));
				wall -> image = get_surface(WALL, hashmap);
				SDL_Rect* pos = malloc(sizeof(SDL_Rect));
				pos -> x = j*WALL_DIM;
				pos -> y = i*WALL_DIM;
				wall -> pos = pos;
				quadtree_insert(new_map -> wall_tree, pos -> x, pos -> y,(void*)wall);
			}
		}
	}
	fclose(map_file);

	return new_map;
}

void update_map(Map* map)//TODO implement later when map scrolls
{//Note, wall collisions are in respective struct's files
		
}

int test[BLOCK_WIDTH][BLOCK_HEIGHT];
void blit_wall(quadtree_node_t* node)
{
	if(node->key != NULL)
		SDL_BlitSurface(((Wall*)(node->key))->image, NULL, screen, ((Wall*)(node->key))->pos);
}

void ascent(quadtree_node_t* a)
{
	//Empty Method for quadtree_walk param
}

void blit_map(Map* map)
{
	SDL_BlitSurface(map->background, NULL, screen, NULL);
	quadtree_walk(map->wall_tree->root, blit_wall, ascent);	
}

void free_tree(quadtree_node_t* node)
{
	if(node->key != NULL)
	{
		free(((Wall*)(node->key))->pos);
		free(node->key);
	}
}

void free_map(Map* map)
{
	map->level=0;
	map->background=NULL;
	quadtree_walk(map->wall_tree->root, free_tree, ascent);
	free(map->wall_tree);
	free(map);
}
