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
	void traverse(direction);
	void appendAndTraverse(Cardinal direction);

	bool deleteBranchTo(Cardinal direction);
	MazeNode* getNodeTo(Cardinal direction);
	bool nodeExistsTo(Cardinal direction);

	Coordinate getCoordinates();

	bool isStart = false;
	bool isFinish = false;

private:
	std::weak_ptr<MazeNode> up, down, left, right;
	int traversalCount;
	Coordinate position; //may change this system

	std::weak_ptr<std::multimap<Coordinate, 
		std::shared_ptr<MazeNode> > > Mazemap;


};

