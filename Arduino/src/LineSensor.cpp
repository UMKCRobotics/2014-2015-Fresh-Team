#include "LineSensor.h"

#include "Arduino.h"

LineSensor::LineSensor()
{
	seesLine = false;
	timeWhenDetected = 0L;
}

void LineSensor::update(float reading)
{
	if(reading > readingThreshold)
	{
		seesLine = true;
		timeWhenDetected = millis();
	}
	else
	{
		seesLine = false;
	}
}

bool LineSensor::lineDetected(long compareTime)
{
	// The goal of this function is to compare the time when
	// the sensor saw the line to the current instant so 
	// that there is no misconception as to having seen a
	// line a long time ago

	return ((compareTime - timeWhenDetected) <= timingThreshold);
}

long LineSensor::getTimeDetected()
{
	return timeWhenDetected;
}