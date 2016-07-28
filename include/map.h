#ifndef MAP_H
#define MAP_H

typedef struct Map{
	int level;
	SDL_Surface* background;
} Map;

Map* load_map(char*, SDL_Surface*);
void free_map(Map*);
#endif
