#include <stdlib.h>
#include <stdio.h>

#include "quadtree.h"

Quadtree* gen_tree(char** map_data)//takes raw map data
{
	Quadtree* tree = malloc(sizeof(Quadtree));
	if(tree == NULL)
	{
		printf("Out of memory\n");
		exit(1);
	}
	tree -> root = calloc(1, sizeof(Quadnode));
	tree -> root -> width = SCREEN_WIDTH;
	tree -> root -> height = SCREEN_HEIGHT;
	tree -> root -> xcenter = SCREEN_WIDTH/2;
	tree -> root -> ycenter = SCREEN_HEIGHT/2;

	int i, j;
	for(i = 0; i < BLOCK_HEIGHT; i++)
	{
		for(j = 0; j < BLOCK_WIDTH; j++)
		{
			if(map_data[i][j] == '0')//if its a wall
			{
				Wall* wall = malloc(sizeof(Wall));
				if(wall == NULL)
				{
					printf("Out of mem\n");
					exit(1);
				}
				wall -> x = j * WALL_WIDTH;
				wall -> y = i * WALL_HEIGHT;
				wall -> data = '0';

				add_wall((tree -> root), wall);
			}
		}
	}
}

Quadnode* alloc_children(Quadnode* root)//Returns address of first child
{
	(root -> child1) = calloc(4, sizeof(Quadnode));
	(root -> child2) = (root->child1)+1;
	(root -> child3) = (root->child1)+2;
	(root -> child4) = (root->child1)+3;
	if(root -> child1 == NULL)
	{
		printf("Unable to malloc mem for Quadnode\n");
		exit(1);
	}
	Quadnode* child1 = root->child1;
	Quadnode* child2 = root->child2;
	Quadnode* child3 = root->child3;
	Quadnode* child4 = root->child4;

	//Set dims
	int w = root->width/2;
	int h = root->height/2;
	
	child1 -> x = root -> xcenter;
	child1 -> y = root -> y;
	child1 -> width = w;
	child1 -> height = h;
	child1 -> xcenter = (child1 -> x + child1 -> width)/2;
	child1 -> ycenter = (child2 -> y + child2 -> height)/2;
	
	child2 -> x = root -> x;
	child2 -> y = root -> y;
	child2 -> width = w;
	child2 -> height = h;
	child2 -> xcenter = (child2 -> x + child1 -> width)/2;
	child2 -> ycenter = (child2 -> y + child2 -> height)/2;
	
	child3 -> x = root -> x;
	child3 -> y = root -> ycenter;
	child3 -> width = w;
	child3 -> height = h;
	child3 -> xcenter = (child3 -> x + child3 -> width)/2;
	child3 -> ycenter = (child3 -> y + child3 -> height)/2;

	child4 -> x = root -> xcenter;
	child4 -> y = root -> ycenter;
	child4 -> width = w;
	child4 -> height = h;
	child4 -> xcenter = (child4 -> x + child4 -> width)/2;
	child4 -> ycenter = (child4 -> y + child4 -> height)/2;

	return root->child1;
}

int isleaf(Quadnode* node)
{
	return (node->child1 == NULL); //If child1 is NULL, all the children are NULL
}

Quadnode* get_child(Quadnode* node, Wall* data)//returns which child this wall belongs to
{
	int x = data -> x > node -> xcenter;
	int y = data -> y > node -> ycenter;
	return (node -> child1)+(3+x-y-2*x*y)%4;
}

void add_wall(Quadnode* root, Wall* data)
{
	if(isleaf(root))
	{
		if(root -> data == NULL)// Empty Leaf
		{
			root -> data = data;
		}else// Leaf with data in it
		{
			alloc_children(root);

			//Transfer root's data down
			Wall* curr = root -> data;
			add_wall(get_child(root, curr), curr);
			(root -> data) = NULL;

			add_wall(get_child(root, data), data);
		}
	}else
	{
		add_wall(get_child(root, data), data);
	}
}

void free_quadnode(Quadnode* root)
{
	if(isleaf(root))
	{
		free(root->data);
		return;
	}
	int i;
	for(i = 0; i < 4; i++)
	{
		free_quadnode((root->child1)+i);
	}
}

void free_quadtree(Quadtree* tree)
{
	free_quadnode(tree -> root);
}
