#include "Navigation.h"
#include <fstream>
#include <string>
#include <regex>

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

	std::string Round;

	while(infile.good())
	{
		infile >> Round;
		int iround = std::stoi(Round, &std::string::size_type);

		infile >> cardinal;

		switch(cardinal)
		{
			case "NORTH":
			map.emplace(iround, NORTH);
			break;
			case "SOUTH":
			map.emplace(iround, SOUTH);
			break;
			case "EAST":
			map.emplace(iround, EAST);
			break;
			case "WEST":
			map.emplace(iround, WEST);
			break;
			default:
				Logger::logError("COULD NOT READ CARDINAL FROM FILE: " + cardinal);
				ifstream.close();
				return false;
		}
	}

	ifstream.close();

}

bool Navigation::storeCriticalPath()
{

	Logger::logMessage("Attempting to write path to file: " + filelocation);

	ofstream outfile;
	outfile.open(fileLocation, ofstream::out | ofstream::app);

	if(!outfile)
	{
		Logger::logError("COULD NOT WRITE TO FILE: " + fileLocation);
	}

	for(auto& position: map)
	{
		outfile << position.first << " " << position.second << endl;

	}

	outfile.close();

}

Cardinal Navigation::getCardinalToNextNodeInPath()
{
	return map[position];
}

void Navigation::addCurrentNodePlusCardinalToPath(Cardinal node)
{
	map.emplace(position, node);
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
