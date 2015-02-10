#ifndef SERIALLISTENER_H
#define SERIALLISTENER_H

#include <string>
#include "serialib.h"
#include "CommandQueue.h"

class SerialListener
{
	private:
		bool shouldListen;
		serialib serial;

	public:
		SerialListener(serialib _serial, CommandQueue _queue);
		void listen();
		void stopListening();
		void beginListening();
};

#endif