#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>
#include <iostream>
#include <string.h>
using namespace std;

enum LOG_OUTPUT
{
	LOGFILEOUT		= (1<<1),
	CONSOLEOUT		= (1<<2)
};

class Logger{
private:
	ostream* os;
	bool consoleOutput;
	bool fileOutput;
	void init();
	/*
	Logger(){};
	Logger(Logger const&);
	void operator=(Logger const&);
	*/
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