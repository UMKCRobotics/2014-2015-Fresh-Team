#include "SerialListener.h"
#include "Logger.h"

SerialListener::SerialListener()
{
	shouldListen = true;
}

bool SerialListener::init()
{
	bool successful = true;
	int initStatus;

	Logger::logMessage("Initiating Arduino SerialStream...");
	initStatus = serial.Open("/dev/ttymxc3", 9600);

	if(initStatus == 1) {
		Logger::logMessage("\tComplete");
	} else {
		Logger::logMessage("\tFailed to Open");
		successful = false;
	}

	return successful;
}

// listen (void)
// Theaded function used to listen on the serial line between processors on the Linux side
// serialib will need to be checked for thread safety: elsewhere in the code we will still
// need to send messages
void SerialListener::listen(MotorCommander* motorCommander)
{
	char received[128];
	int readStatus;
	string str_equiv, command, argument;

	if(shouldListen)
	{
		readStatus = serial.ReadString(received, '\n', 128);

		if(readStatus > 0)
		{
			str_equiv = received;
			str_equiv = str_equiv.substr(0, strlen(str_equiv.c_str())-2);
			
			if(str_equiv == "LineDetected")
			{
				Logger::logMessage("I'm in a new space");

				// Let's figure out if we should stop
				serial.WriteString("FindRHOpening$");
			}
			else if(str_equiv.find(" ") != -1)
			{
				// We have a command to interpret
				command = str_equiv.substr(0, str_equiv.find(" "));
				argument = str_equiv.substr(str_equiv.find(" ")+1);

				if(command == "Opening" && argument != "Front")
				{
					motorCommander->halt();

					// TODO: Interact with navigation and update direction and position

					if(argument == "Right")
					{
						motorCommander->turn(-90);
					}
					else if(argument == "Left")
					{
						motorCommander->turn(90);
					}
					else if(argument == "Back")
					{
						motorCommander->turn(180);
					}
				}
			}

			// TODO: Push into queue
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
void SerialListener::stopListening()
{
	Logger::logMessage("Disabling SerialListner!");
	shouldListen = false;
	// TODO: Code to cleanup and possibly stop the thread
}

void SerialListener::beginListening()
{
	Loger::logMessage("Enabling SerialListener!");
	shouldListen = true;
}

serialib SerialListener::getSerialStream()
{
	return serial;
}