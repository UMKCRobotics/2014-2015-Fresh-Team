#ifndef MOTORCOMMANDER_H
#define MOTORCOMMANDER_H

#include "Cardinal.h"

class MotorCommander
{
public:
	MotorCommander();

	void move(Cardinal currentDirection, Cardinal direction);
	void turn(int degrees);
	float getAngle();
};

#endif
