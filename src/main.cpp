#include "Robot.h"


int main(void)
{
	cout << "1\n";
	Logger::setStream(&std::cout);
	Logger::logMessage("Instantiating Robot...");
	cout << "2\n";
	Robot robot;
	Logger::logMessage("\tComplete");
	
	robot.init();

	return 0;
}
