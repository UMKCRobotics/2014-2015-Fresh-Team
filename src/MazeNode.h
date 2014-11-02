#include "Cardinal.h"

class MazeNode
{
public:
	MazeNode();
	MazeNode(Cardinal EntryDirection, MazeNode node);

	void append(Cardinal direction, MazeNode node);
	MazeNode getNode(Cardinal direction);
	void traverse();
	int getTraversalCount();


private:
	MazeNode *up, *down, *left, *right;
	int traversalCount;
}