#include <sstream>
#include <math.h>
#include "MotorCommander.h"
#include "Pins.h"
#include "Navigation.h"
#include "Interface.h"
#include "CommandQueue.h"

MotorCommander::MotorCommander()
{
  
}

//return true if init was successful
bool MotorCommander::init()
{
	commandqueue::registerFunction("MOVE", [this](std::string arguments) //add argument as: "direction orientation"
	{
		Cardinal direction;
		Cardinal orientation;
		string ori = "";
		string dir = "";

		std::stringstream ss;
		ss << arguments;
		
		// Get Direction
		ss >> dir;
		ss >> ori;
		
		if(dir == "NORTH")
		{
			direction = NORTH;
		}
		else if(dir == "SOUTH")
		{
			direction = SOUTH;
		}
		else if(dir == "EAST")
		{
			direction = EAST;
		}
		else if(dir == "WEST")
		{
			direction = WEST;
		}
		else
		{
			Logger::logError("The string sent to 'MOVE' does not contain an acceptable direction: " + dir);            
		}
		
		if(ori == "NORTH")
		{
			orientation = NORTH;
		}
		else if(ori == "SOUTH")
		{
			orientation = SOUTH;
		}
		else if(ori == "EAST")
		{
			orientation = EAST;
		}
		else if(ori == "WEST")
		{
			orientation = WEST;
		}
		else
		{
			Logger::logError("The string sent to 'MOVE' does not contain an acceptable orientation: " + ori);            
		}
		
		this->move(direction, orientation);
	});
	
	commandqueue::registerFunction("MOVERelative", [this](std::string arguments) //add argument as: "direction orientation"
	{		
		Cardinal direction;
		Cardinal orientation;
		string relativeDirection = "";

		std::stringstream ss;
		ss << arguments;
		
		// Get Direction
		ss >> relativeDirection;
		
		Logger::logMessage("Relative Direction: "+relativeDirection);
		
		if(relativeDirection == "Right")
		{
			this->turn(-90);
		}
		else if(relativeDirection == "Front")
		{
			Logger::logMessage("I'm about to move forward");
			this->moveForward();
		}
		else if(relativeDirection == "Left")
		{
			this->turn(90);
		}
		else if(relativeDirection == "Back")
		{
			this->turn(180);
		}
		else
		{
			Logger::logError("The string sent to 'MOVERelative' does not contain an acceptable relative direction: '" + relativeDirection + "'");            
		}
	});
		
	commandqueue::registerFunction("AngleReached", [this](std::string arguments) 
	{
		this->moveForward();
	});
	
	commandqueue::registerFunction("ChangeRoundPhase", [this](std::string PHASE)
	{
		if(PHASE == "true") this->isFastRound = true;
		else this->isFastRound = false;
	});
	
	return true;
}

// Moves robot in desired cardinal direction
void MotorCommander::move(Cardinal direction, Cardinal currentOrientation)
{
	if (currentOrientation == direction)
	{
		moveForward();
	} else {
		int steps = (direction - currentOrientation);
		turn(steps*90);
	}
	
	if(!isFastRound)
	{
		switch(direction)
		{
			case NORTH:
			commandqueue::sendNewCommand(2, "ReportMove", "NORTH" );
			break;
			case SOUTH:
			commandqueue::sendNewCommand(2, "ReportMove", "SOUTH");
			break;
			case WEST:
			commandqueue::sendNewCommand(2, "ReportMove", "WEST");
			break;
			case EAST:
			commandqueue::sendNewCommand(2, "ReportMove", "EAST");
			break;
			default:
			Logger::logError("Unknown Cardinal provided in MotorCommander::move");
			break;
		}   
	}
}

void MotorCommander::turn(int degrees)
{
  if (degrees > 0){
        // left motor back, right foward
        Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
        Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

        Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
        Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);
    }
    else {
        // right motor back, left motor foward
        Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
        Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

        Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
        Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
    }

    // Send Arduino a message to notify us when we are done turning
    commandqueue::sendNewCommand(1, "SerialSend", ("NotifyOfAngle " + to_string(degrees)).c_str());
}

void MotorCommander::moveForward()
{	
    Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
    Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

    Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
    Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}

void MotorCommander::moveBackward()
{
    Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
    Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

    Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
    Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);
}

void MotorCommander::halt()
{
    Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
    Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

    Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
    Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}
