#ifndef MOTORCOMMANDER_H
#define MOTORCOMMANDER_H

#include "Cardinal.h"
#include "Robot.h"

class MotorCommander
{
public:
	MotorCommander();

	void move(Robot* robot, Cardinal direction);
	void turn(int degrees, Robot* robot);
	float getAngle();

private:
	void moveForward(Robot* robot);
	void moveBackward(Robot* robot);
};

#endif
