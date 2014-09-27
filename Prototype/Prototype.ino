#include <RedBot.h>
#include <RedBotSoftwareSerial.h>
#include <DistanceGP2Y0A21YK.h>
#include <Arduino.h>

//Anything below 1000 was consistently not a line during testing
const int lineConstant = 1000; 

//line array(holds the last 10 linesensor readings)
int lineArray[10];

//maximum distance value to stop it at
const int FDistanceThreshold = 300;

//delay value
const int delayTime = 30; 

// robot state enumeration
enum State
{
  Cruising,
  Pivoting  
};

// Robot initual state - cruising
State state = Cruising;

//distance Array(holds the last 10 distances)
int DistanceArray[10];

//redbot motors
RedBotMotor motors;

//Constant variables for maximum movement speed in either direction 
const int driveforward = 255;
const int drivebackward = -255;

// Pivot timing
long starttime = millis();
long difference = 0L;
 
void setup()
{
  Serial.begin(9600);
  
  pinMode(A1, INPUT); // IR Sensor input pin is A1
  pinMode(A5, INPUT); // Intended for the Button 
  pinMode(A4, INPUT); // Line Sensor Pin is A4  
  
  //sets all values of distance array and line reader to threshold
  //this keeps the average high enough to avoid starting
  for(int i = 0; i < 10; i++)
  {
    DistanceArray[i] = FDistanceThreshold;
    lineArray[i] = lineConstant;
  } 
}

//Averages readings from given sensor
int ReadingAverager(int & reading, int (&readingArray)[10] )
{
  int sum = 0;
  
  for(int i = 0; i < 9; i++)
  {
    //Serial.println(readingArray[i]);
    sum += readingArray[i];
    readingArray[i] = readingArray[i+1];
    
  }
  
  readingArray[9] = reading;
  sum += reading;
   
  return sum/10;
}

// State function for driving until finding a wall
void cruising(int LDAverage, int FDAverage)
{
  Serial.println("Cruising");
  if(FDAverage < FDistanceThreshold) 
  {
    motors.rightDrive(driveforward-15); //slight difference to correct
    motors.leftDrive(driveforward);
  }
  else
  {
    motors.drive(0); //stop if within proximity of a wall
    //I havent measured actual proximity, will need to be
    //calibrated for what we want sometime.
    
    state = Pivoting;
    starttime = millis(); // Set the start time to now for the pivot timing
  }
  
  //prints information
  Serial.print("Raw Distance Average: ");
  Serial.print(FDAverage);
  Serial.print("\n");

  if(LDAverage > lineConstant)
  {
    Serial.println("Line Detected");
  }
  else
  {
    Serial.println("No Line...");
  }  
}

// State function for pivoting 90 degrees
void pivot()
{
  Serial.println("Pivoting");
  difference = millis() - 1000;
  
  if(difference >= 2200)
  {
    // Done turning; begin to drive forward again
    motors.rightDrive(driveforward - 15);
    motors.leftDrive(driveforward);
    
    state = Cruising;
  }
  
  // Else, continue turning
  motors.rightDrive(driveforward - 15);
  motors.leftDrive(drivebackward);
}

void loop()
{
  int linedetect = analogRead(5);
  int frontDistance = analogRead(1);
  
  int LDAverage = ReadingAverager(linedetect, lineArray);
  int FDAverage = ReadingAverager(frontDistance, DistanceArray);
  
  switch(state)
  {
    case Cruising:
      cruising(LDAverage, FDAverage);
    break;

    case Pivoting:
      pivot();
    break;  
  };
  
  //delays (feel free to modify any constants at the top)
  delay(delayTime);
}
