#include "Robot.h"
#include "Pins.h"

int main(void)
{
	Logger::setStream(&std::cout);
	Logger::logMessage("Instantiating Robot...");

	Robot robot;
	Logger::logMessage("\tComplete");
	
	//Logger::logMessage("Instantiating MotorCommander...");
	//MotorCommander motorCommander; 
	//Logger::logMessage("\tComplete");
	//motor commander should be called at robot init


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
