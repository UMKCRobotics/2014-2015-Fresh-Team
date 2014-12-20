#ifndef ROBOT_H
#define ROBOT_H

#include "serialib.h"
#include "Cardinal.h"
#include "Logger.h"
#include "Navigation.h"

class Robot
{
private:
	Logger logger;

	int round;
	int part;

	void getRoundAndPart(void);
	string getPinFileContents(int pin, int property);
	bool writePinFileContents(int pin, int property, int value);
public:
	serialib arduinoSerial; // TEMP: Put me back into private plz :)

	Robot();
	Navigation navigation;

	bool init(void);
	void go(void);

	int getPinDirection(int pin);
	int getPinState(int pin);

	void setPinState(int pin, int state);
	bool setPinDirection(int pin, int state);
};
#endif