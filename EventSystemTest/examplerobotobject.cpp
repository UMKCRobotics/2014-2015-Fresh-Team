#include <iostream>
#include "robotbase.h"

class examplerobotobject : public RobotBase
{
	public:
		examplerobotobject()
		{

		}

		virtual void halt()
		{
			std::cout << "They Call me Gato\nI have metal joints\nBeat me up\nAnd earn 15 Silver Points\n";
		}
};