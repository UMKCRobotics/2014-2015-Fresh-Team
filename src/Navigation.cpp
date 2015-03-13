#include "Navigation.h"
#include <fstream>
#include <string>
#include <sstream>

Navigation::Navigation()
{
	position = startPosition;

	CommandQueue::RegisterFunction("CHANGEROUND", [this](std::string ROUND) //pass an integer as a string ie. "1" for round one.
	{
		int iround = std::stoi(ROUND, std::string::size_type);

		this->changeRound(iround);


	});

	CommandQueue::RegisterFunction("REPORTMOVE", [this](std::string MOVE)
	{
		//pass a string with the current position and last move ie. "2 NORTH"
		std::stringstream ms;
		ms << MOVE;

		int pos;
		std::string dir;
		ms >> pos >> dir;

		this->changePosition(pos);

		switch(dir)
		{
			case "NORTH":
			this->addMove(NORTH);
			break;
			case "EAST":
			this->addMove(EAST);
			break;
			case "SOUTH":
			this->addMove(SOUTH);
			break;
			case "WEST":
			this->addMove(WEST);
			break;
		};

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
	cardinal move;
	int pos;

	while(infile.good())
	{
		infile >> Round;
		//int iround = std::stoi(Round, &std::string::size_type);

		infile >> pos >> cardinal;

		switch(cardinal)
		{
			case "NORTH":
			map.emplace(pos, cardinal);
			break;
			case "SOUTH":
			map.emplace(pos, SOUTH);
			case "EAST":
			map.emplace(pos, EAST);
			break;
			case "WEST":
			map.emplace(pos, WEST);
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

	std::ifstream cpFile(fileLocation, std::ifstream::in);
	std::ostream outFile;

	outFile.open(fileLocation + ".old", std::ofstream::out | std::ofstream::trunc);
	if(cpFile.good())
	{
		Logger::logMessage(filelocation + " already exists, creating a backup!");
		outfile << cpFile << std::endl;

		while(outFile.good())
		{
			outfile << cpFile << " " << cpFile << std::endl;
		}
	}

	cpFile.close();
	outFile.close();

	outFile.open(fileLocation, ofstream::out | ofstream::trunc);

	if(!outfile)
	{
		Logger::logError("COULD NOT WRITE TO FILE: " + fileLocation);
	}

	for(auto& position: map)
	{
		outfile << position.first << " " << position.second << endl;

	}

	outfile.close();

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
		for(auto it = map.end(); it != nodeInMap; iter--)
		{
			map.erase(it);
		}

		return;
	}


	map.emplace(prevPos, node); //map stores the move to make from previous position to current position
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
