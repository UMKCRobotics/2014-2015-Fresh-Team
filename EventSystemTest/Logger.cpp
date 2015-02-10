#include "Logger.h"
#include <stdexcept>

void Logger::log(string& message){
	(*os) << message;
}

void Logger::logMessage(string message)
{
	message = message + "\n";

	Logger::getInstance().checkStream();
	Logger::getInstance().log(message);
}

void Logger::logError(string error)
{
	error = "Error: " + error + "\n";
	Logger::getInstance().checkStream();
	Logger::getInstance().log(error);
}
void Logger::p_setStream(ostream* out){
	os = out;
}
void Logger::setStream(ostream* out){
	Logger::getInstance().p_setStream(out);	
}

bool Logger::checkStream(bool throwError){
	if(Logger::getInstance().os == NULL){
		if(throwError) {
			throw std::runtime_error("No stream set");
		}
		return false;
	}
	return true;
}