#ifndef ROBOT_H
#define ROBOT_H

#include "serialib.h"
#include "Cardinal.h"
#include "Logger.h"

class Robot
{
private:
	Cardinal orientation;
	int position;
	int endPosition;
	Logger logger;

	int round;
	int part;

	void getRoundAndPart(void);
	string getPinFileContents(int pin, int property);
	bool writePinFileContents(int pin, int property, int value);
public:
	serialib arduinoSerial; // TEMP: Put me back into private plz :)

	Robot();

	bool init(void);
	void go(void);

	Cardinal getOrientation(void);

	int getPinDirection(int pin);
	int getPinState(int pin);

	void setPinState(int pin, int state);
	bool setPinDirection(int pin, int state);
};
#endif