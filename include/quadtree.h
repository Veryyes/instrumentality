#ifndef MAP_H
#define MAP_H

typedef struct Quadnode{
	char* data;
	int xcenter;
	int ycenter;
/*	int x;
	int y;
	int width;
	int height;*/
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
	int size; //number of total nodes
} Quadtree;

Quadtree* gen_tree(char**);
void add_node(Quadnode*, int x, int y);

#endif
