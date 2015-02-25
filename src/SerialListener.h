#ifndef SERIALLISTENER_H
#define SERIALLISTENER_H

#include "serialib.h"

class SerialListener
{
	private:
		bool shouldListen;
		serialib serial;

	public:
		SerialListener(serialib _serial);
		void listen();
		void stopListening();
};

#endif