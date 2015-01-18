#include <map>
#include <memory>
#include "cardinal.h"
#include "coordinate.h"

enum nodeType(START, PASSAGE, TERMINAL);

class MazeNode
{
public:
	
	/**constructor**/
	MazeNode(
		int Location, Cardinal EntryDirection, std::weak_ptr<MazeNode> previous, nodeType Type);

	/**positive actions**/
	void append(MazeNode nextNode);
	std::shared_ptr<MazeNode> traverse();
	std::shared_ptr<MazeNode> appendAndTraverse(MazeNode nextNode);

	/**negative actions**/
	std::shared_ptr<MazeNode> backstepAndDelete();
	std::shared_ptr<MazeNode> backstep();

	void deleteNext();

	/**accessors**/
	Cardinal getEntryDirection();
	int getlocation();

private:
	std::shared_ptr<MazeNode> nextNode;
	std::weak_ptr<MazeNode> previousNode;

	Cardinal entrydirection;
	nodeType type;
	int traversalCount;
	int location; //may change this system

};

