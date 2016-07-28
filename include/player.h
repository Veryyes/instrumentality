#ifndef PLAYER_H
#define PLAYER_H

typedef struct player{
	int hp;
	int energy;
	int lives;
	SDL_Surface* sprite;
	SDL_Rect* pos;
} Player;

Player* load_player(SDL_Surface*);
void free_player(Player*);

#endif
