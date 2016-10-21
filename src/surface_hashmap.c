#include <stdio.h>
#include <ftw.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "surface_hashmap.h"


SurfaceHashMap* load_SurfaceHashMap(SDL_Surface* screen)
{
	SurfaceHashMap* hashmap = malloc(sizeof(SurfaceHashMap));
	if(hashmap==NULL)
	{
		printf("Could not malloc mem for SurfaceHashMap\n");
		exit(1);
	}
	hashmap->len = countfiles("./res",".png .jpg"," ") * 3;
	hashmap->map = calloc(hashmap->len, sizeof(SurfaceEntry));
	if(hashmap->map == NULL)
	{
		printf("Could not calloc memory for SurfaceHashMap\n");
		exit(1);
	}
	populate_surface_hashmap("./res",".png .jpg", " ", hashmap, screen);
	return hashmap;
}

void free_SurfaceHashMap(SurfaceHashMap* hashmap)
{
	long i;
	for(i = 0; i < hashmap->len; i++)
	{
		SurfaceEntry* entry = hashmap->map[i];
		if(entry == NULL)
			continue;
		SDL_FreeSurface(entry->value);
		free(entry);
	}
	free(hashmap);
}

int hash(char* surface_name, SurfaceHashMap* hashmap)
{
	int hash = 0;
	int i;
	for(i=0;surface_name[i];i++)
	{
		hash += i*surface_name[i];
	}
	return hash%(hashmap->len);
}

int quad_probe_hash(int hash, SurfaceHashMap* hashmap)
{
	int new_hash = hash;
	long i;
	for(i = 0; (hashmap->map)[new_hash]!=NULL; i++)
	{
		new_hash = (hash + i*i) % (hashmap->len);
		if(new_hash<0)
			new_hash *= -1;
	}
	return new_hash;
}

void add_surface(SurfaceEntry* entry, SurfaceHashMap* hashmap)
{
	int hash_code = hash(entry->key, hashmap);
	hash_code = quad_probe_hash(hash_code, hashmap);
	(hashmap->map)[hash_code] = entry;
}

SDL_Surface* get_surface(char* surface_name, SurfaceHashMap* hashmap)
{
	int hash_code = hash(surface_name, hashmap);
	int next_hash = hash_code;
	long i = 0;
	SurfaceEntry* item = (hashmap->map[next_hash]);
	while(item != NULL && strcmp(item->key, surface_name))
	{
		next_hash = (hash_code + i*i) % (hashmap->len);
		if(next_hash<0)
			next_hash *= -1;
		item = (hashmap->map[next_hash]);
		i++;
	}
	/*for(i = 0; ((hashmap->map)[next_hash]) != NULL && !strcmp(((hashmap->map)[next_hash])->key,surface_name); i++)
	{
		next_hash = (hash_code + i*i) % (hashmap->len);
		if(next_hash<0)
			next_hash *= -1;
	}*/
	return item->value;
	//return ((hashmap->map)[next_hash])->value;
}

int countfiles(const char* root, const char* extention_filter, const char* delimiters)
{
	int i=0;
	int read_file(const char* path, const struct stat* status, int info)
	{
		if(info == FTW_F)//If its a file
		{
			char filter_cpy[strlen(extention_filter)+1];
		strcpy(filter_cpy, extention_filter);
			char* extention = strtok(filter_cpy, delimiters);
			int valid = 0;
			while(extention!=NULL) //checks if the file has at least one of the given extentions
			{
				if(strstr(path,extention))
				{
					valid=1;
					break;
				}
				extention=strtok(NULL,delimiters);
			}
			if(valid)
			{
				i++;
			}
		}
		return 0;
	}
	ftw(root, &read_file, 4);
	return i;
}

void populate_surface_hashmap(char* root, char* extention_filter, char* delimiters, SurfaceHashMap* hashmap, SDL_Surface* screen)
{
	int read_file(const char* path, const struct stat* status, int info)
	{
		if(info == FTW_F)//If its a file
		{
			char filter_cpy[strlen(extention_filter)+1];
			strcpy(filter_cpy, extention_filter);
			char* extention = strtok(filter_cpy, delimiters);
			int valid = 0;
			while(extention!=NULL) //checks if the file has at least one of the given extentions
			{
				if(strstr(path,extention))
				{
					valid=1;
					break;
				}
				extention=strtok(NULL,delimiters);
			}
			if(valid)
			{
				SurfaceEntry* entry = malloc(sizeof(SurfaceEntry));
				if(entry==NULL)
				{
					printf("Could not malloc mem for entry in Surface Hashmap\n");
					exit(1);
				}
				char* pathmem = malloc(strlen(path)+1);
				strcpy(pathmem, path);
				entry->key = pathmem;
				entry->value = load_surface(path, screen);
				
				add_surface(entry, hashmap);
				//printf("Added: %s\n", path);
			}
		}
		return 0;
	}
	ftw(root, &read_file, 4);
}

void printmap(SurfaceHashMap* hashmap)
{
	int i;
	for(i = 0; i < hashmap->len; i++)
	{
		if((hashmap->map)[i]!=NULL)
			printf("[%d] %s\n",i,((hashmap->map)[i])->key);
	}
}
