#ifndef ROBOT_H
#define ROBOT_H

#include "serialib.h"

#include "MotorCommander.h"
#include "Cardinal.h"
#include "Logger.h"

class Robot
{
private:
	Cardinal orientation;
	int position;
	int endPosition;
	MotorCommander motorCommander;
	Logger logger;

	serialib PCSerial;
	serialib arduinoSerial;

	int round;
	int part;

	void getRoundAndPart(void);

public:
	Robot();


	bool init(void);
	void go(void);

	Cardinal getOrientation(void);
};

#endif