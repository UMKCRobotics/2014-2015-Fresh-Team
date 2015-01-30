#include "string.h"

#include "../../src/Pins.h"
#include "LineSensor.h"

// --- Message Handling ---
char incomingByte;
String receivedMessage;
void handleMesage(String message);

// --- Line Sensors ---
LineSensor ls_left;
LineSensor ls_right;

// --- IMU ---
// TODO

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	// If data is available on the Serial line,
	// read it a byte at a time until we are done
	while(Serial.available())
	{
		incomingByte = (char)Serial.read();
		receivedMessage += incomingByte;
	}

	// If we actually got more than a character, parse it
	// If not, just throw it away
	if(strlen(receivedMessage.c_str()) > 1)
	{
		handleMessage(receivedMessage);
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
			response = "DistSensor " + sensor + " " + analogRead(PIN_DISTANCE_SENSOR_F);
		}
		else if(sensor == "LF")
		{
			response = "DistSensor " + sensor + " " + analogRead(PIN_DISTANCE_SENSOR_LF);
		}
		else if(sensor == "LB")
		{
			response = "DistSensor " + sensor + " " + analogRead(PIN_DISTANCE_SENSOR_LB);
		}
		else if(sensor == "RF")
		{
			response = "DistSensor " + sensor + " " + analogRead(PIN_DISTANCE_SENSOR_RF);
		}
		else if(sensor == "RB")
		{
			response = "DistSensor " + sensor + " " + analogRead(PIN_DISTANCE_SENSOR_RB);
		}
	}

	if(strlen(response.c_str()) > 1)
	{
		Serial.println(response);
	}
}
