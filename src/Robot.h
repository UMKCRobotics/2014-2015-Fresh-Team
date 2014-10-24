#ifndef ROBOT_H
#define ROBOT_H

#include "lib/Serial/SerialStream.h"

#include "MotorCommander.h"
#include "Cardinal.h"

class Robot
{
private:
	Cardinal orientation;
	int position;
	int endPosition;
	MotorCommander motorCommander;
	Logger logger;

	SerialStream arduinoSerial;
	SerialStream PCSerial;

	int round;
	int part;

	void getRoundAndPart(void);

public:
	Robot(Logger logger);

	bool init(void);
	void go(void);

	Cardinal getOrientation(void);
};

#endif