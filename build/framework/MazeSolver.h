#include <vector>
#include "Cardinal.h"

class MazeSolver{
	public:
		virtual Cardinal computeOpenings(vector<Cardinal> openings) = 0;
};

