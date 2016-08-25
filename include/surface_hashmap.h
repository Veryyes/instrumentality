#ifndef SURFACE_HASHMAP_H
#define SURFACE_HASHMAP_H

typedef struct SurfaceEntry
{
	char* key;
	SDL_Surface* value;
} SurfaceEntry;

typedef struct SurfaceHashMap
{
	SurfaceEntry** map;
	int len;
} SurfaceHashMap;

SurfaceHashMap* load_SurfaceHashMap(SDL_Surface*);
void free_SurfaceHashMap(SurfaceHashMap*);
void add_surface(SurfaceEntry*, SurfaceHashMap*);
SDL_Surface* get_surface(char*, SurfaceHashMap*);
void populate_surface_hashmap(char*, char*, char*, SurfaceHashMap*, SDL_Surface*);
void printmap(SurfaceHashMap*);

#endif
