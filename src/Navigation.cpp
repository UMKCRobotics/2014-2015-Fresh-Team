#include "Navigation.h"
#include <string>

Navigation::Navigation()
{
	position = startPosition;

	CommandQueue::RegisterFunction("CHANGEROUND", [this](std::string ROUND) //pass an integer as a string ie. "1" for round one.
	{
		int iround = std::stoi(ROUND, std::string::size_type);

		changeround(iround);


	});
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
