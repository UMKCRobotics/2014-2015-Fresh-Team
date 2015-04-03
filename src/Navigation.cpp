#include "Navigation.h"
#include <sstream>
#include <iostream>
#include <fstream>

Navigation::Navigation()
{
	position = prevPos = startPosition;
	orientation = NORTH;

	commandqueue::registerFunction("ChangeRound", [this](std::string ROUND) 
	{
		//pass an integer as a string ie. "1" for round one.
		Logger::logMessage("I'm changing the round");
		std::string::size_type sz;
		int iround = std::stoi(ROUND, &sz);

		this->changeRound(iround);
		Logger::logMessage("Done changing the round");
	});

	commandqueue::registerFunction("ReportMove", [this](std::string MOVE)
	{
		//pass a string with the last move ie. "NORTH"
		std::stringstream ms;
		ms << MOVE;

		std::string dir;
		ms >> dir;

		

		//c++ can't do string switches
		if(dir == "NORTH"){ this->addMove(NORTH); this->changePosition(position - 7); }
		else if(dir == "EAST"){ this->addMove(EAST); this->changePosition(position + 1); }
		else if(dir == "SOUTH"){ this->addMove(SOUTH); this->changePosition(position + 7); }
		else if(dir == "WEST"){ this->addMove(WEST); this->changePosition(position - 1);}
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

void Navigation::changePosition(int newPosition)
{
	Logger::logMessage("Changing position...");
	Logger::logMessage("Previous Position: ");
	Logger::logMessage(to_string(prevPos));
	Logger::logMessage("New Position: ");
	Logger::logMessage(to_string(newPosition));
	prevPos = position;
	position = newPosition;
}

Cardinal Navigation::getNextMove()
{
	return map[position];
}

//Dear past self: What is this, C#? addCurrentNodePlusCardinalToPath is a ridiculous name.
//edit: so is getCardinalToNextNodeInPath
void Navigation::addMove(Cardinal node) 
{
	Logger::logMessage("Adding move: " + to_string(node));
	
	//checks map to ensure that the current node hasn't been added already and then acts appropriately
	auto nodeInMap = map.find(position);

	if(nodeInMap != map.end())
	{
		Logger::logMessage("New move is not the last node");
		
		for(auto it = map.end(); it != nodeInMap; it--)
		{
			map.erase(it);
		}

		return;
	}
	
	map.emplace(prevPos, node); //map stores the move to make from previous position to current position
	Logger::logMessage("Added move node");
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
