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

    auto cardinalsiter = std::sregex_iterator(teststring.begin(), teststring.end(), regex);

    std::smatch match = *cardinalsiter;
    if(!match.empty())
    {

      switch(match.str())
      {
        case "NORTH":
          direction = NORTH;
          break;
        case "SOUTH":
          direction = SOUTH;
          break;
        case "EAST":
          direction = EAST;
          break;
        case "WEST":
          direction = WEST;
          break;
        default:
          Logger::logError("The string sent to 'MOVE' does not contain an acceptable direction: " + match.str());
          return;
      } 

    }
    match = *(++cardinalsiter);

    if(!match.empty())
    {
      switch(match.str())
      {
        case "NORTH":
          orientation = NORTH;
          break;
        case "SOUTH":
          orientation = SOUTH;
          break;
        case "EAST":
          orientation = EAST;
          break;
        case "WEST":
          orientation = WEST;
          break;
        default:
          Logger::logError("The string sent to 'MOVE' does not contain an acceptable orientation: " + match.str());
          return;
      }
    }
    this.move(direction, orientation);
  });
}


//return true if init was successful
bool MotorCommander::init()
{

  Logger::logMessage("Motor Commander initialized successfully");
  return true;
}

// Moves robot in desired cardinal direction
void MotorCommander::move(Cardinal direction, Cardinal currentOrientation, serialib arduinoSerial)
{
  if (currentOrientation == direction){
    moveForward();
  }
  else {
        int x = (direction - currentOrientation);
   
        turn(x*90, arduinoSerial);
   }
}

void MotorCommander::turn(int degrees, serialib arduinoSerial)
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
    arduinoSerial.WriteString(("NotifyOfAngle " + to_string(degrees)).c_str());
}

void MotorCommander::moveForward()
{
    Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
    Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

    Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
    Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}
