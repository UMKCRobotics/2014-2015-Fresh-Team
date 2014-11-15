#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
using namespace std;

const float minimumWallDistance = 2.0f; // Dummy value, will need to be discovered through testing

class DistanceSensor
{
private:
	bool closeToWall;

public:
	Sensor();

	void update(float distance);
	bool isCloseToWall();
};

#endif