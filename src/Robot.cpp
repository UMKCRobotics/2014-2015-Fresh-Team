#include "Robot.h"
#include "Pins.h"

#include <iostream>
#include <fstream>
using namespace std;

Robot::Robot()
{
	
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

	Logger::logMessage("Initiating Arduino SerialStream...");
	initStatus = arduinoSerial.Open("/dev/ttymxc3", 9600);

	if(initStatus == 1) {
		Logger::logMessage("\tComplete");
	} else {
		Logger::logMessage("\tFailed to Open");
		successful = false;
	}

	if(successful)
	{
		Logger::logMessage("Configuring GPIO Directions...");
		if(!setPinDirection(PIN_GO_BUTTON_TO, PIN_DIRECTION_OUT)) successful = false;
		if(!setPinDirection(PIN_GO_BUTTON_FROM, PIN_DIRECTION_IN)) successful = false;
		if(!setPinDirection(PIN_GO_BUTTON_VCC, PIN_DIRECTION_OUT)) successful = false;
		if(!setPinDirection(PIN_GO_BUTTON_GND, PIN_DIRECTION_OUT)) successful = false;

		if(!setPinDirection(PIN_READY_LIGHT_VCC, PIN_DIRECTION_OUT)) successful = false;
		if(!setPinDirection(PIN_END_LIGHT_VCC, PIN_DIRECTION_OUT)) successful = false;
		if(!setPinDirection(PIN_STATUS_LIGHTS_GND, PIN_DIRECTION_OUT)) successful = false;

		if(successful) Logger::logMessage("\tComplete");
		else Logger::logMessage("\tFailed");
	}

	if(successful)
	{
		Logger::logMessage("Configuring Default GPIO Outputs...");
		setPinState(PIN_GO_BUTTON_TO, PIN_STATE_LOW);
		setPinState(PIN_GO_BUTTON_VCC, PIN_STATE_HIGH);
		setPinState(PIN_GO_BUTTON_GND, PIN_STATE_LOW);

		setPinState(PIN_READY_LIGHT_VCC, PIN_STATE_HIGH);
		setPinState(PIN_END_LIGHT_VCC, PIN_STATE_LOW);
		setPinState(PIN_STATUS_LIGHTS_GND, PIN_STATE_LOW);
		
		Logger::logMessage("\tComplete");
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

	navigation.setRoundAndPart(round, part);

	Logger::logMessage("Starting at position " + to_string(navigation.getCurrentPosition()));
}

// This function gets the round and part from the potentiometers
// connected to the board using the Arduino side
// Returns INVALID when the received message from the Arduino is flawed
// or just not correct. If the function does return INVALID, the Robot class 
// should call it again
void Robot::getRoundAndPart(void)
{
	Logger::logMessage("Getting Round and Part...");

	// TODO: get round and part values from analog pins

	string response = "1:1"; 	// Will get them in the format
								// round:part
								// Navigation class will hold these for  us

	// parse the round and part
	string str_round, str_part = "";
	str_round = response.substr(0, response.find(":"));
	str_part = response.substr(response.find(":")+1);

	if(!isdigit(str_round.at(0)) && !isdigit(str_part.at(0)))
	{
		// TODO: request round and part again
	}

	round = atoi(str_round.c_str());
	part = atoi(str_part.c_str());
}

// Returns the Pins.h defined constant for the direction
// of a pin
int Robot::getPinDirection(int pin)
{
	int direction = 0;
	string str_pin = to_string(pin);
	string str_direction = getPinFileContents(pin, PIN_DIRECTION);

	if(str_direction == "in") {
		direction = PIN_DIRECTION_IN;
	} else {
		direction = PIN_DIRECTION_OUT;
	}

	return direction;
}

// Returns the Pins.h defined constant for the current
// state of a pin
int Robot::getPinState(int pin)
{
	int state = 0;
	string str_pin = to_string(pin);
	string str_state = getPinFileContents(pin, PIN_STATE);

	if(str_state == "1") {
		state = PIN_STATE_HIGH;
	} else {
		state = PIN_STATE_LOW;
	}

	return state;
}

// Sets a pin direction and will return true/false 
// depending on the success of the setting
bool Robot::setPinDirection(int pin, int direction)
{
	bool status = true;

	status = writePinFileContents(pin, PIN_DIRECTION, direction);

	return status;
}

// Sets a pin to high or low output
// This function will check to make sure that the pin is
// actually in output mode before trying to do this
void Robot::setPinState(int pin, int state)
{
	if(getPinDirection(pin) == PIN_DIRECTION_OUT)
	{
		// Pin is set as output thus we CAN change its state
		writePinFileContents(pin, PIN_STATE, state);

		// TODO: Check if the state was successfully set?
	} else {
		// Pin not set as output thus how could we chance the state
			
	}
}

// Private method for doing the behind the scenes work of
// getting the direction and state of a pin on the Udoo
// This function is used in:
//	- getPinDirection
//	- getPinState
string Robot::getPinFileContents(int pin, int property)
{
	string contents = "";
	string str_pin = to_string(pin);
	string str_property = "";
	string filePath = "/sys/class/gpio/gpio" + str_pin;

	// Convert from the pin property's integer value to a string
	switch(property)
	{
		case PIN_DIRECTION:
			str_property = "direction";
		break;

		case PIN_STATE:
			str_property = "value";
		break;
	};

	// Append the path of what we want from the pin
	filePath = filePath + "/" + str_property;

	fstream pinFile;
	pinFile.open(filePath, fstream::in);

	if(pinFile.is_open())
	{
		getline(pinFile, contents);

		pinFile.close();
	} else {
		string error = "Could not read " + str_property + " from pin " + str_pin + " file";
		logger.logError(error);
	}

	return contents;
}

bool Robot::writePinFileContents(int pin, int property, int value)
{
	bool status = true;
	string str_pin = to_string(pin);
	string filePath = "/sys/class/gpio/gpio" + str_pin;
	string str_property = "";
	string str_value = "";

	// Convert the property to a string
	switch(property)
	{
		case PIN_DIRECTION:
			str_property = "direction";
		break;

		case PIN_STATE:
			str_property = "value";
		break;
	};

	// Convert the value to a string
	switch(value)
	{
		case PIN_STATE_LOW:
			str_value = "0";
		break;

		case PIN_STATE_HIGH:
			str_value = "1";
		break;

		case PIN_DIRECTION_IN:
			str_value = "in";
		break;

		case PIN_DIRECTION_OUT:
			str_value = "out";
		break;
	};

	// Append the path of what we want from the pin
	filePath = filePath + "/" + str_property;

	// Now open the pin file up and try to write the value
	// to it
	fstream pinFile;
	pinFile.open(filePath, fstream::out);

	if(pinFile.is_open())
	{
		pinFile << str_value;

		pinFile.close();
	} else {
		string error = "Could not write " + str_value + " to " + str_property + " of pin " + str_pin + " file";
		logger.logError(error);
		status = false;
	}

	return status;
}
