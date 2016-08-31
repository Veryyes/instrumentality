#include <stdio.h>

#include "quadtree.h"
#include "wall.h"

Quadtree* gen_tree(char** map_data)
{

}

Quadnode* alloc_children(Quadnote* root)//Returns address of first child
{
	(root -> child1) = calloc(4, sizeof(Quadnode));
	(root -> child2) = (root1->child1)[1];
	(root -> child3) = (root1->child1)[2];
	(root -> child4) = (root1->child1)[3];
	if((root -> child1)|(root -> child2)|(root -> child3)|(root -> child4) == NULL)
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

	child4 -> x = root -> xcenter 
	child4 -> y = root -> ycenter
	child4 -> width = w;
	child4 -> height = h;
	child4 -> xcenter = (child4 -> x + child4 -> width)/2;
	child4 -> ycenter = (child4 -> y + child4 -> height)/2;

	return root->child1;
}

void add_point(Quadnode* root, int x, int y, Wall* data)
{
	if(root->data == NULL)
	{
		root->data = data;
		return;
	}else//This node already is full we need to split it 4 way
	{	//Also at this point it shouldnt have any children
		alloc_children(root);
		//Transfer root's data down
			
			//if both data points are in thr same quadrent
			//if data points are in diff quadrents
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
