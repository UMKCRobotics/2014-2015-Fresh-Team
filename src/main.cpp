#include <iostream>
#include "Robot.h"
#include "Pins.h"
#include "CommandQueue.h"

int main(void)
{
	Logger::setStream(&std::cout);
	Logger::logMessage("Instantiating Robot...");

	Robot robot;
	Logger::logMessage("\tComplete");
	
	if(robot.init())
	{
		Logger::logMessage("Startup successful");
		while(robot.loop());
		Logger::logMessage("Robot has finished")
	} else{
		Logger::logError("Startup failed");
	}
	
	return 0;
}
