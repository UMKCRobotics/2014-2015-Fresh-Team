#ifndef MOTOR_H
#define MOTOR_H

#include "Robot.h"
#include "iRobotBase.h"

class Motor : iRobotBase
{
public:

	//state definitions
	enum state{FORWARD, REVERSE, STOPPED}; 

	state setState();

	Motor();

	bool init() override;
	void loop() override;
	void halt() override;

private:
	state State;
};

#endif