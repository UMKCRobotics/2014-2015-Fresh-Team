#include "DistanceSensor.h"

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

bool isCloseToWall()
{
	return closeToWall;
}
