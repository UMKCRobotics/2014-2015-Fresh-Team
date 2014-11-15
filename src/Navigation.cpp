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
	// Apply right-hand rule
	if(openings.size() == 1) return openings[0];
	else
	{
		sort(openings.begn(), openings.end(), cardinalComparator);

		int endDirection = orientation - 1;
		if(endDirection < 0) endDirection = Cardinal.West;

		for(int directionIndex = orientation; endDirection; directionIndex++)
		{
			if(std::find(openings.begin(), openings.end(), Cardinal(directionIndex) != openings.end())
			{
				// This direction exists so lets go with that.
				return Cardinal(directionIndex);
			}
		}
	}

	// No openings in the front 3 sides of the robot
	// Therefore we are in a dead end and we should just turn around
	int deadendExitDirection = orientation + 2;
	if(deadendExitDirection > 3) deadendExitDirection -= 3;

	return Cardinal(deadendExitDirection);
}

void Navigation::addCurrentNodePlusCardinalToPath()
{
	
}

bool Navigation::inFinalNode()
{

}

bool Navigation::cardinalComparator(Cardinal a, Cardinal b)
{
	return ( (a - b) < 0 ); // Equivalent of a < b
}
