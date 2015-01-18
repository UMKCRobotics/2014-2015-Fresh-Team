#include "LineSensor.h"

LineSensor::LineSensor()
{
	seesLine = false;
}

void LineSensor::update(float reading)
{
	if(reading > readingThreshold)
	{
		seesLine = true;
	}
	else
	{
		seesLine = false;
	}
}

bool LineSensor::lineDetected()
{
	return seesLine;
}