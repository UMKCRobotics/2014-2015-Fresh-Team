#include <iostream>
#include "pins.h"

using namespace std;

void MotionControl()
{
  double x;
  double m;
  double z;
  
  int distance_RF = analogread(PIN_DISTANCE_SENSOR_RF); 
  int distance_LF = analogread(PIN_DISTANCE_SENSOR_LF);
  int distance_RB = analogread(PIN_DISTANCE_SENSOR_RB);
   
  // Square but off to one side
  if (abs(distance_RF - distance_RB) <= 15) // Dummy value
  {
    if (distance_RF < minDistance && distance_LF > maxDistance)
      z = -10; 
    else if (distance_LF < minDistance && distance_RF > maxDistance)
      z = 10;
  }
  // Turned left
  else if (distance_RF > distance_RB)
  { 
    x = distance_RF(tan(90));
    m = acos((distance_RF/x)*(180/3.14159265));
    z = 90 - m;
  }
  // Turned right
  else if (distance_RF < distance_RB)   
  {
    x = distance_RF(tan(90));
    z = atan2((distance_RF/x)*(180/3.14159265));
    z = z*(-1);    
  }
  
  if(z != 0)
  {
    Serial.print("AdjustAlignment ");
    Serial.println(z);
  } 
}
