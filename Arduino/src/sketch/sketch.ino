#include "Pins.h"
#include "LineSensor.h"
#include "string.h"
#include "Arduino.h"

// --- Message Handling ---
char incomingByte;
String receivedMessage;
void handleMesage(String message);
const String invalid = "Invalid Message: ";
bool isWaiting = true;

// --- Line Sensors ---
LineSensor ls_left(880);
LineSensor ls_middle(880);
LineSensor ls_right(880);
bool CurrentlySeesLine = false;
bool BumpDetected = false;
long timeOfLastDetect = 0;
const long minimumLineSeparationTime = 600000;

// --- Distance Sensors ---
int distanceThreshold = 90;
bool receivedEndline = false;

// --- Course Correction ---
bool correcting = false;
unsigned long correctionStartTime = 0;

void setup()
{
    Serial.begin(9600);

    Serial.println("Running...");

    pinMode(PIN_DISTANCE_SENSOR_F, INPUT);
    pinMode(PIN_DISTANCE_SENSOR_LF, INPUT);
    pinMode(PIN_DISTANCE_SENSOR_RF, INPUT);
    pinMode(PIN_DISTANCE_SENSOR_LB, INPUT);
    pinMode(PIN_DISTANCE_SENSOR_RB, INPUT);
    
    Serial.println("Finished setting up distance sensor pins");

    pinMode(PIN_LINE_SENSOR_L, INPUT);
    pinMode(PIN_LINE_SENSOR_M, INPUT);
    pinMode(PIN_LINE_SENSOR_R, INPUT);

    Serial.println("Finished setting up line sensor pins");
    Serial.println("Ready to sync");
}

void loop()
{
  if(isWaiting)
  {
    if(receivedMessage.length() > 0)
    {
      if(receivedMessage.startsWith("Sync"))
      {
        sendSerial("OK");
        isWaiting = false;
        timeOfLastDetect = micros() - 600000;
      }
      
      receivedMessage = "";
    }   
  }
  else
  {
      updateLineSensors();
      checkCourse();
      //collisionPrevention();
      
      if(receivedMessage.length() >= 2)
      {
          handleMessage(receivedMessage);
          
          receivedMessage = "";
      }
  }
  
//  if(Serial.available()) 
//  {
//    receivedMessage = Serial.readStringUntil('$');
//    if(receivedMessage.length() <= 2) receivedMessage = "";
//    
//    handleMessage(receivedMessage);
//    receivedMessage = "";
//  }
}

void serialEvent()
{
//    while(Serial.available() && !receivedEndline)
//    {
//        incomingByte = (char)Serial.read();
//        receivedMessage += incomingByte;
//
//        if(incomingByte == '$') receivedEndline = true;
//    }
    receivedMessage = Serial.readStringUntil('$');
    
    // If the message is an insignificant/correct length, clear it
    if(receivedMessage.length() <= 2) receivedMessage = "";
    
//    receivedEndline = false;
}

// Handles a message sent by the Linux side to the Arduino side
// Takes the incoming message as a string
// Does not return any value: the action needed to take by the 
// message will be handled inside
// Handling of errors will also occur inside
void handleMessage(String message)
{
    if(message.startsWith("ReadDistSensor "))
    {
        sendSerial("OK");
  
	readDistSensor(message.substring(15));
    }
    else if(message.startsWith("FindRHOpening"))
    {  
        sendSerial("OK");
  
        findRHOpening();
    }
    else if(message.startsWith("NotifyOfAngle "))
    {
        sendSerial("OK");
      
	notifyOfAngle(message.substring(14));
    }
    else
    {
        String invalidmessage;
        invalidmessage.concat(invalid);
        invalidmessage.concat(message);
        sendSerial(invalidmessage);
    }
}

void updateLineSensors()
{
    // Update 
    ls_left.update(analogRead(PIN_LINE_SENSOR_L));
    ls_middle.update(analogRead(PIN_LINE_SENSOR_M));
    ls_right.update(analogRead(PIN_LINE_SENSOR_R));
    
    // Check and see if both of them have seen a line  within
    // the threshold of time
    if(ls_left.lineDetected(ls_right.getTimeDetected()))
    {  
          if(!CurrentlySeesLine && !BumpDetected)
          {
              long delta = micros() - timeOfLastDetect;
              
              if(delta >= minimumLineSeparationTime)
              {
                  //Serial.print("Delta: ");
                  //Serial.println(delta);
                
                  CurrentlySeesLine = true;
                  sendSerial("LineDetected");
                  timeOfLastDetect = micros();
              }
              //else
              //{
              //    if(!BumpDetected)
              //    {
              //        sendSerial("BumpDetected");
              //        BumpDetected = true;
              //    }  
              //}
         }        
     } else {
         CurrentlySeesLine = false;
         BumpDetected = false;
     }
}

void readDistSensor(String sensor)
{
    String response;

    if(sensor == "F")
    {
        response = "DistSensor " + sensor + ":" + analogRead(PIN_DISTANCE_SENSOR_F);
    }
    else if(sensor.startsWith("LF"))
    {
        response = "DistSensor " + sensor + ":" + analogRead(PIN_DISTANCE_SENSOR_LF);
    }
    else if(sensor.startsWith("LB"))
    {
	response = "DistSensor " + sensor + ":" + analogRead(PIN_DISTANCE_SENSOR_LB);
    }
    else if(sensor.startsWith("RF"))
    {
	response = "DistSensor " + sensor + ":" + analogRead(PIN_DISTANCE_SENSOR_RF);
    }
    else if(sensor.startsWith("RB"))
    {
	response = "DistSensor " + sensor + ":" + analogRead(PIN_DISTANCE_SENSOR_RB);
    }

    sendSerial(response);
}

void findRHOpening()
{
    // Front
    int distanceFront = analogRead(PIN_DISTANCE_SENSOR_F);

    // Left
    int distanceLeftFront = analogRead(PIN_DISTANCE_SENSOR_LF);
    int distanceLeftBack = analogRead(PIN_DISTANCE_SENSOR_LB);

    // Right
    int distanceRightFront = analogRead(PIN_DISTANCE_SENSOR_RF);
    int distanceRightBack = analogRead(PIN_DISTANCE_SENSOR_RB);

    // Check values and send Opening command with parameter/argument of where the opening is
    if((distanceRightFront + distanceRightBack)/2 < distanceThreshold)
    {
        sendSerial("Opening Right");
    }
    else if(distanceFront < distanceThreshold)
    {
        sendSerial("Opening Front");
    }
    else if((distanceLeftFront + distanceLeftBack)/2 < distanceThreshold)
    {
        sendSerial("Opening Left");
    }
    else
    {
	sendSerial("Opening Back");
    }
}

void notifyOfAngle(String argument)
{
    // Parse end angle from string
    int endAngle = atoi(argument.c_str());
    int numberOfRightAngles = abs(endAngle / 90);
    boolean angleReached = false;
    boolean passedLeadingSensorBefore = false;
    int lastNumberOfLinesPassed = 0;
    bool allOffLine = false;
    long currentTime = 0;
    
    bool rightSensorDetected = false;
    bool leftSensorDetected = false;
    
    // Reset lines passed so that the number of lines passed starts at 0
    ls_left.resetLinesPassed();
    ls_middle.resetLinesPassed();
    ls_right.resetLinesPassed();
    
    while(!angleReached)
    {
        currentTime = micros();
        
        ls_left.update(analogRead(PIN_LINE_SENSOR_L));
        ls_middle.update(analogRead(PIN_LINE_SENSOR_M));
        ls_right.update(analogRead(PIN_LINE_SENSOR_R));
        
        // Wait until all of the line sensors clear into the white then allow the rest of the turning code to run
        if(!ls_left.lineDetected(currentTime) && !ls_middle.lineDetected(currentTime) && !ls_right.lineDetected(currentTime)) allOffLine = true;
        
        if(allOffLine)
        {
            // Turning Right
            if(endAngle < 0)
            {
                //if(ls_right.getLinesPassed() >= numberOfRightAngles)
                if(ls_right.lineDetected(currentTime)) rightSensorDetected = true;
                
                if(rightSensorDetected)
                {
                    // See if the leading line sensor has passed this line before
                    if(!passedLeadingSensorBefore)
                    {
                        // If not, then reset the middle line sensor and let it start scanning for the line
                        ls_middle.resetLinesPassed();
                        passedLeadingSensorBefore = true;
                    }
                    else
                    {
                        if(ls_middle.getLinesPassed() >= (numberOfRightAngles - 1) && ls_middle.lineDetected(currentTime) && !ls_right.lineDetected(currentTime)) //modified >=
                        {
                            sendSerial("AngleReached");
                            angleReached = true;
                        }
                    }
                }
                else if(lastNumberOfLinesPassed != ls_right.getLinesPassed())
                {
                  Serial.print("Lines passed: ");
                  Serial.println(ls_right.getLinesPassed());
                  
                  lastNumberOfLinesPassed = ls_right.getLinesPassed();
                }
            }
            // Turning Left
            else if(endAngle > 0)
            {
                //if(ls_left.getLinesPassed() >= numberOfRightAngles)
                if(ls_left.lineDetected(currentTime)) leftSensorDetected = true;
                
                if(leftSensorDetected)
                {
                    if(!passedLeadingSensorBefore)
                    {
                        ls_middle.resetLinesPassed();
                        passedLeadingSensorBefore = true;
                    }
                    else
                    {
                        //if(ls_middle.getLinesPassed() >= (numberOfRightAngles - 1) && ls_middle.lineDetected(currentTime) && !ls_left.lineDetected(currentTime))
                        if(ls_middle.getLinesPassed() >= (numberOfRightAngles - 1))
                        {
                            sendSerial("AngleReached");
                            angleReached = true;
                        }
                    }
                }
                else if(lastNumberOfLinesPassed != ls_left.getLinesPassed())
                {
                  Serial.print("Lines passed: ");
                  Serial.println(ls_left.getLinesPassed());
                  
                  lastNumberOfLinesPassed = ls_left.getLinesPassed();
                }
            }
        }
    }
    
    // After we are done turning, the time since last line read will need to be reset the time
    // since the last line has been passed. The majority of the time has been spent turning.
    timeOfLastDetect = micros();
}

void checkCourse()
{
    unsigned long currentTime = micros();
    
    if(correcting)
    {
        // If the middle line sensor picks the line up while we are correcting course then we have finished correcitn
        // course and can continue moving forward
        if(ls_middle.lineDetected(currentTime))
        {
              sendSerial("Corrected");
              correcting = false;
              timeOfLastDetect = timeOfLastDetect + (micros() - correctionStartTime);
        }
    }
    // If the robot is not currently correcting then check and see if it should be
    // Or
    // If the robot has been waiting for a correct for a quarter of a second then resend the command
    else if(!correcting || (correcting && timeOfLastDetect >= minimumLineSeparationTime))  /**((correctionStartTime + 150*1000) <= micros())) && */
    {
        // Check if the middle line sensor is on the line. In optimal conditions, it should be
        if(!ls_middle.lineDetected(currentTime))
        {
              // If both are reading a line, we cannot accurately correct the course
              if(ls_left.lineDetected(currentTime) && ls_right.lineDetected(currentTime))
              {
                  
              }
              // If the right is reading, then the robot is off to the left
              else if(!ls_left.lineDetected(currentTime) && ls_right.lineDetected(currentTime))
              {
                   sendSerial("Correct Right");
                   correctionStartTime = micros();
                   correcting = true;
              }
              // If the left is reading, then the robot is off to the right
              else if(ls_left.lineDetected(currentTime) && !ls_right.lineDetected(currentTime))
              {
                   sendSerial("Correct Left");
                   correctionStartTime = micros();
                   correcting = true;
              }
        }
    }
}

void collisionPrevention()
{
      int frontSensorReading = analogRead(PIN_DISTANCE_SENSOR_F);
      
      // Check and see if the wall is too close for comfort
      // If so, and there has been long enough time span for there to be a line
      if(frontSensorReading >= 280 && (micros() - timeOfLastDetect) >= minimumLineSeparationTime)
      {
          // Then we missed a line
          // Send the message now and reset the variables as if it had actually triggered.
          sendSerial("LineDetected");
          timeOfLastDetect = micros();
          CurrentlySeesLine = true;          
      }
}

void sendSerial(String message)
{
    Serial.print(message + "\r\n");
    Serial.flush();
}
