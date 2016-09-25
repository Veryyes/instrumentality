#ifndef MAP_H
#define MAP_H
#include "quadtree.h"
#ifndef MAPDIMS
#define MAPDIMS
#define SCREEN_WIDTH 1216
#define SCREEN_HEIGHT 704
#define BLOCK_WIDTH 38
#define BLOCK_HEIGHT 22
#endif
#define MAP_AREA 38*22


typedef struct Map{
	int level;
	SDL_Surface* background;
	quadtree_t* wall_tree;
} Map;

Map* load_map(char*, SurfaceHashMap*);
void free_map(Map*);
#endif
