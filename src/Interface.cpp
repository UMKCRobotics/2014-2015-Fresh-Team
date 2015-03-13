#include "Interface.h"
#include "Pins.h"
#include "Logger.h"

// Sets a pin direction and will return true/false 
// depending on the success of the setting
bool Interface::setPinDirection(int pin, int direction)
{
	bool status = true;

	status = Interface::getInstance().writePinFileContents(pin, PIN_DIRECTION, direction);

	return status;
}

// Sets a pin to high or low output
// This function will check to make sure that the pin is
// actually in output mode before trying to do this
void Interface::setPinState(int pin, int state)
{
	if(Interface::getInstance().getPinDirection(pin) == PIN_DIRECTION_OUT)
	{
		// Pin is set as output thus we CAN change its state
		if(!Interface::getInstance().writePinFileContents(pin, PIN_STATE, state))
		{
			string error = "Cannot set gpio " + to_string(pin) + " state";
			Logger::logError(error);
		}
	} else {
		// Pin not set as output thus how could we change the state
		string error = "Cannot set gpio " + to_string(pin) +  "state; pin is set to input";
		Logger::logError(error);	
	}
}

// Private method for doing the behind the scenes work of
// getting the direction and state of a pin on the Udoo
// This function is used in:
//	- getPinDirection
//	- getPinState
string Interface::getPinFileContents(int pin, int property)
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
		Logger::logError(error);
	}

	return contents;
}

bool Interface::writePinFileContents(int pin, int property, int value)
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
		Logger::logError(error);
		status = false;
	}

	return status;
}

// Returns the Pins.h defined constant for the direction
// of a pin
int Interface::getPinDirection(int pin)
{
	int direction = 0;
	string str_pin = to_string(pin);
	string str_direction = Interface::getInstance().getPinFileContents(pin, PIN_DIRECTION);

	if(str_direction == "in") {
		direction = PIN_DIRECTION_IN;
	} else {
		direction = PIN_DIRECTION_OUT;
	}

	return direction;
}

// Returns the Pins.h defined constant for the current
// state of a pin
int Interface::getPinState(int pin)
{
	int state = 0;
	string str_pin = to_string(pin);
	string str_state = Interface::getInstance().getPinFileContents(pin, PIN_STATE);

	if(str_state == "1") {
		state = PIN_STATE_HIGH;
	} else {
		state = PIN_STATE_LOW;
	}

	return state;
}