#ifndef PLAYER_H
#define PLAYER_H

#define LEFT 0
#define UP 90
#define RIGHT 180
#define DOWN 270

typedef struct player{
	int hp;
	int energy;
	int lives;
	SDL_Surface* sprite;
	SDL_Rect* pos;

	int xVel;
	int yVel;

	int direction;
} Player;

Player* load_player(SurfaceHashMap*);
void free_player(Player*);
void update_player(Player*, Uint8*);
void blit_player(Player*);

#endif
