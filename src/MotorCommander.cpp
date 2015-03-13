#include <regex>
#include <math.h>
#include "MotorCommander.h"
#include "Pins.h"
#include "Navigation.h"


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
void MotorCommander::move(Cardinal direction, Cardinal orientation)
{

  if (robot->navigation.getOrientation() == direction){
    moveForward(robot);
  }
  else {
      int x = (direction - robot->navigation.getOrientation());
   
      if (x == 0){
        moveForward(robot);
      }
      else
      {
        turn(x*90, robot);
      }
   }
  
}

void MotorCommander::turn(int degrees, Robot* robot)
{
  if (degrees < 0){
    // left motor back, right foward
    robot->setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
    robot->setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

    robot->setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
    robot->setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
  }
 else{
  // right motor back, left motor foward
  robot->setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
  robot->setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

  robot->setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);
 }
  
  float desiredAngle = getAngle() + degrees;
  
  while(fabs(getAngle() - desiredAngle) >= 2)
  {
    // Nothing
  }
  
  // Stop turning
  robot->setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

  robot->setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}

void MotorCommander::moveForward(Robot* robot)
{
  robot->setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
  robot->setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

  robot->setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
  robot->setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}

void MotorCommander::moveBackward(Robot* robot)
{
  robot->setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

  robot->setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);
}

// Returns the angle the robot currently is in degrees
float MotorCommander::getAngle()
{
	float heading;
	float hx = 0; // Heading X
	float hy = 0; // Heading Y

	if (hy > 0)
	{
		heading = 90 - (atan(hx / hy) * (180 / pi));
	}
	else if (hy < 0)
	{
		heading = - (atan(hx / hy) * (180 / pi));
	}
	else // hy = 0
	{
		if (hx < 0) heading = 180;
		else heading = 0;
	}

	return heading;
}
