#include "IMU.h"

LSM9DS0 dof(MODE_I2C, LSM9DS0_G, LSM9DS0_XM);
int CurrentOrientation = 1;

const int E1 = 4;
const int E2 = 5;

const int L1 = 6;
const int L2 = 7;

const int L3 = 8;
const int L4 = 9;

void move(int cardinaldirection){
  
  if (CurrentOrientation == cardinaldirection){
  }
  else {
      int x = (cardinaldirection-CurrentOrientation);
   
      if (x == 0){
        //move foward
      }
      else
      {
        turn(x*90);
        
      }
   }
}
void turn(int neededDegrees)
{
  if (neededDegrees < 0){
    //leftmotor back, right foward
    digitalWrite (E1,HIGH);
    digitalWrite (L1,HIGH);
    digitalWrite (L2,LOW);
    digitalWrite (E2, HIGH);
    digitalWrite (L3, LOW);
    digitalWrite (L4, HIGH);
  }
 else{
  //rightmotor back, left motor foward
  digitalWrite (E1, HIGH);
  digitalWrite (L1, LOW);
  digitalWrite (L2, HIGH);
  digitalWrite (E2, HIGH);
  digitalWrite (L3, HIGH);
  digitalWrite (L4, LOW);
 }
  
  float desiredAngle = getAngle() + neededDegrees;
  
  while(abs(getAngle() - desiredAngle) >= 2)
  {
    
  }
  
  // Stop turning
  digitalWrite (E1, HIGH);
  digitalWrite (L1, HIGH);
  digitalWrite (L2, HIGH);
  digitalWrite (E2, HIGH);
  digitalWrite (L3, HIGH);
  digitalWrite (L4, HIGH);
)
float getAngle()
{
  float heading;
  float hx = dof.mx;
  float hy = dof.my;
  
  if (hy > 0)
  {
    heading = 90 - (atan(hx / hy) * (180 / PI));
  }
  else if (hy < 0)
  {
    heading = - (atan(hx / hy) * (180 / PI));
  }
  else // hy = 0
  {
    if (hx < 0) heading = 180;
    else heading = 0;
  }
  
  return heading;
}


void setup(){
  
  
  
}




void loop(){
  
  
  
}
