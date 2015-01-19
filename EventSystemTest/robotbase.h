//class to be implemented by robot classes that need access to the commandqueue
#pragma once
#include <iostream>

class RobotBase
{
public:
	virtual ~RobotBase(){};

	virtual void halt(){}; //override this for halt functionality
	virtual void driveForward(){}; //override this for driveForward functionality
	virtual void turnLeft(){}; //override this for turning left functionality
	virtual void turnRight(){}; //override this for turning right functionality

	/**more core generic callbacks can be added in the future**/


};