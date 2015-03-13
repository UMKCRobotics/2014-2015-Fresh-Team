#ifndef MOTORCOMMANDER_H
#define MOTORCOMMANDER_H

#include "Cardinal.h"
#include "serialib.h"

class MotorCommander
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
	void move(Cardinal direction, Cardinal currentOrientation, serialib arduinoSerial);
	void turn(int degrees, serialib arduinoSerial);

private:
	void moveForward();
};

#endif
