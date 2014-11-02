#include "MazeNode.h"


//initializes empty MazeNode(for Root)
MazeNode::MazeNode()
{
	up = NULL;
	down = NULL;
	left = NULL;
	right = NULL;
}

//Initializes maze node with a pointer to the previous node
MazeNode::MazeNode(cardinal EntryDirection, MazeNode node)
{
	switch(EntryDirection)
	{
		case NORTH:
			up = &node;
			down = NULL;
			left = NULL;
			right = NULL;
			break;
		case SOUTH:
			up = NULL;
			down = &node;
			left = NULL;
			right = NULL;
			break;
		case EAST:
			up = NULL;
			down = NULL;
			left = NULL;
			right = &node;
			break;
		case WEST:
			up = NULL;
			down = NULL;
			left = &node;
			right = NULL;
			break;
	}
}

//adds a pointer to the node to the new direction
void MazeNode::append(Cardinal Direction, MazeNode node)
{
	switch(Direction)
	{
		case NORTH:
			up = &(new MazeNode(Cardinal.SOUTH, this));
			break;
		case SOUTH:
			down = &(new MazeNode(Cardinal.NORTH, this));
			break;
		case WEST:
			left = &(new MazeNode(Cardinal.RIGHT, this));
			break;
		case EAST:
			right = &(new MazeNode(Cardinal.LEFT, this));
			break;
	}
}

//todo: Review c++ pointers, finish filling this in, make corrections to my tree
//datastructure
