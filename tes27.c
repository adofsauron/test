#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node *Positon;
typedef struct Node *Tree;

#define ElemType  int
#define NONE -1

struct Node
{
	Tree left;
	Tree right;
	ElemType elem;
};

//typedef struct Node *Positon;
//typedef struct Node *Tree;

struct Node *init(ElemType _elem)
{
	struct Node  *tree;
	tree = (struct Node *) malloc (sizeof(struct Node));

	tree->left = tree->right = NULL;
	tree->elem = _elem;

	return tree;
}

Tree set(Tree tree, Tree _left, Tree _right)
{
	tree->left = _left;
	tree->right = _right;

	return tree;
}

Tree insert(Tree tree, Positon pos)
{
	if(tree)
	{
		if(tree->elem > pos->elem)
		{
			if(tree->left == NULL)
				tree->left = pos;
			else	
				tree->left = insert(tree->left, pos);
		}
		else if(tree->elem < pos->elem)
		{
			if(tree->right)
				tree->right = insert(tree->right, pos);
			else
				tree->right = pos;	
		}
	}
	else
	{
			return NULL;
	}
	 
	return tree;
}

void show(Tree tree)
{
	if(tree)
	{
		if(tree->left)
			show(tree->left);

		printf("%d\t",tree->elem);

		if(tree->right)
			show(tree->right);
	}
	
	//printf("\n");
	//printf("NULL");
	return ;
}

int main()
{
	Positon pos1, pos2, pos3, pos4, pos5, pos6;
	pos1 = init(1);
	pos2 = init(2);
	pos3 = init(3);
	pos4 = init(4);
	pos5 = init(5);

/*
	insert(pos2, pos1);
	insert(pos2, pos3);
	insert(pos3, pos4);
*/	

	set(pos1, pos2, pos3);
	set(pos3, pos4, pos5);

	show(pos1);
	printf("\n");

	return 0;
}


