#ifndef ROBOT_H
#define ROBOT_H

#include <time.h>
#include "serialib.h"
#include "Navigation.h"
#include "MotorCommander.h"
#include "SerialListener.h"

class Robot
{
private:
	enum State{INIT, WAITFORGO, RUNNING, HALTED};
	enum Round{ONE, TWO, THREE};
	enum Part{}; //unsure what the parts are at the moment, can be added later

	bool GoButtonPressed;
	time_t iButtonPress; //intial button press time
	double HoldTime; //amount of time button was held down
	int resetCounter = 0; //reset counter thing
	
	bool CQISEMPTY;
	bool isFastRound;
	State state = INIT;
	Round round = ONE;
	//Part part;



	MotorCommander* motorCommander;
	SerialListener serialListener;

	void getRoundType(void);
public:
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
