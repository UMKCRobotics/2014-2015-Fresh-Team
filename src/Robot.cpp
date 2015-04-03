#include "Robot.h"
#include "Pins.h"
#include "MotorCommander.h"
#include "Interface.h"
#include "Logger.h"
#include <time.h>
#include <string>
#include "unistd.h"
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
	resetCounter = 0;
	
	Logger::logMessage("Initiating SerialListener...");

	if(serialListener.init()) {
		Logger::logMessage("\tComplete");

		successful = motorCommander->init();
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
	CQISEMPTY = false; // assumes a command will be in the queue
	state = WAITFORGO;
	
	commandqueue::registerFunction("halt", [this](std::string arguments){
		Logger::logMessage("Robot halting: " + arguments);
		this->halt();
	});

	commandqueue::registerFunction("print", [](std::string arguments){
		cout << "Asked to print: " << arguments << endl;
	});

	commandqueue::registerFunction("LineDetected", [this](std::string arguments){
		Logger::logMessage("Line detected");
		
		if(isFastRound)
		{
			// Follow navigation's directions
			// TODO: For now, let's make sure all of these systems work and do a little test
			state = WAITFORGO;
			Logger::logMessage("Fast Round");
		}
		else
		{
			// TODO: Take a picture of the wall and parse it
			Logger::logMessage("Slow Round");
		}
	});

	return successful;
}

// wait for go is continuously called until the go button is called
void Robot::waitforgo(void)
{
		
	if(!(Interface::getPinState(PIN_GO_BUTTON_FROM) == PIN_STATE_LOW))
	{
		while(!(Interface::getPinState(PIN_GO_BUTTON_FROM) == PIN_STATE_LOW)) {};
		usleep(300000); //sleep for 3 seconds to allow for release of button, this might cause problems and might need to be changed.

		Interface::setPinState(PIN_READY_LIGHT_VCC, PIN_STATE_LOW);
		Interface::setPinState(PIN_END_LIGHT_VCC, PIN_STATE_HIGH);
		//navigation.setRoundAndPart(round, part);
		Logger::logMessage("Starting at position " + to_string(navigation.getCurrentPosition()));
		
		commandqueue::sendNewCommand(1, "ChangeRound", "1");
		Logger::logMessage("Going to the next command");
		commandqueue::sendNewCommand(1, "MOVE", "WEST");


		state = RUNNING;
	}
}

void Robot::running(void)
{
	serialListener.listen(motorCommander);

	
	if(!(commandqueue::isEmpty()))
	{
		CQISEMPTY = false;
	    commandqueue::runNextCommand();
	} else if(!CQISEMPTY) {
		CQISEMPTY = true;
		Logger::logMessage("Command Queue Empty");
	}

}

void Robot::halted(void)
{
}

// go is called when the start button of the robot
// is pressed at the beginning of the part
bool Robot::loop()
{
	
	if(state != INIT && state != WAITFORGO)
	{
		// Reset the robot when the go button is pressed while running
		if(!(Interface::getPinState(PIN_GO_BUTTON_FROM) == PIN_STATE_LOW))
		{
			if(!GoButtonPressed)
			{
				resetCounter = 0;
				GoButtonPressed = true;
				iButtonPress = time(NULL); // resets to current time?
			}
			
			time_t cTime; //current time
			cTime = time(NULL); //set current time to the actual current time
			
			double secondsDiff = difftime(cTime, iButtonPress);
			Logger::logMessage("Will soft restart in " + std::to_string(3.0 - secondsDiff) + " seconds");
			
			if(secondsDiff > 3.0)
			{
				
				//purge the command queue
				Logger::logMessage("Purging waiting commands in command queue...");
				while(!commandqueue::isEmpty())
				{
					commandqueue::skipNextCommand();
				}
				Logger::logMessage("\tComplete");
				
				//send a halt command
				Logger::logMessage("Sending and executing a halt command");
				commandqueue::sendNewCommand(0, "HALT", "Soft reset");
				
				//execute the halt command
				if(!commandqueue::isEmpty())
				{
					commandqueue::runNextCommand();
				} else {
					Logger::logMessage("Halt command unable to run: command queue is empty");
				}
				
				//begin waiting for go
				Logger::logMessage("Returning to state: WAITFORGO");
				state = WAITFORGO;
				
				GoButtonPressed = false;
				
				while(!(Interface::getPinState(PIN_GO_BUTTON_FROM) == PIN_STATE_LOW)) {};
				usleep(500000); //sleep for 5 seconds to allow for release of button, this might cause problems and might need to be changed.
				
				Logger::logMessage("Waiting for go...");
			}

		} else {
			//if the button is released reset GoButtonState
			if(GoButtonPressed)
			{
				if(resetCounter >= 10)
				{
					GoButtonPressed = false;
				}
				resetCounter++;
			}
		}
	}
	
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
	//alternatively use voids instead of bools
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
