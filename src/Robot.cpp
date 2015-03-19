#include "Robot.h"
#include "Pins.h"
#include "MotorCommander.h"
#include "Interface.h"
#include "Logger.h"
#include <string>
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

	Logger::logMessage("Initiating SerialListener...");

	if(serialListener.init()) {
		Logger::logMessage("\tComplete");

		successful = motorCommander->init(serialListener.getSerialStream());
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

	// TODO: Any other needed initiation

	if(!successful) return successful;

	state = WAITFORGO;
	
	commandqueue::registerFunction("halt", [this](std::string arguments){
		Logger::logMessage("Robot halting: " + arguments);
		this->halt();
	});

	commandqueue::registerFunction("print", [](std::string arguments){
		cout << "Asked to print: " << arguments << endl;
	});

	commandqueue::registerFunction("LineDetected", [this](std::string arguments){
		if(isFastRound)
		{
			// Follow navigation's directions
			// TODO: For now, let's make sure all of these systems work and do a little test
			state = WAITFORGO;
		}
		else
		{
			// TODO: Take a picture of the wall and parse it
		}
	});

	return successful;
}

// wait for go is continuously called until the go button is called
void Robot::waitforgo(void)
{
	if(!(Interface::getPinState(PIN_GO_BUTTON_FROM) == PIN_STATE_LOW))
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
	serialListener.listen(motorCommander);
	commandqueue::runNextCommand();

}

void Robot::halted(void)
{
}

// go is called when the start button of the robot
// is pressed at the beginning of the part
bool Robot::loop()
{

	switch(state)
	{
		case INIT:
		//init should have been handled before entering this loop...
		break;

		case WAITFORGO:

		waitforgo();

		break;

		case RUNNING:

		running();

		break;

		case HALTED:

		halted();

		break;
	}
	return true; 
	//todo: boolean is required to end loop
	//fix the code so it uses bools insted of voids
}

void Robot::halt()
{
	motorCommander->halt();
	state = HALTED;
}

void Robot::getRoundType(void)
{
	if(Interface::getPinState(PIN_FAST_ROUND) == PIN_STATE_LOW)
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
