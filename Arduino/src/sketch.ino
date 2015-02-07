#include "string.h"

#include "../../src/Pins.h"
#include "LineSensor.h"
#include "IMU.h"

// --- Message Handling ---
char incomingByte;
String receivedMessage;
void handleMesage(String message);

// --- Line Sensors ---
LineSensor ls_left;
LineSensor ls_right;

// --- IMU ---
LSM9DS0 IMU(MODE_I2C, 0x6B, 0x1D); 	// Arguments are from SparkFun example
									// See "Simple" example for explanation

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
	else if(response.startsWith("NotifyOfAngle "))
	{
		// This clause will send a message to the Linux side to stop turning when a designated
		// angle has been reached (such as 90 or 180 degrees)

		// Parse end angle from string
		String str_endAngle = response.substring(14);
		float f_endAngle = str_angle.toFloat();

		long lastCheckTime = microseconds();
		float currentRotationSpeed = 0;
		long timeSinceLastCheck = 0;
		float f_angle = 0.0f;

		// While the difference between the current angle and end angle is +/- 3 degrees...
		while(fabs(angle - f_endAngle) >= 3) // 3 is the error in degrees acceptable. Will need to be tested
		{
			// Get our rotation speed and get an estimation as to how long we have been
			// turning at that speed
			currentRotationSpeed = IMU.readGyro(IMU.gz);
			timeSinceLastCheck = microseconds() - lastCheckTime;

			// Add the degrees turned during that time period to our current angle
			// Also set the lastCheckTime for the next calculation
			angle += timeSinceLastCheck * currentRotationSpeed;
			lastCheckTime = microseconds();
		}

		Serial.println("AngleReached");
	}

	if(strlen(response.c_str()) > 1)
	{
		Serial.println(response);
	}
}
