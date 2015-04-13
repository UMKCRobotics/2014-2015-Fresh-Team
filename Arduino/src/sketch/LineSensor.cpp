#include "LineSensor.h"
#include "Arduino.h"

LineSensor::LineSensor(int _readingThreshold)
{
    readingThreshold = _readingThreshold;
    seesLine = false;
    timeWhenDetected = 0L;
    consecutiveReadings = 0;
}

void LineSensor::update(float reading)
{
	lastReading = reading;

	if(reading > readingThreshold)
	{
		consecutiveReadings++;	
  
                if(consecutiveReadings >= 3)
                {              
                    timeWhenDetected = micros();
                    seesLine = true;
                }
	}
	else
	{
		// Increment our number of lines passed
		if(seesLine) linesPassed++;

		seesLine = false;
                consecutiveReadings = 0;
	}
}

bool LineSensor::lineDetected(long compareTime)
{
	// The goal of this function is to compare the time when
	// the sensor saw the line to the current instant so 
	// that there is no misconception as to having seen a
	// line a long time ago
        // Additionally, this is to compare when the other line 
        // sensors saw the line so we can confirm that the line
        // sensors saw the line at approximately the same time       

	return  (abs(compareTime - timeWhenDetected) <= timingThreshold) && 
                (timeWhenDetected != 0L) && 
                seesLine;
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
