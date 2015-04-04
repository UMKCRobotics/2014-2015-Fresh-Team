#ifndef SERIALLISTENER_H
#define SERIALLISTENER_H

#include "serialib.h"
#include "MotorCommander.h"

class SerialListener
{
	private:
		bool shouldListen;
		bool noMessage;
		serialib serial;		
		
	public:
		SerialListener();
		bool init();
		void listen();
		void stopListening();
		void beginListening();
		serialib* getSerialStream();
};

#endif
