#include "Navigation.h"
#include <ifstream>
#include <string>

Navigation::Navigation()
{
	position = startPosition;

	CommandQueue::RegisterFunction("CHANGEROUND", [this](std::string ROUND) //pass an integer as a string ie. "1" for round one.
	{
		int iround = std::stoi(ROUND, std::string::size_type);

		changeRound(iround);


	});
}

void Navigation::changeRound(int round)
{
	//todo: Set up the proper configurations for each round
	switch(round)
	{
		case 1:
		startposition = 48;
		finalposition = 9;

		break;
		case 2:
		startposition = 48
		finalposition = 1;

		break;
		case 3:
		startposition = 49;
		finalposition = 1;

		break;
		default:
		break;
	}



}

bool Navigation::loadPath()
{
	Logger::logMessage("Attempting to read path in file: " + filelocation);

	std::ifstream infile(filelocation, std::ifstream::in);
	
	if(!infile)
	{
		Logger::logError("COULD NOT READ THE FILE: " + filelocation);
		return false;		
	}

	std::string line;

	while(infile.good())
	{
		line = infile.getLine();
		

		switch(cardinal)
		{
			case "NORTH":

			break;
			case "SOUTH":

			break;
			case "EAST":

			break;
			case "WEST":

			break;
			default:
				Logger::logError("COULD NOT READ CARDINAL FROM FILE: " + cardinal);
				return false;
		}
		map.emplace()
	}

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
