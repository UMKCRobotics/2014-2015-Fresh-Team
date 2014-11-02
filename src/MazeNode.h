#include <map>
#include "Cardinal.h"

class MazeNode
{
public:

	//constructors
	MazeNode();
	MazeNode(Cardinal EntryDirection, MazeNode node);


	void append(Cardinal direction, MazeNode node);

	MazeNode getNodeTo(Cardinal direction);
	bool nodeExistsTo(Cardinal direction);

	bool isStart = false;
	bool isFinish = false;

private:
	MazeNode *up, *down, *left, *right;
	int traversalCount;
	int posX, posY; //may change this system

	std::map<pair<int, int>, std::unique_ptr<MazeNode>> *Mazemap;
	//pair doesn't work with ints?


};

/*******************************Notes*******************************************
These notes are just for reference on how I envision it working as of November 2 
at 2AM and mostly for myself, but I included them because I feel it will be 
useful to anyone else.

Maze will be constructed as robot navigates -> 
check if the node in direction of movement exists already
if it doesnt -> append a new node
move the position pointer to that next node
(also need to check by coordinate system or such if a disconnected node exists
in that position -> I have ideas for how to handle this but they're not needed
for these notes)
*******************************************************************************/

