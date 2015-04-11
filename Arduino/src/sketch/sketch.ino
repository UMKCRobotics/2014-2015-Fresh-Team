#include "Pins.h"
#include "LineSensor.h"
#include "string.h"
#include "Arduino.h"

// --- Message Handling ---
char incomingByte;
String receivedMessage;
void handleMesage(String message);
bool CurrentlySeesLine = false;
bool BumpDetected = false;
long TimeOfLastDetect = 0;
const String invalid = "Invalid Message: ";

// --- Line Sensors ---
LineSensor ls_left(880);
LineSensor ls_middle(880);
LineSensor ls_right(880);

// --- Distance Sensors ---
int distanceThreshold = 100;
bool receivedEndline = false;

void setup()
{
    Serial.begin(9600);

    Serial.println("Running...");

    pinMode(PIN_DISTANCE_SENSOR_F, INPUT);
    pinMode(PIN_DISTANCE_SENSOR_LF, INPUT);
    pinMode(PIN_DISTANCE_SENSOR_RF, INPUT);
    pinMode(PIN_DISTANCE_SENSOR_LB, INPUT);
    pinMode(PIN_DISTANCE_SENSOR_RB, INPUT);
    pinMode(PIN_FAST_ROUND, INPUT);

    pinMode(PIN_LINE_SENSOR_L, INPUT);
    pinMode(PIN_LINE_SENSOR_M, INPUT);
    pinMode(PIN_LINE_SENSOR_R, INPUT);

    Serial.println("Finished setting up pins");
}

bool waitforgo = true;

void loop()
{
  if(waitforgo)
  {
    if(receivedMessage.length() > 0)
    {
      if(receivedMessage.startsWith("Sync"))
      {
        sendSerial("OK");
        waitforgo = false;
        TimeOfLastDetect = micros();
      }
      
      receivedMessage = "";
    }   
  }
  else
  {
    updateLineSensors();
    
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
              long j = micros();
              long delta = j - TimeOfLastDetect;
              TimeOfLastDetect = j;
              
              if(delta > 70000)
              {
//                  Serial.print("Time since last detect (uS): ");
//                  Serial.print(delta);
//                  Serial.print("\r\n");
                  
                  CurrentlySeesLine = true;
                  sendSerial("LineDetected");
              } 
              else if(delta < 70000) 
              {
                  if(!BumpDetected)
                  {
                      sendSerial("BumpDetected");
                      BumpDetected = true;
                  }  
              }
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
    
    // Reset lines passed so that the number of lines passed starts at 0
    ls_left.resetLinesPassed();
    ls_middle.resetLinesPassed();
    ls_right.resetLinesPassed();
    
    while(!angleReached)
    {
        ls_left.update(analogRead(PIN_LINE_SENSOR_L));
        ls_middle.update(analogRead(PIN_LINE_SENSOR_M));
        ls_right.update(analogRead(PIN_LINE_SENSOR_R));
        
        // Turning Right
        if(endAngle < 0)
        {
            if(ls_right.getLinesPassed() == numberOfRightAngles)
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
                    if(ls_middle.getLinesPassed() >= numberOfRightAngles)
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
            if(ls_left.getLinesPassed() == numberOfRightAngles)
            {
                if(!passedLeadingSensorBefore)
                {
                    ls_middle.resetLinesPassed();
                    passedLeadingSensorBefore = true;
                }
                else
                {
                    if(ls_middle.getLinesPassed() >= numberOfRightAngles)
                    {
                        sendSerial("AngleReached");
                        angleReached = true;
                    }
                }
            }
            else if(lastNumberOfLinesPassed != ls_right.getLinesPassed())
            {
              Serial.print("Lines passed: ");
              Serial.println(ls_left.getLinesPassed());
              
              lastNumberOfLinesPassed = ls_left.getLinesPassed();
            }	
        }
    }
}

void sendSerial(String message)
{
    Serial.print(message + "\r\n");
    Serial.flush();
}
