#include "string.h"

#include "../../src/Pins.h"
#include "LineSensor.h"

// --- Message Handling ---
char incomingByte;
String receivedMessage;
void handleMesage(String message);

// --- Line Sensors ---
LineSensor ls_left;
LineSensor ls_middle;
LineSensor ls_right;

// --- Distance Sensors ---
int distanceThreshold = 0;

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
}

void loop()
{
	// // If data is available on the Serial line,
	// // read it a byte at a time until we are done
	while(Serial.available())
	{
		incomingByte = (char)Serial.read();
		receivedMessage += incomingByte;
	}

	// If we actually got more than a character, parse it
	// If not, just throw it away
	if(strlen(receivedMessage.c_str()) > 1)
	{
		// handleMessage(receivedMessage);
		handleMessage("FindRHOpening");
		receivedMessage = ""; // Still need to clear the message for next time
	} 
	else
	{
		receivedMessage = "";
	}

	// Update 
	ls_left.update(analogRead(PIN_LINE_SENSOR_L));
	ls_right.update(analogRead(PIN_LINE_SENSOR_R));

	// Check and see if both of them have seen a line  within
	// the threshold of time
	if(ls_left.lineDetected(ls_right.getTimeDetected()))
	{
//		Serial.print(ls_left.getLastReading());
//		Serial.print("\t\t");
//	 	Serial.println(ls_right.getLastReading());
        Serial.println("LineDetected");
	}
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

	if(response.startsWith("ReadDistSensor "))
	{
		String sensor = message.substring(11);

		if(sensor == "F")
		{
			response = "DistSensor " + sensor + ":" + analogRead(PIN_DISTANCE_SENSOR_F);
		}
		else if(sensor == "LF")
		{
			response = "DistSensor " + sensor + ":" + analogRead(PIN_DISTANCE_SENSOR_LF);
		}
		else if(sensor == "LB")
		{
			response = "DistSensor " + sensor + ":" + analogRead(PIN_DISTANCE_SENSOR_LB);
		}
		else if(sensor == "RF")
		{
			response = "DistSensor " + sensor + ":" + analogRead(PIN_DISTANCE_SENSOR_RF);
		}
		else if(sensor == "RB")
		{
			response = "DistSensor " + sensor + ":" + analogRead(PIN_DISTANCE_SENSOR_RB);
		}
	}
	if(response.startsWith("FindRHOpening"))
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
		if(distanceRightFront > distanceThreshold && distanceRightBack > distanceThreshold)
		{
			Serial.println("Opening Right");
		}
		else if(distanceFront > distanceThreshold)
		{
			Serial.println("Opening Front");
		}
		else if(distanceLeftFront > distanceThreshold && distanceLeftBack > distanceThreshold)
		{
			Serial.println("Opening Left");
		}
		else
		{
			Serial.println("Opening Back");
		}
	}
	else if(response.startsWith("NotifyOfAngle "))
	{
		// This clause will send a message to the Linux side to stop turning when a designated
		// angle has been reached (such as 90 or 180 degrees)

		// Parse end angle from string
		String str_endAngle = response.substring(14);
		int endAngle = atoi(str_endAngle.c_str());
		boolean angleReached = false;

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
				if(ls_right.getLinesPassed() == abs(endAngle / 90) &&
				   ls_middle.getLinesPassed() == (abs(endAngle / 90) - 1) && 
				   ls_middle.lineDetected(micros()))
				{
					Serial.println("AngleReached");
					angleReached = true;
				}
			}
			// Turning Left
			if(endAngle > 0)
			{
				if(ls_left.getLinesPassed() == abs(endAngle / 90) &&
				   ls_middle.getLinesPassed() == (abs(endAngle / 90) - 1) && 
				   ls_middle.lineDetected(micros()))
				{
					Serial.println("AngleReached");
					angleReached = true;
				}
			}
		}
	}

    delay(500);
}
