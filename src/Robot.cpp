#include "Robot.h"
#include "Pins.h"
#include "iRobotBase.h"
#include "Interface.h"

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
	
	//initiate motorCommander
	Logger::logMessage("Instantiating MotorCommander...");
	motorCommander = new MotorCommander();
	Logger::logMessage("\tComplete");

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

		// Go Button
		if(!Interface::setPinDirection(PIN_GO_BUTTON_TO, PIN_DIRECTION_OUT)) successful = false;
		if(!Interface::setPinDirection(PIN_GO_BUTTON_FROM, PIN_DIRECTION_IN)) successful = false;
		if(!Interface::setPinDirection(PIN_GO_BUTTON_VCC, PIN_DIRECTION_OUT)) successful = false;
		if(!Interface::setPinDirection(PIN_GO_BUTTON_GND, PIN_DIRECTION_OUT)) successful = false;

		// Status Lights
		if(!Interface::setPinDirection(PIN_READY_LIGHT_VCC, PIN_DIRECTION_OUT)) successful = false;
		if(!Interface::setPinDirection(PIN_END_LIGHT_VCC, PIN_DIRECTION_OUT)) successful = false;
		if(!Interface::setPinDirection(PIN_STATUS_LIGHTS_GND, PIN_DIRECTION_OUT)) successful = false;

		// Left Motor
		if(!Interface::setPinDirection(PIN_MOTOR_L1, PIN_DIRECTION_OUT)) successful = false;
		if(!Interface::setPinDirection(PIN_MOTOR_L2, PIN_DIRECTION_OUT)) successful = false;

		// Right Motor
		if(!Interface::setPinDirection(PIN_MOTOR_L3, PIN_DIRECTION_OUT)) successful = false;
		if(!Interface::setPinDirection(PIN_MOTOR_L4, PIN_DIRECTION_OUT)) successful = false;

		if(successful) Logger::logMessage("\tComplete");
		else Logger::logMessage("\tFailed");
	}

	if(successful)
	{
		Logger::logMessage("Configuring Default GPIO Outputs...");

		// Go Button
		Interface::setPinState(PIN_GO_BUTTON_TO, PIN_STATE_LOW);
		Interface::setPinState(PIN_GO_BUTTON_VCC, PIN_STATE_HIGH);
		Interface::setPinState(PIN_GO_BUTTON_GND, PIN_STATE_LOW);

		// Status Lights
		Interface::setPinState(PIN_READY_LIGHT_VCC, PIN_STATE_HIGH);
		Interface::setPinState(PIN_END_LIGHT_VCC, PIN_STATE_LOW);
		Interface::setPinState(PIN_STATUS_LIGHTS_GND, PIN_STATE_LOW);

		// Left Motor
		Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
		Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);
		
		// Right Motor
		Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
		Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);

		Logger::logMessage("\tComplete");
	}

	//Begin Serial Listener
	serialListener = new serialListener(arduinoSerial);

	// TODO: Any other needed initiation
	if(!successful) return successful;

	State = WAITFORGO;

	commandqueue::registerFunction(0, "halt", [this](std::string arguments){
			Logger::logMessage("Robot halting: " + arguments);
		this->halt();
	});

	commandqueue::registerFunction(99, "print", [](std::string arguments){
		cout << "Asked to print: " << arguments << endl;
	});

	return successful;
}

// wait for go is continuously called until the go button is called
void Robot::waitforgo(void)
{
	getRoundAndPart();

	if(!(getPinState(PIN_GO_BUTTON_FROM) == PIN_STATE_LOW))
	{
		Logger::logMessage("Go Button Pressed");
		Interface::setPinState(PIN_READY_LIGHT_VCC, PIN_STATE_LOW);
		Interface::setPinState(PIN_END_LIGHT_VCC, PIN_STATE_HIGH);
		//navigation.setRoundAndPart(round, part);
		Logger::logMessage("Starting at position " + to_string(navigation.getCurrentPosition()));
		state = RUNNING;
	}

}

void Robot::running(void)
{
	serialListener.listen();
	CommandQueue::runNextCommand();

}

void Robot::halted(void)
{

}


//loop is continuously called after init and go as long as no errors occur
void Robot::loop()
{
	switch(state)
	{
		case WAITFORGO:

		waitforgo(void);

		break;

		case RUNNING:

		running(void);

		break;

		case HALTED:

		halted(void);

		break;
	}
}

void Robot::halt()
{

	state = HALTED;
}



// This function gets the round and part from the potentiometers
// connected to the board using the Arduino side
// Returns INVALID when the received message from the Arduino is flawed
// or just not correct. If the function does return INVALID, the Robot class 
// should call it again
void Robot::getRoundAndPart(void)
{
	if(Interface::getPinState(PIN_ROUND_TYPE_SWITCH) == PIN_STATE_LOW)
	{
		isFastRound = true;
	}
	else
	{
		isFastRound = false;
	}
}

bool Robot::getIsFastRound()
{
	return isFastRound;
}
