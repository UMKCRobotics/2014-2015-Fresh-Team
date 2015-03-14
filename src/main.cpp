#include <iostream>
#include "Robot.h"
#include "Pins.h"
#include "SerialListener.h"
#include "Interface.h"
#include "Logger.h"

int main(void)
{
	Logger::setStream(&std::cout);
	Logger::logMessage("Starting up...");

	Robot robot;
	
	bool robotStartupSuccessful = robot.init(); //robot.init(); TEMP

	if(!robotStartupSuccessful)
	{
		Logger::logError("Startup failed");
	}
	else
	{
		Logger::logMessage("Startup complete; waiting for go button to be pressed");

		while(Interface::getPinState(PIN_GO_BUTTON_FROM) == PIN_STATE_LOW)
		{
			// Do nothing
			usleep(50);
		}

		Interface::setPinState(PIN_READY_LIGHT_VCC, PIN_STATE_LOW);

		while(robot.loop());

		Interface::setPinState(PIN_END_LIGHT_VCC, PIN_STATE_HIGH);
	}

	return 0;
}
