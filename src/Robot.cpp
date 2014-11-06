#include "Robot.h"
#include <iostream>
Robot::Robot()
{
	orientation = NORTH;
	Logger::setStream(&std::cout);
}


// Initiation function for all main robot components
// will be called before the robot begins working 
// and after the class has been initiated.
// The boolean return status will determine whether or 
// not the robot will actually run (as well as set status lights)
bool Robot::init(void)
{
	bool successful = true;
	int initStatus = 0;


	Logger::logMessage("Initiating PC SerialStream...");
	initStatus = PCSerial.Open("dev/ttsy0", 115200);

	if(initStatus == 1) {
		Logger::logMessage("\tComplete");
	} else {
		Logger::logMessage("\tFailed to Open");
		successful = false;
	}

	Logger::logMessage("Initiating Arduino SerialStream...");
	initStatus = arduinoSerial.Open("/dev/ttymxc3", 9600);

	if(initStatus == 1) {
		Logger::logMessage("\tComplete");
	} else {
		Logger::logMessage("\tFailed to Open");
		successful = false;
	}

	// TODO: Any other needed initiation

	return successful;
}

// go is called when the start button of the robot
// is pressed at the beginning of the part
void Robot::go(void)
{
	Logger::logMessage("Go Button Pressed");

	getRoundAndPart();

	if(round == 1)
	{
		position = 48;
		endPosition = 9;
	}
	else if(round == 2) 
	{
		position = 48;
		endPosition = 1;
	}
	else if(round == 3)
	{
		position = 49;
		endPosition = 1;
	}

	Logger::logMessage("Starting at position ");
}

// This function gets the round and part from the potentiometers
// connected to the board using the Arduino side
void Robot::getRoundAndPart(void)
{
	Logger::logMessage("Getting Round and Part");

	// TODO: get round and part values from the Arduino side

	string str_round = ""; // TODO: Dummy values; convert received integers to strings
	string str_part = "";

	Logger::logMessage("Selected Round: " + str_round);
	Logger::logMessage("Selected Part: "  + str_part);
}

Cardinal Robot::getOrientation(void)
{
	return orientation;
}