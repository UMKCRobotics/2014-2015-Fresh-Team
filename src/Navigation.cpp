#include "Navigation.h"

Navigation::Navigation(Robot& robot)
{
	position = startPosition;
	
}

void Navigation::loadPath()
{

}

void Navigation::storeCriticalPath()
{

}

Cardinal Navigation::getCardinalToNextNodeInPath(vector<Cardinal> openings)
{
	return NORTH;
}

void Navigation::addCurrentNodePlusCardinalToPath(Cardinal node)
{
	map[position] = node;
}

bool Navigation::inFinalNode()
{
	return position == finalPosition;
}

int Navigation::getCurrentPosition()
{
	return position;
}

int Navigation::getFinalPosition()
{
	return finalPosition;
}

Cardinal Navigation::getOrientation()
{
	return orientation;
}
