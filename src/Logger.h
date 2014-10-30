#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string.h>
using namespace std;

class Logger{
	public:
		void logMessage(string message);
		void logError(string error);
};
	
#endif