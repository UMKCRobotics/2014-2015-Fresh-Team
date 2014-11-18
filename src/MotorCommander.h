#ifndef MOTORCOMMANDER_H
#define MOTORCOMMANDER_H

#include "Cardinal.h"
#include "Robot.h"

class MotorCommander
{
private:
	
public:
	MotorCommander();

	void move(Cardinal direction);
	void turn(int degrees);
	float getAngle();
};

#endif
