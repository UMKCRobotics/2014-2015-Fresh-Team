//This interface class should be implemented by Robot Object parts

#ifndef IROBOTBASE_H
#define IROBOTBASE_H

#include <iostream>

class iRobotBase
{
public:
	virtual ~iRobotBase(){};

	virtual bool init(){}; //initializer

	virtual void halt(){}; //override this for halt functionality
	virtual bool loop(){}; //override this for standard looping

	/**more core generic callbacks can be added in the future**/


};

#endif