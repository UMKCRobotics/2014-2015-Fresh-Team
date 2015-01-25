#include "commandqueue.h"
#include "command.h"

void commandqueue::push(command a)
{
	commands.push(a);
}

command commandqueue::poptop()
{
	if(!commands.empty())
	{
		commands.pop();
		return commands.top();
	}

	//return fake command if the queue is empty
	command c;
	c.priority = 999;
	c.dothis = [](){};

	return c;
}

void commandqueue::setcompare()
{
	compare = [](command a, command b)
	{
		return a.priority > b.priority;
	};		
}

void commandqueue::init()
{
	commandqueue::getinstance().setcompare();
}

void commandqueue::sendCommand(command a)
{
	commandqueue::getinstance().push(a);
}

command commandqueue::receiveCommand()
{
	return commandqueue::getinstance().poptop();
}
