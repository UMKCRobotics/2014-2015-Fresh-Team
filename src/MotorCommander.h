#ifndef MOTORCOMMANDER_H
#define MOTORCOMMANDER_H

#include "Cardinal.h"
#include "Robot.h"

class MotorCommander
{
private:
	Robot* robot;
public:
	MotorCommander(Robot &_robot);

	void move(Cardinal direction);
	void turn(int degrees);
	float getAngle();
};

#endif
