#include "LineSensor.h"

#include "Arduino.h"

LineSensor::LineSensor()
{
	seesLine = false;
	timeWhenDetected = 0L;
}

void LineSensor::update(float reading)
{
	lastReading = reading;

	if(reading > readingThreshold)
	{
		seesLine = true;
		timeWhenDetected = micros();
	}
	else
	{
		// Increment our number of lines passed
		if(seesLine)	linesPassed++;

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

void LineSensor::resetLinesPassed()
{
	linesPassed = 0;
}

long LineSensor::getTimeDetected()
{
	return timeWhenDetected;
}

int LineSensor::getLastReading()
{
	return lastReading;
}

int LineSensor::getLinesPassed()
{
	return linesPassed;
}