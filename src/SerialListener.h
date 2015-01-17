#ifndef SERIALLISTENER_H
#define SERIALLISTENER_H

#include "serialib.h"
#include "boost/heap.h" // Double check the location

// Let's make our lives easier
typedef boost::heap::priority_queue<String> CommandQueue;

class SerialListener
{
	private:
		bool shouldListen;
		serialib serial;
		CommandQueue queue;

	public:
		SerialListener(serialib _serial, CommandQueue _queue);
		void listen();
};

#endif