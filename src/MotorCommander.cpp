#include <regex>
#include <math.h>
#include "MotorCommander.h"
#include "Pins.h"
#include "Navigation.h"
#include "Interface.h"

// Define pi here for sake of precision and easy of use
const float pi = 3.14159265358979f;

MotorCommander::MotorCommander()
{
  commandqueue::registerFunction("MOVE", [this](std::string arguments) //add arguments as: "direction orientation" where 
  {
    Cardinal direction;
    Cardinal orientation;

    std::regex regex("([A-Z])+");

    auto cardinalsiter = std::sregex_iterator(arguments.begin(), arguments.end(), regex);

    // Get Direction
    std::smatch match = *cardinalsiter;
    if(!match.empty())
    {
        if(match.str() == "NORTH")
        {
            direction = NORTH;
        }
        else if(match.str() == "SOUTH")
        {
            direction = SOUTH;
        }
        else if(match.str() == "EAST")
        {
            direction = EAST;
        }
        else if(match.str() == "WEST")
        {
            direction = WEST;
        }
        else
        {
            Logger::logError("The string sent to 'MOVE' does not contain an acceptable direction: " + match.str());            
        }
    }

    // Get Orientation
    match = *(++cardinalsiter);
    if(!match.empty())
    {
        if(match.str() == "NORTH")
        {
            orientation = NORTH;
        }
        else if(match.str() == "SOUTH")
        {
            orientation = SOUTH;
        }
        else if(match.str() == "EAST")
        {
            orientation = EAST;
        }
        else if(match.str() == "WEST")
        {
            orientation = WEST;
        }
        else
        {
            Logger::logError("The string sent to 'MOVE' does not contain an acceptable orientation: " + match.str());            
        }
    }
        
    this->move(direction, orientation);
  });
}

//return true if init was successful
bool MotorCommander::init(serialib* _arduinoSerial)
{
    Logger::logMessage("Motor Commander initialized successfully");
    arduinoSerial = _arduinoSerial;
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
   
        turn(x*90);
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
    arduinoSerial->WriteString(("NotifyOfAngle " + to_string(degrees)).c_str());
}

void MotorCommander::moveForward()
{
    Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
    Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

    Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
    Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}
