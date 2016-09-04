#ifndef MAP_H
#define MAP_H

#ifndef MAPDIMS
#define SCREEN_WIDTH 1216
#define SCREEN_HEIGHT 704
#define BLOCK_WIDTH 38
#define BLOCK_HEIGHT 22
#endif

struct Quadtree;

typedef struct Map{
	int level;
	SDL_Surface* background;
	struct Quadtree* walls;
} Map;

Map* load_map(char*, SurfaceHashMap*);
void free_map(Map*);
#endif
