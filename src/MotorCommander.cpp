#include <regex>
#include <math>
#include "MotorCommander.h"
#include "Pins.h"
#include "Navigation.h"


// Define pi here for sake of precision and easy of use
const float pi = 3.14159265358979f;

MotorCommander::MotorCommander()
{

  commandqueue::register(2, "MOVE", [this](std::string arguments) //add arguments as: "direction orientation" where 
  {    
	
	
	
	
	
	
	std::string direction = "NORTH";
	std::string orientation = "NORTH";
	
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


  /*
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
  */
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
