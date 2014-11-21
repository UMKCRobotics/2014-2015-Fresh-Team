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
		// Logger::logMessage("Startup complete; waiting for go button to be pressed");

		// while(robot.getPinState(PIN_GO_BUTTON) == PIN_STATE_LOW)
		// {
		// 	// Do nothing
		// 	usleep(50000);
		// }

		// robot.go();

		// TEMP: Code for testing communication with the Arduino side
		char* received;
		int readStatus = 0;

		while(1)
		{
			readStatus = robot.arduinoSerial.ReadString(received, "\r\n", 100);

			if(readStatus > 0)
			{
				Logger::logMessage("Data!");
				Logger::logMessage(received);
			}
			else if(readStatus == 0)
			{
				Logger::logMessage("Timeout Reached");
			}
			else if(readStatus == -1)
			{
				Logger::logMessage("Error while setting timeout");
			}
			else if(readStatus == -2)
			{
				Logger::logMessage("Error while reading byte");
			}
			else if(readStatus == -3)
			{
				Logger::logMessage("Byte maximum is reached");
				Logger::logMessage(received);
			}
		}
	}

	return 0;
}
