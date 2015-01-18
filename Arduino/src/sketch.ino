char incomingByte = '';
string receivedMessage = "";

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	// If data is available on the Serial line,
	// read it a byte at a time until we are done
	while(Serial.available())
	{
		incomingByte = (char)Serial.read();
		receivedMessage += incomingByte;
	}

	// If we actually got more than a character, parse it
	// If not, just throw it away
	if(strlen(receivedMessage) > 1)
	{
		handleMessage(receivedMessage);
		receivedMessage = ""; // Still need to clear the message for next time
	} 
	else 
	{
		receivedMessage = "";
	}
}

// Handles a message sent by the Linux side to the Arduino side
// Takes the incoming message as a string
// Does not return any value: the action needed to take by the 
// message will be handled inside the class through
// the serial object
// Handling of errors will also occur inside
void handleMessage(string message)
{
	string response = "";

	if(message == "readRoundAndPart")
	{
		response = "1:1"
	}

	Serial.println(response);
}
