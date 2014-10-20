#ifndef MOTORCOMMANDER_H
#define MOTORCOMMANDER_H

class MotorCommander
{
public:
	MotorCommander();

	void move(int cardinalDirection);
	void turn(int degrees);
	float getAngle();
};

#endif
