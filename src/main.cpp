#include "Robot.h"
#include "MotorCommander.h"
#include "Pins.h"

int main(void)
{
	Logger::setStream(&std::cout);
	Logger::logMessage("Instantiating Robot...");

	Robot robot;
	Logger::logMessage("\tComplete");
	
	Logger::logMessage("Instantiating MotorCommander...");
	MotorCommander motorCommander;
	Logger::logMessage("\tComplete");
	
	bool startupSuccessful = robot.init();

	if(!startupSuccessful)
	{
		Logger::logError("Startup failed");
	}
	else
	{
		Logger::logMessage("Startup complete; waiting for go button to be pressed");

		while(robot.getPinState(PIN_GO_BUTTON) == PIN_STATE_LOW)
		{
			// Do nothing
		}

		robot.go();
	}

	return 0;
}
