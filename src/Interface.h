#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Interface
{
public:
	static Interface& getInstance(){
		static Interface instance;
		return instance;
	}
	
	static int getPinDirection(int pin);
	static int getPinState(int pin);
	static void setPinState(int pin, int state);
	static bool setPinDirection(int pin, int state);

private:
	string getPinFileContents(int pin, int property);
	bool writePinFileContents(int pin, int property, int value);
};

#endif