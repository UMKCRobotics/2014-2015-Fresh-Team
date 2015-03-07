#ifndef ROBOT_H
#define ROBOT_H

#include "serialib.h"
#include "Navigation.h"
#include "MotorCommander.h"

class Robot
{
private:
	MotorCommander motorCommander;
	bool isFastRound;

	void getRoundType(void);
public:
	Robot();
	Navigation navigation;

	bool init(void);
	void go();

	bool getIsFastRound();
};
#endif