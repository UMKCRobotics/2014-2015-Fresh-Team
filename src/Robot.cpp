#include "Robot.h"

Robot::Robot(Logger logger)
{
	orientation = NORTH;
	this.logger = logger;
}

// go is called when the start button of the robot
// is pressed at the beginning of the part
void Robot::go(void)
{
	logger.logMessage("Go Button Pressed");

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

	logger.logMessage("Starting at position ");
}

// This function gets the round and part from the potentiometers
// connected to the board using the Arduino side
void Robot::getRoundAndPart(void)
{
	logger.logMessage("Getting Round and Part");

	// TODO: get round and part values from the Arduino side

	string str_round = ""; // TODO: Dummy values; convert received integers to strings
	string str_part = "";

	logger.logMessage("Selected Round: " + str_round);
	logger.logMessage("Selected Part: "  + str_part);
}

Cardinal Robot::getOrientation(void)
{
	return orientation;
}