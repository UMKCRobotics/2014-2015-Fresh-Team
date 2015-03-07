#ifndef MOTORCOMMANDER_H
#define MOTORCOMMANDER_H

#include "Cardinal.h"

class MotorCommander
{
public:
	MotorCommander();

	void move(Cardinal currentOrientation, Cardinal direction);
	void turn(int degrees);
	void moveForward();
	void halt();

private:
	void moveBackward();
};

#endif
