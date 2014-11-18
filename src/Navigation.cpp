#include "Navigation.h"

Navigation::Navigation()
{

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

void Navigation::setRoundAndPart(int round, int part)
{
	if(round == 1)
	{
		position = 48;
		finalPosition = 9;
	}
	else if(round == 2) 
	{
		position = 48;
		finalPosition = 1;
	}
	else if(round == 3)
	{
		position = 49;
		finalPosition = 1;
	}
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
