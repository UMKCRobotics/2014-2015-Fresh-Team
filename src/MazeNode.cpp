#include "MazeNode.h"


//initializes empty MazeNode(for Root)
MazeNode::MazeNode(std::weak_ptr <
	std::multimap<Coordinate, std::shared_ptr<MazeNode> > > map)
{

	//sets next positions to empty weak_ptrs
	up = std::make_shared<MazeNode>(nullptr);
	down = std::make_shared<MazeNode>(nullptr);
	left = std::make_shared<MazeNode>(nullptr);
	right = std::make_shared<MazeNode>(nullptr);

	//assigns the provided map to the mazemap
	Mazemap = map;

	//assigns position x and y to 0
	position.x = position.y = 0;

	//traversal count is set to 1 because it has been traversed if detected.
	traversalCount = 1;

	//sets isStart to true
	isStart = true;

	std::shared_ptr<std::multimap<Coordinate, std::shared_ptr<MazeNode> > > mazemapaccessor = Mazemap.lock();

	mazemapaccessor->insert(std::make_pair(position, std::make_shared<MazeNode>(this)));

}

//Initializes maze node with a pointer to the previous node
MazeNode::MazeNode(Cardinal EntryDirection, std::shared_ptr<MazeNode> node, std::weak_ptr<std::multimap<Coordinate, std::shared_ptr<MazeNode> > > map)
{
	/*!!note that this constructor does not add to the map because it is assumed
	*that this constructor is being called from the append function of another
	*node where it will be added automatically.
	*/

	switch(EntryDirection)
	{
		position = node->getCoordinates;

		case NORTH:
			up = node;
			down = std::make_shared<MazeNode>(nullptr);
			left = std::make_shared<MazeNode>(nullptr);
			right = std::make_shared<MazeNode>(nullptr);
			position.x += 1;			
			break;
		case SOUTH:
			up = std::make_shared<MazeNode>(nullptr);
			down = node;
			left = std::make_shared<MazeNode>(nullptr);
			right = std::make_shared<MazeNode>(nullptr);
			position.x -= 1;
			break;
		case EAST:
			up = std::make_shared<MazeNode>(nullptr);
			down = std::make_shared<MazeNode>(nullptr);
			left = node;
			right = std::make_shared<MazeNode>(nullptr);
			position.y += 1;
			break;
		case WEST:
			up = std::make_shared<MazeNode>(nullptr);
			down = std::make_shared<MazeNode>(nullptr);
			left = std::make_shared<MazeNode>(nullptr);
			right = node;
			position.y -= 1;
			break;
	}

	//traversal count initialized at 0 due to possibility that it has been created
	//without being traversed to.
	traversalCount = 0;

}


//Note to self: I think i'm forgetting something here
//creates a new node with a pointer to that node in the new direction
void MazeNode::append(Cardinal Direction)
{
	std::shared_ptr<std::multimap<Coordinate,
		std::shared_ptr<MazeNode> > > mazemapaccessor = Mazemap.lock();
	std::shared_ptr<MazeNode> nodeptr = mazemapaccessor->find(position)->second;



	switch(Direction)
	{

		
		case NORTH:
			std::shared_ptr<MazeNode> newNode;
				= make_shared(MazeNode(SOUTH, nodeptr, Mazemap)*);
			mazemapaccessor->insert(position(position.x+1,position.y), newNode);
			up = newNode;
			break;
		case SOUTH:
			std::shared_ptr<MazeNode> newNode;
				= make_shared(MazeNode(NORTH, nodeptr, Mazemap)*);
			mazemapaccessor->insert(position(position.x-1,position.y), newNode);
			down = newNode;
			break;
		case WEST:
			std::shared_ptr<MazeNode> newNode;
				= make_shared(MazeNode(EAST, nodeptr, Mazemap)*);
			mazemapaccessor->insert(position(position.x,position.y+1), newNode);
			left = newNode;
			break;
		case EAST:
			std::shared_ptr<MazeNode> newNode;
				= make_shared(MazeNode(WEST, nodeptr, Mazemap)*);
			mazemapaccessor->insert(position(position.x,position.y-1), newNode);
		

void MazeNode::appendAndTraverse(Cardinal Direction)
{
	append(Direction);
	traverse(direction);
}

MazeNode* MazeNode::getNodeTo(Cardinal direction)
{

}








