#include <map>
#include <memory>
#include "cardinal.h"
#include "coordinate.h"

class MazeNode
{
public:
	
	//constructors
	MazeNode(
		std::weak_ptr<
		std::multimap<Coordinate,std::shared_ptr<MazeNode> > > map);

	MazeNode(Cardinal EntryDirection, std::shared_ptr<MazeNode> node, 
		std::weak_ptr<
		std::multimap<Coordinate,std::shared_ptr<MazeNode> > > map);


	void append(Cardinal direction);

	MazeNode* getNodeTo(Cardinal direction);
	bool nodeExistsTo(Cardinal direction);

	Coordinate getCoordinates();

	bool isStart = false;
	bool isFinish = false;

private:
<<<<<<< HEAD
	std::shared_ptr<MazeNode> *up, *down, *left, *right;
=======
	std::weak_ptr<MazeNode> up, down, left, right;
>>>>>>> 7f769f872ad83fa43c7063675ca18ed2882acbee
	int traversalCount;
	Coordinate position; //may change this system

	std::weak_ptr<std::multimap<Coordinate, 
		std::shared_ptr<MazeNode> > > Mazemap;


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

