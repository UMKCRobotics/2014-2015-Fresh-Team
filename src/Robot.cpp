#include "Robot.h"

Robot::Robot()
{
	orientation = NORTH;
}

Robot::Robot(Logger _logger)
{
	orientation = NORTH;
	logger = _logger;
}

// Initiation function for all main robot components
// will be called before the robot begins working 
// and after the class has been initiated.
// The boolean return status will determine whether or 
// not the robot will actually run (as well as set status lights)
bool Robot::init(void)
{
	bool successful = true;

	logger.logMessage("Initiating PC SerialStream...");
	PCSerial.Open("/dev/ttyUSB0");

	if(PCSerial.IsOpen()) {
		logger.logMessage("\tSuccessfully Opened");

		logger.logMessage("\tSetting character size to 8")
		PCSerial.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);

		logger.logMessage("\tSetting baud rate to 11520");
		PCSerial.SetBaudRate(SerialStreamBuf::BAUD_11520) ;

		logger.logMessage("\tSetting number of stop bits to 1");
		PCSerial.SetNumOfStopBits(1);

		logger.logMessage("\tSetting parity type to odd");
		PCSerial.SetParity(SerialStreamBuf::PARITY_ODD);

		logger.logMessage("\tSetting flow control to hard");
		PCSerial.SetFlowControl(SerialStreamBuf::FLOW_CONTROL_HARD);

		logger.logMessage("\tComplete");
	} else {
		logger.logMessage("\tFailed to Open");
		successful = false;
	}

	logger.logMessage("Initiating Arduino SerialStream...");
	arduinoSerial.Open("/dev/ttymxc3"); 

	if(arduinoSerial.IsOpen()) {
		logger.logMessage("\tSuccessfully Opened");

		logger.logMessage("\tSetting character size to 8")
		arduinoSerial.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);

		logger.logMessage("\tSetting baud rate to 9600");
		arduinoSerial.SetBaudRate(SerialStreamBuf::BAUD_9600) ;

		logger.logMessage("\tSetting number of stop bits to 1");
		arduinoSerial.SetNumOfStopBits(1);

		logger.logMessage("\tSetting parity type to odd");
		arduinoSerial.SetParity(SerialStreamBuf::PARITY_ODD);

		logger.logMessage("\tSetting flow control to hard");
		arduinoSerial.SetFlowControl(SerialStreamBuf::FLOW_CONTROL_HARD);

		logger.logMessage("\tComplete");
	} else {
		logger.logMessage("\tFailed to Open");
		successful = false;
	}

	// TODO: Any other needed initiation

	return successful;
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