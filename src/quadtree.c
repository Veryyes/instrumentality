#include <stdio.h>

#include "quadtree.h"

Quadtree* gen_tree(char** map_data)
{

}

void add_point(Quadnode* root, int x, int y)
{
	(root -> child1) = malloc(sizeof(Quadnode));
	(root -> child2) = malloc(sizeof(Quadnode));
	(root -> child3) = malloc(sizeof(Quadnode));
	(root -> child4) = malloc(sizeof(Quadnode));
	if((root -> child1)|(root -> child2)|(root -> child3)|(root -> child4) == NULL)
	{
		printf("Unable to malloc mem for Quadnode\n");
		exit(1);
	}
	if(x > root->xcenter)//right side
	{
		if(y > root->ycenter)//bottom
		{//4
			
		}else//top
		{//1

		}
	}else //left side
	{
		if(y > root->ycenter)//bottom
		{//3

		}else//top
		{//2

		}
	}
}
