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
	
	bool startupSuccessful = robot.init(); //robot.init(); TEMP

	if(!startupSuccessful)
	{
		Logger::logError("Startup failed");
	}
	else
	{
		Logger::logMessage("Startup complete; waiting for go button to be pressed");

		while(robot.getPinState(PIN_GO_BUTTON_FROM) == PIN_STATE_LOW)
		{
			// Do nothing
			usleep(50);
		}

		robot.setPinState(PIN_READY_LIGHT_VCC, PIN_STATE_LOW);
		robot.setPinState(PIN_END_LIGHT_VCC, PIN_STATE_HIGH);

		robot.go();
	}

	return 0;
}
