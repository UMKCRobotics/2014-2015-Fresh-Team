#ifndef SERIALLISTENER_H
#define SERIALLISTENER_H

#include <string>
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
};

#endif