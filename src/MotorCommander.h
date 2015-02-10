#ifndef MOTORCOMMANDER_H
#define MOTORCOMMANDER_H

#include "Cardinal.h"
#include "Robot.h"
#include "iRobotBase.h"

class MotorCommander : iRobotBase 
{
public:

	//state declaration for the motors
	//use as LeftMotor.setState(FORWARD); RightMotor.setState(REVERSE); 
	//as an example to turn right
	enum state{FORWARD, REVERSE, STOPPED}; 


	MotorCommander();

	bool init() override;

	void loop() override;
	void halt() override;

	//Not Sure if we'll still need these
	void move(Robot* robot, Cardinal direction);
	void turn(int degrees, Robot* robot);
	float getAngle();

	void moveForward(Robot* robot);

private:
	
	void moveBackward(Robot* robot);
};

#endif
