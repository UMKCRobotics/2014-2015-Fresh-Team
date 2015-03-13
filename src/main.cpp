#include <iostream>
#include "Robot.h"
#include "Pins.h"
#include "CommandQueue.h"

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
		Logger::logMessage("Startup successful");
		while(robot.loop());
		Logger::logMessage("Robot has finished")
	}
	
	return 0;
}
