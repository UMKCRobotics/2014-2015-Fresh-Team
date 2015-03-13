#ifndef ROBOT_H
#define ROBOT_H

#include "serialib.h"
#include "Cardinal.h"
#include "Logger.h"
#include "Navigation.h"
#include "MotorCommander.h"
#include "SerialListener.h"

class Robot
{
private:
	enum State{INIT, WAITFORGO, RUNNING, HALTED};
	enum Round{ONE, TWO, THREE};
	enum Part{}; //unsure what the parts are at the moment, can be added later

	State state = INIT;
	Round round = ONE;
	//Part part;

	MotorCommander motorCommander;
	SerialListener serialListener;


	void getRoundType(void);
public:

	serialib arduinoSerial; // TEMP: Put me back into private plz :)

	Robot();
	Navigation navigation;

	bool init(void);
	bool loop();

	//state functions
	void waitforgo(void);
	void running(void);
	void halted(void);

	int getPinDirection(int pin);
	int getPinState(int pin);

	void halt();

	bool getIsFastRound();
};
#endif