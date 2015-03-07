#include "../../src/Pins.h"
#include "LineSensor.h"
#include "Arduino.h"

// --- Message Handling ---
char incomingByte;
String receivedMessage;
void handleMesage(String message);

// --- Line Sensors ---
LineSensor ls_left(880);
LineSensor ls_middle(880);
LineSensor ls_right(880);

// --- Distance Sensors ---
int distanceThreshold = 150;
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

void loop()
{
	// // If data is available on the Serial line,
	// // read it a byte at a time until we are done
	while(Serial.available() && !receivedEndline)
	{
		incomingByte = (char)Serial.read();
		receivedMessage += incomingByte;

		if(incomingByte == '$') receivedEndline = true;
	}

	receivedEndline = false;

	// If we actually got more than a character, parse it
	// If not, just throw it away
	if(receivedMessage.length() > 1 && receivedMessage.indexOf("$") != -1)
	{
		receivedMessage = receivedMessage.substring(0, strlen(receivedMessage.c_str()) - 2);

		handleMessage(receivedMessage);
		receivedMessage = ""; // Still need to clear the message for next time
	}
	// Update 
	ls_left.update(analogRead(PIN_LINE_SENSOR_L));
	ls_middle.update(analogRead(PIN_LINE_SENSOR_M));
	ls_right.update(analogRead(PIN_LINE_SENSOR_R));

	// Check and see if both of them have seen a line  within
	// the threshold of time
	if(ls_left.lineDetected(ls_right.getTimeDetected()))
	{
		// Serial.print(ls_left.getLastReading());
		// Serial.print("\t\t");
		// Serial.println(ls_right.getLastReading());

        Serial.print("LineDetected\r\n");
	}

    delay(10);
}

// Handles a message sent by the Linux side to the Arduino side
// Takes the incoming message as a string
// Does not return any value: the action needed to take by the 
// message will be handled inside the class through
// the serial object
// Handling of errors will also occur inside
void handleMessage(String message)
{
	String response;

	Serial.print("Command: ");
	Serial.println(message);

	if(message.startsWith("ReadDistSensor "))
	{
		String sensor = message.substring(15);

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

		Serial.print(response + "\n");
	}
	else if(message.startsWith("FindRHOpening"))
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
			Serial.println("Opening Right");
		}
		else if(distanceFront < distanceThreshold)
		{
			Serial.println("Opening Front");
		}
		else if((distanceLeftFront + distanceLeftBack)/2 < distanceThreshold)
		{
			Serial.println("Opening Left");
		}
		else
		{
			Serial.println("Opening Back");
		}
	}
	else if(message.startsWith("NotifyOfAngle "))
	{
		// This clause will send a message to the Linux side to stop turning when a designated
		// angle has been reached (such as 90 or 180 degrees)

		// Parse end angle from string
		String str_endAngle = response.substring(14);
		int endAngle = -90;	//atoi(str_endAngle.toCharArray());
		int numberOfRightAngles = abs(endAngle / 90);
		boolean angleReached = false;
		boolean passedLeadingSensorBefore = false;

		// Reset lines passed so that the number of lines passed starts at 0
		ls_left.resetLinesPassed();
		ls_middle.resetLinesPassed();
		ls_right.resetLinesPassed();

		Serial.println("OK");

		while(!angleReached)
		{
			ls_left.update(analogRead(PIN_LINE_SENSOR_L));
			ls_middle.update(analogRead(PIN_LINE_SENSOR_M));
			ls_right.update(analogRead(PIN_LINE_SENSOR_R));

			//Serial.println(ls_middle.getLinesPassed());

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
						if(ls_middle.getLinesPassed() == numberOfRightAngles)
						{
							Serial.print("AngleReached\n");
							angleReached = true;
						}
					}
				}
			}
			// Turning Left
			if(endAngle > 0)
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
						if(ls_middle.getLinesPassed() == numberOfRightAngles)
						{
							Serial.print("AngleReached\n");
							angleReached = true;
						}
					}
				}	
			}
		}
	}
}
