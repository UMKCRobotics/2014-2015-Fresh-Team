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
	const string fileLocation = "/home/Ubuntu/Documents/path.txt";
	Cardinal orientation;
	Cardinal map[50];

	int position;
	int finalPosition;

public:
	Navigation();
	Cardinal getCardinalToNextNodeInPath(vector<Cardinal> openings);
	void loadPath();
	void storeCriticalPath();
	void addCurrentNodePlusCardinalToPath(Cardinal node);
	bool inFinalNode();

	void setRoundAndPart(int round, int part);
	int getCurrentPosition();
	int getFinalPosition();
	Cardinal getOrientation(void);
};

#endif