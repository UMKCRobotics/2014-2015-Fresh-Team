#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string.h>
using namespace std;

class Logger{
	public:
		Logger();
		void logMessage(string message);
		void logError(string error);
};
	
#endif