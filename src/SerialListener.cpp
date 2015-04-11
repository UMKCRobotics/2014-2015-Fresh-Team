#include "SerialListener.h"
#include "Logger.h"
#include "CommandQueue.h"

SerialListener::SerialListener()
{
	shouldListen = true;
}

bool SerialListener::init()
{
	bool successful = true;
	int initStatus;
	noMessage = false; //assumes there might be a message.
	
	Logger::logMessage("Initiating Arduino SerialStream...");
	initStatus = serial.Open("/dev/ttymxc3", 9600);

	if(initStatus == 1) {
		Logger::logMessage("\tComplete");
	} else {
		Logger::logMessage("\tFailed to Open");
		successful = false;
	}
	
	commandqueue::registerFunction("SerialSend", [this](string message){
			Logger::logMessage("SerialSend: "+message+"$");
			this->serial.WriteString((message+"$").c_str());
			Logger::logMessage("Sent");
		});

	return successful;
}

// listen (void)
// Theaded function used to listen on the serial line between processors on the Linux side
// serialib will need to be checked for thread safety: elsewhere in the code we will still
// need to send messages
void SerialListener::listen()
{
	char received[128];
	int readStatus;
	string str_equiv, command, argument;

	if(serial.Peek() > 0) // Check and see if there are any bytes to read
	{
		Logger::logMessage("New message from Arduino:");
		readStatus = serial.ReadString(received, '\n', 128);

		if(readStatus > 0)
		{
			str_equiv = received;
			str_equiv = str_equiv.substr(0, strlen(str_equiv.c_str())-2);
			
			Logger::logMessage("'"+str_equiv+"'");
			
			if(str_equiv == "LineDetected")
			{
				Logger::logMessage("Entered new space");
				commandqueue::sendNewCommand(5, "LineDetected", "");
			}
			else if(str_equiv == "AngleReached")
			{
				Logger::logMessage("Angle reached: completed turn");
				commandqueue::sendNewCommand(1, "AngleReached", "");
			}
			else if(str_equiv == "OK")
			{
				Logger::logMessage("Message accepted by Arduino");
			}
			else if(str_equiv.find(" ") != std::string::npos)
			{
				// We have a command that has an argument
				// The command and argument will need to be split
				command = str_equiv.substr(0, str_equiv.find(" "));
				argument = str_equiv.substr(str_equiv.find(" ")+1);

				if(command == "Opening")
				{					
					Logger::logMessage("Move Relative: "+argument);

					if(argument == "Right")
					{
						commandqueue::sendNewCommand(1, "MOVERelative", "Right");
					}
					else if(argument == "Front")
					{
						commandqueue::sendNewCommand(1, "MOVERelative", "Front");
					}
					else if(argument == "Left")
					{
						commandqueue::sendNewCommand(1, "MOVERelative", "Left");
					}
					else if(argument == "Back")
					{
						commandqueue::sendNewCommand(1, "MOVERelative", "Back");
					}
				}
			}
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
		
		noMessage = false;
	}
	else if(!noMessage)
	{
		noMessage = true;
	}
}

// stopListening (void)
// Stops listening on the serial line
void SerialListener::stopListening()
{
	Logger::logMessage("Disabling SerialListener!");
	shouldListen = false;
}

void SerialListener::beginListening()
{
	Logger::logMessage("Enabling SerialListener!");
	shouldListen = true;
}

serialib* SerialListener::getSerialStream()
{
	return &serial;
}
