#ifndef MAP_H
#define MAP_H

#define WALL_WIDTH 32
#define WALL_HEIGHT 32

typedef struct Wall{
	int x;
	int y;
	char data;
} Wall;

typedef struct Quadnode{
	Wall* data;
	int x;
	int y;
	int width;
	int height;
	int xcenter;
	int ycenter;
	struct Quadnode* child1;
	struct Quadnode* child2;
	struct Quadnode* child3;
	struct Quadnode* child4;
	/*
	Spacial Location of Children
		|
	    2	|   1
		|	
	--------|--------
		|
	    3	|   4
		|
	*/
} Quadnode;

typedef struct Quadtree{
	Quadnode* root;
} Quadtree;

Quadtree* gen_tree(char**);
void add_node(Quadnode*, int x, int y);
void free_quadtree(Quadnode*);
#endif
