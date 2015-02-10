#include "SerialListener.h"

SerialListener::SerialListener(serialib _serial, CommandQueue _queue)
{
	serial = _serial;
	queue = _queue;

	shouldListen = true;
}


// listen (void)
// Theaded function used to listen on the serial line between processors on the Linux side
// serialib will need to be checked for thread safety: elsewhere in the code we will still
// need to send messages
void SerialListener::listen()
{
	char received[128];
	int readStatus;

	while(shouldListen)
	{
		readStatus = serial.ReadString(received, '\n', 128);

		if(readStatus > 0)
		{
			Logger::logMessage("Received from Arduino: ");
			Logger::logMessage(received);

			queue.push(string(received)); 	// TODO: Will need to be expanded to accompany priority
											// For example: a container class to hold the command itself, priority code,
											// and the appropriate callback
		}
		else if(readStatus == 0)
		{
			Logger::logMessage("Error: Timeout Reached");
		}
		else if(readStatus == -1)
		{
			Logger::logMessage("Error: Could not set timeout");
		}
		else if(readStatus == -2)
		{
			Logger::logMessage("Error: Encountered error while parsing byte");
		}
		else if(readStatus == -3)
		{
			Logger::logMessage("Error: Byte maximum is reached:");
			Logger::logMessage(received);
		}
	}
}

// stopListening (void)
// Stops the listening on the serial line
void stopListening()
{
	shouldListen = false;
	// TODO: Code to cleanup and possibly stop the thread
}