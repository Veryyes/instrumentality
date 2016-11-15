#ifndef MAP_H
#define MAP_H
#include "quadtree.h"
#define SCREEN_WIDTH 1216
#define SCREEN_HEIGHT 704
#define BLOCK_WIDTH 38
#define BLOCK_HEIGHT 22
#define WALL_DIM 32
#define MAP_AREA 38*22

#define WALL "./res/block.png"

typedef struct Map{
	int level;
	SDL_Surface* background;
	quadtree_t* wall_tree;
} Map;

typedef struct Wall{
	SDL_Surface* image;
	SDL_Rect* pos;
}Wall;

Map* load_map(char*);
void update_map(Map*);
void blit_map(Map*);
void free_map(Map*);
#endif
