#include "MazeNode.h"

//initializes empty MazeNode
MazeNode::MazeNode(
	int Location, Cardinal EntryDirection, std::weak_ptr<MazeNode> previous, nodeType Type)
{
	location = Location;
	entrydirection = EntryDirection;
	previousNode = previous;
	nextNode =  std::shared_ptr<MazeNode>(null_ptr);
}

void MazeNode::append(MazeNode nextNode)
{
	nextNode = make_shared(nextNode);
}

std::shared_ptr<MazeNode> MazeNode::traverse()
{
	weak_ptr<MazeNode> node = nextNode;
	return nextNode;
}

std::shared_ptr<MazeNode> MazeNode::appendAndTraverse(MazeNode nextNode)
{
	append(nextNode);
	return traverse();
}

std::shared_ptr<MazeNode> MazeNode::backstep()
{
	return previousNode.lock();
}

void MazeNode::deleteNext()
{
	nextNode.reset();
}

std::shared_ptr<MazeNode> MazeNode::backstepAndDelete()
{
	shared_ptr<MazeNode> temp = backstep();
	temp.deleteNext());
	return temp;
}

Cardinal MazeNode::getEntryDirection()
{
	return entrydirection();
}

int MazeNode::getLocation()
{
	return location;
}


