#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>
#include <iostream>
#include <string.h>
using namespace std;

class Logger{
private:
	ostream* os;
	void init();
	void log(string& message);
	void p_setStream(ostream* out);
	bool checkStream(bool throwError=true);
public:
	static Logger& getInstance(){
		static Logger instance;
		return instance;
	}

	static void setStream(ostream* out);
	static void logMessage(string message);
	static void logError(string error);

};
	
#endif