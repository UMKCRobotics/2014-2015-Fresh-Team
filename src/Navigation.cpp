#include "Navigation.h"
#include <sstream>
#include <iostream>
#include <fstream>

Navigation::Navigation()
{
	position = startPosition;

	commandqueue::registerFunction("ChangeRound", [this](std::string ROUND) 
	{
		//pass an integer as a string ie. "1" for round one.
		std::string::size_type sz;
		int iround = std::stoi(ROUND, &sz);

		this->changeRound(iround);
	});

	commandqueue::registerFunction("ReportMove", [this](std::string MOVE)
	{
		//pass a string with the current position and last move ie. "2 NORTH"
		std::stringstream ms;
		ms << MOVE;

		int pos;
		std::string dir;
		ms >> pos >> dir;

		this->changePosition(pos);

		//c++ can't do string switches
		if(dir == "NORTH") addMove(NORTH);
		else if(dir == "EAST") addMove(EAST);
		else if(dir == "SOUTH") addMove(SOUTH);
		else if(dir == "WEST") addMove(WEST);
		else Logger::logError("Improper direction provided: " + dir);
	});

}

void Navigation::changeRound(int round)
{
	//todo: Set up the proper configurations for each round
	switch(round)
	{
		case 1:
		startPosition = 48;
		finalPosition = 9;

		break;
		case 2:
		startPosition = 48;
		finalPosition = 1;

		break;
		case 3:
		startPosition = 49;
		finalPosition = 1;

		break;
		default:
		break;
	}

}

bool Navigation::loadPath()
{
	Logger::logMessage("Attempting to read path in file: " + fileLocation);

	std::ifstream infile(fileLocation, std::ifstream::in);
	
	if(!infile)
	{
		Logger::logError("Could not read file: " + fileLocation);
		return false;		
	}

	std::string Round;
	int pos;

	while(infile.good())
	{
		infile >> Round;
		string cardinal = "";

		infile >> pos >> cardinal;

		if(cardinal == "NORTH") map.emplace(pos, NORTH);
		else if(cardinal == "SOUTH") map.emplace(pos, SOUTH);
		else if(cardinal == "EAST") map.emplace(pos, EAST);
		else if(cardinal == "WEST") map.emplace(pos, WEST);
		else
		{
			Logger::logError("Could not read cardinal from file: " + cardinal);
			infile.close();
			return false;
		}
	}

	infile.close();

	return true;
}

bool Navigation::storeCriticalPath()
{

	Logger::logMessage("Attempting to write path to file: " + fileLocation);

	std::ifstream cpFile(fileLocation, std::ifstream::in);
	std::ofstream outFile;

	outFile.open(fileLocation + ".old", std::ofstream::out | std::ofstream::trunc);
	if(cpFile.good())
	{
		Logger::logMessage(fileLocation + " already exists, creating a backup!");
		outFile << cpFile << std::endl;

		while(outFile.good())
		{
			outFile << cpFile << " " << cpFile << std::endl;
		}
	}

	cpFile.close();
	outFile.close();

	outFile.open(fileLocation, std::ofstream::out | std::ofstream::trunc);

	if(!outFile)
	{
		Logger::logError("Could not write to file: " + fileLocation);
	}

	for(auto& position: map)
	{
		outFile << position.first << " " << position.second << endl;

	}

	outFile.close();

	return true;
}

void Navigation::changePosition(int pos)
{
	prevPos = position;
	position = pos;
}

Cardinal Navigation::getNextMove()
{
	return map[position];
}

//Dear past self: What is this, C#? addCurrentNodePlusCardinalToPath is a ridiculous name.
//edit: so is getCardinalToNextNodeInPath
void Navigation::addMove(Cardinal node) 
{
	//checks map to ensure that the current node hasn't been added already and then acts appropriately
	auto nodeInMap = map.find(position);

	if(nodeInMap != map.end())
	{
		for(auto it = map.end(); it != nodeInMap; it--)
		{
			map.erase(it);
		}

		return;
	}


	map.emplace(prevPos, node); //map stores the move to make from previous position to current position
}

void Navigation::setOrientation(Cardinal newOrientation)
{
	orientation = newOrientation;
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

Cardinal Navigation::getCurrentOrientation()
{
	return orientation;
}
