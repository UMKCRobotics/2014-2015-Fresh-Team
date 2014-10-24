#ifndef MOTORCOMMANDER_H
#define MOTORCOMMANDER_H

class MotorCommander
{
public:
	MotorCommander(Robot robot);

	void move(Cardinal direction);
	void turn(int degrees);
	float getAngle();
};

#endif
