#include <vector>
#include "Cardinal.h"

using std::vector;

class WorldSensor{ 
	public:
		virtual vector<Cardinal> computeOpenings() = 0;
}

