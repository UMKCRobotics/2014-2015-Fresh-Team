#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include "logger.h"
#include "CommandQueue.h"
using namespace std;

#include "Cardinal.h"

class Navigation
{
private:
	const string fileLocation = "/home/Ubuntu/Documents/path.txt"; // Dummy value
	Cardinal orientation;
	std::map<int, Cardinal> map; //holds position and direction

	/*
	Round 1
		Start 	48
		End 	9

	Round 2
		Start 	48
		End 	1

	Round 3
		Start 	49
		End 	1
	*/

	int position 				= 0; // position set to start position upon class instantiation
	int prevPos					= 0; // previous position
	int startPosition 			= 48;
	int finalPosition 			= 9; 	// Hard coded value because
										// we no longer have dials
										// Must be recoded for each round

	void changeRound(int round); //to be called from command "CHANGEROUND"

public:
	Navigation();
	Cardinal getNextMove();
	bool loadPath();
	bool storeCriticalPath();
	void addMove(Cardinal node);
	void changePosition(int pos);

	bool inFinalNode();

	int getCurrentPosition();
	int getFinalPosition();

};

#endif