#include <iostream>
#include "commandqueue.h"
#include "command.h"

void commandqueue::push(command a)
{
	commands.push(a);
}

command commandqueue::poptop()
{
	command c;
	
	if(!commands.empty())
	{
		c = commands.top();


		commands.pop();

		return c;
	}
	
	c.priority = 999;
	c.dothis = [](){std::cout << "No available commands in commandqueue\n";}; //switch this to logger

	return c;
}

void commandqueue::sendCommand(command a)
{
	commandqueue::getinstance().push(a);
}

command commandqueue::receiveCommand()
{
	return commandqueue::getinstance().poptop();
}
