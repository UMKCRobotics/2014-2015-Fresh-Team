#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Cardinal.h"

class Navigation
{
private:
	const string fileLocation = "/home/Ubuntu/Documents/path.txt"; // Dummy value
	Cardinal orientation;
	Cardinal map[50];

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
	const int startPosition 	= 48;
	const int finalPosition 	= 9; 	// Hard coded value because
										// we no longer have dials
										// Must be recoded for each round

public:
	Navigation();
	Cardinal getCardinalToNextNodeInPath(vector<Cardinal> openings);
	void loadPath();
	void storeCriticalPath();
	void addCurrentNodePlusCardinalToPath(Cardinal node);
	bool inFinalNode();

	int getCurrentPosition();
	int getFinalPosition();
	Cardinal getOrientation(void);
};

#endif