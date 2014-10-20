#ifndef ROBOT_H
#define ROBOT_H

#include "MotorCommander.h"
#include "Cardinal.h"

class Robot
{
private:
	Cardinal orientation;
	int position;
	int endPosition;
	MotorCommander motorCommander;
	Logger logger;

	int round;
	int part;

	void getRoundAndPart(void);

public:
	Robot(Logger logger);

	void go(void);
};

#endif