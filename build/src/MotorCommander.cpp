#include <sstream>
#include <math.h>
#include "MotorCommander.h"
#include "Pins.h"
#include "Navigation.h"
#include "Interface.h"
#include "CommandQueue.h"

// Define pi here for sake of precision and easy of use
const float pi = 3.14159265358979f;

MotorCommander::MotorCommander()
{
  
}

//return true if init was successful
bool MotorCommander::init()
{
    //Logger::logMessage("Motor Commander initialized successfully");
    //arduinoSerial = _arduinoSerial;
commandqueue::registerFunction("MOVE", [this](std::string arguments) //add arguments as: "direction orientation" where 
  {
    Cardinal direction;
    Cardinal orientation;
    string dir = "";
    string ori = "";
    std::stringstream ss;
    ss << arguments;

    // Get Direction
    ss >> dir;
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

    // Get Orientation
    ss >> ori;
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
  
  commandqueue::registerFunction("AngleReached", [this](std::string arguments){
	 this->moveForward(); 
  });
    return true;
}

// Moves robot in desired cardinal direction
void MotorCommander::move(Cardinal direction, Cardinal currentOrientation)
{
  if (currentOrientation == direction){
    moveForward();
  }
  else {
        int x = (direction - currentOrientation);
        
        if(abs(x) == 180)
        {
			moveBackward();
		}
		else
		{
			turn(x*90);
		}
   }
}

void MotorCommander::turn(int degrees)
{
  if (degrees > 0){
        // left motor back, right foward
        Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
        Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

        Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
        Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
    }
    else{
        // right motor back, left motor foward
        Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
        Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

        Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
        Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);
    }

    // Send Arduino a message to notify us when we are done turning
    //arduinoSerial->WriteString(("NotifyOfAngle " + to_string(degrees)).c_str());
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
    Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
    Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

    Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
    Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);
}
