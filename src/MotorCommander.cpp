#include <math.h>
#include "MotorCommander.h"

// Define pi here for sake of precision and easy of use
const float pi = 3.14159265358979f;

// Enable Pins for Motors
const int E1 = 4;
const int E2 = 5;

// Control Pins for Left Motor
const int L1 = 6;
const int L2 = 7;

// Control Pins for Right Motor
const int L3 = 8;
const int L4 = 9;

MotorCommander::MotorCommander()
{
  
}

// Moves robot in desired cardinal direction
void MotorCommander::move(Cardinal currentDirection, Cardinal direction)
{
  if (currentDirection == direction){
    // TODO: Move forward
  }
  else {
      int x = (direction - currentDirection);
   
      if (x == 0){
        // TODO: Move foward
      }
      else
      {
        turn(x*90);
      }
   }
}

void MotorCommander::turn(int degrees)
{
  if (degrees < 0){
    // left motor back, right foward
    //digitalWrite (E1,HIGH);
    //digitalWrite (L1,HIGH);
    //digitalWrite (L2,LOW);
    //digitalWrite (E2, HIGH);
    //digitalWrite (L3, LOW);
    //digitalWrite (L4, HIGH);
  }
 else{
  // right motor back, left motor foward
  //digitalWrite (E1, HIGH);
  //digitalWrite (L1, LOW);
  //digitalWrite (L2, HIGH);
  //digitalWrite (E2, HIGH);
  //digitalWrite (L3, HIGH);
  //digitalWrite (L4, LOW);
 }
  
  float desiredAngle = getAngle() + degrees;
  
  while(fabs(getAngle() - desiredAngle) >= 2)
  {
    // Nothing
  }
  
  // Stop turning
  //digitalWrite (E1, HIGH);
  //digitalWrite (L1, HIGH);
  //digitalWrite (L2, HIGH);
  //digitalWrite (E2, HIGH);
  //digitalWrite (L3, HIGH);
  //digitalWrite (L4, HIGH);
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
