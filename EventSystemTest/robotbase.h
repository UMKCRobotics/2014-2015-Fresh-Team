#ifndef ROBOTBASE_H
#define ROBOTBASE_H

//class to be implemented by robot classes for standard callback functions
#include <iostream>

class RobotBase
{
public:
	virtual ~RobotBase(){};

	virtual void halt(){}; //override this for halt functionality
	virtual void driveForward(){}; //override this for driveForward functionality
	virtual void turnLeft(){}; //override this for turning left functionality
	virtual void turnRight(){}; //override this for turning right functionality

	virtual bool loop(){}; //override this for standard looping

	/**more core generic callbacks can be added in the future**/


};
#endif