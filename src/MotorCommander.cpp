#include <math.h>
#include "MotorCommander.h"
#include "Pins.h"
#include "Navigation.h"


// Define pi here for sake of precision and easy of use
const float pi = 3.14159265358979f;

MotorCommander::MotorCommander()
{
  
}

// Moves robot in desired cardinal direction
void MotorCommander::move(Robot* robot, Cardinal direction)
{
  if (robot->navigation.getOrientation() == direction){
    moveForward();
  }
  else {
      int x = (direction - robot->navigation.getOrientation());
   
      if (x == 0){
        moveForward();
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

    robot->setPinState(PIN_MOTOR_E1, PIN_STATE_HIGH);
    robot->setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
    robot->setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

    robot->setPinState(PIN_MOTOR_E2, PIN_STATE_HIGH);
    robot->setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
    robot->setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
  }
 else{
  // right motor back, left motor foward

  robot->setPinState(PIN_MOTOR_E1, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
  robot->setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

  robot->setPinState(PIN_MOTOR_E2, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);
 }
  
  float desiredAngle = getAngle() + degrees;
  
  while(fabs(getAngle() - desiredAngle) >= 2)
  {
    // Nothing
  }
  
  // Stop turning
  robot->setPinState(PIN_MOTOR_E1, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

  robot->setPinState(PIN_MOTOR_E2, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}

void MotorCommander::moveForward()
{
  robot->setPinState(PIN_MOTOR_E1, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
  robot->setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

  robot->setPinState(PIN_MOTOR_E2, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
  robot->setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}

void MotorCommander::moveBackward()
{
  robot->setPinState(PIN_MOTOR_E1, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
  robot->setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

  robot->setPinState(PIN_MOTOR_E2, PIN_STATE_HIGH);
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
