#include "../../src/Pins.h"
#include "LineSensor.h"
#include "Arduino.h"

// --- Message Handling ---
char incomingByte;
String receivedMessage;

// --- Line Sensors ---
LineSensor ls_left(880);
LineSensor ls_middle(880);
LineSensor ls_right(880);

// --- Distance Sensors ---
int distanceThreshold = 150;


// --- setup ---

void setup()
{
	Serial.begin(9600);
	Serial.setTimeout(); //sets serial listening timeout to a second

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

// --- state values ---
enum State{ Forward, Turning }; //these go unused for now


// -- Arduino automatically calls this between each loop
void serialEvent()
{
	//bool receivedEndline = false;

	if(Serial.available() > 1) //makes sure there is more than 1 character being sent
	{

		receivedMessage = Serial.readStringUntil('$');

		//for debug purposes
		Serial.print("Command: ");
		Serial.println(receivedMessage);

	}else{
		receivedMessage = "";
	}
}

// -- Read Sensors --

void readLineSensors()
{

	// Update sensor readings
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
	//this may need updated, I'm not sure at the moment
	//TODO: Ask Connor on Friday
}

void readDistSensor(string sensor)
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

	Serial.print(response + "\n");
}

void findRHOpening()
{
	String response;

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
		Serial.print("Opening Right\r\n");
	}
	else if(distanceFront < distanceThreshold)
	{
		Serial.print("Opening Front\r\n");
	}
	else if((distanceLeftFront + distanceLeftBack)/2 < distanceThreshold)
	{
		Serial.print("Opening Left\r\n");
	}
	else
	{
		Serial.print("Opening Back\r\n");
	}

}

//todo: I really want to clean this function up but I don't think it's necessary (granted most of what I did was just
//style over function) and it would be best to modify it while at the lab where I can test changes I think if it's
//still having problems it is in this block of code as well. I did clean up the line endings for the messages but I
//don't think that should matter.
void notifyOfAngle()
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
						Serial.print("AngleReached\r\n");
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
						Serial.print("AngleReached\r\n");
						angleReached = true;
					}
				}
			}	
		}
	}	
}

// --- The Main Loop ---
void loop()
{

	readLineSensors();

	//message state handling
	if(receivedMessage.length() > 0)
	{
		if(message.startsWith("ReadDistSensor "))
		{
			readDistSensor(message.substring(15));
		}
		else if(message.startsWith("FindRHOpening"))
		{
			findRHOpening();
		}
		else if(message.startsWith("NotifyOfAngle "))
			notifyOfAngle();
		}
	}

	receivedMessage = ""; //reset receivedMessage
	//Don't want delays between loops unless necessary
}
