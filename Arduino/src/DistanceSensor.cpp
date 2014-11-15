#include "Sensor.h"

DistanceSensor::DistanceSensor()
{
	closeToWall = false;
}

void DistanceSensor::update(float distance)
{
	if(distance < minimumWallDistance)
	{
		closeToWall = true;
	}
	else
	{
		closeToWall = false;
	}
}
