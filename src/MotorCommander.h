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

	bool init(serialib* _arduinoSerial);

	void loop();
	void halt();

	//Not Sure if we'll still need these
	void move(Cardinal direction, Cardinal currentOrientation);
	void turn(int degrees);

private:
	void moveForward();
	serialib* arduinoSerial;
};

#endif
