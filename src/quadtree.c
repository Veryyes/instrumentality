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

int isleaf(Quadnode* node)
{
	return (node->child1 == NULL); //If child1 is NULL, all the children are NULL
}

Quadnode* get_child(Quadnode* node, Wall* data)//returns which child this wall belongs to
{
	int x = data -> x > node -> xcenter;
	int y = data -> y > node -> ycenter;
	return (node -> child1)[(3+x-y-2*x*y)%4];
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

