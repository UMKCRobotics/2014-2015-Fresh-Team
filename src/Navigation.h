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

	bool cardinalComparator(Cardinal a, Cardinal b);
public:
	Navigation();
	Cardinal getCardinalToNextNodeInPath(vector<Cardinal> openings);
	void loadPath();
	void storeCriticalPath();
	void addCurrentNodePlusCardinalToPath();
	bool inFinalNode();
};

#endif