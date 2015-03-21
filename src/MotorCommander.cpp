#include <sstream>
#include <math.h>
#include "MotorCommander.h"
#include "Pins.h"
#include "Navigation.h"
#include "Interface.h"
#include "CommandQueue.h"

MotorCommander::MotorCommander()
{
  commandqueue::registerFunction("ChangeRoundPhase", [this](std::string PHASE)
  {
	  if(PHASE == "true") this->isFastRound = true;
	  else this->isFastRound = false;
  });
}

//return true if init was successful
bool MotorCommander::init()
{
    //Logger::logMessage("Motor Commander initialized successfully");
    //arduinoSerial = _arduinoSerial;
commandqueue::registerFunction("MOVE", [this](std::string arguments) //add argument as: "direction"
  {
    Cardinal direction;
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
    /*ss >> ori;
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
    }*/
    
    this->move(direction, navigation.getCurrentOrientation());
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
        int steps = (direction - currentOrientation);
		turn(steps*90);
   }
   
   // Update position nwith regards to the current position and the 
   // direction we are going
   switch(direction)
   {
	   case NORTH:
			navigation.changePosition(navigation.getCurrentPosition() - 7);
	   break;
	   
	   case SOUTH:
			navigation.changePosition(navigation.getCurrentPosition() + 7);
	   break;
	   
	   case EAST:
			navigation.changePosition(navigation.getCurrentPosition() - 1);
	   break;
	   
	   case WEST:
			navigation.changePosition(navigation.getCurrentPosition() + 1);
	   break;
   }
   
   if(!isFastRound()) navigation.addMove(direction);
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
    else {
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
