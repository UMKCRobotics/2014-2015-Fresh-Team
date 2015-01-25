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

	command c;
	c.priority = 999;
	c.dothis = [](){}; //return empty pointer if empty

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
	std::cout << "Initializing Command Queue\n";
	commandqueue::getinstance().setcompare();
}

void commandqueue::sendCommand(command a)
{
	std::cout << "Command Queue has received command\n";
	commandqueue::getinstance().push(a);
}

command commandqueue::receiveCommand()
{
	std::cout << "Command Queue is returning command\n";
	return commandqueue::getinstance().poptop();
}