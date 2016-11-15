#ifndef PLAYER_H
#define PLAYER_H

#define LEFT 0
#define UP 2
#define RIGHT 1
#define DOWN 3
#define FALLING 4

typedef struct player{
	int hp;
	int energy;
	int lives;
	SDL_Surface* sprite;
	SDL_Rect* pos;

	int xVel;
	int yVel;
	int xAccel;
	int yAccel;

	uint16_t state;

} Player;

Player* load_player();
void free_player(Player*);
void update_player(Player*, Uint8*);
void blit_player(Player*);

#endif
