#ifndef SERIALLISTENER_H
#define SERIALLISTENER_H

#include "serialib.h"
#include "MotorCommander.h"

class SerialListener
{
	private:
		bool shouldListen;
		serialib serial;

	public:
		SerialListener();
		bool init();
		void listen(MotorCommander* motorCommander);
		void stopListening();
		serialib getSerialStream();
};

#endif