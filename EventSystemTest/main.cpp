#include <iostream>

#include "robotbase.h"
#include "examplerobotobject.cpp"
#include "command.h"
#include "commandqueue.cpp"

void world()
{
	std::cout << "world\n";
}

void hello()
{
	std::cout << "hello\n";
}


int main()
{
	examplerobotobject gato;
	commandqueue::init();
	std::cout << "Starting now!\n";
	

	std::function<void()> example = [] ()
	{
		std::cout << "World!\n";
	};


	command c;
	c.priority = 2;
	c.dothis = example;

	std::cout << "Sending command 'c'\n";
	commandqueue::sendCommand(c);

	command d;
	d.priority = 1;
	d.dothis = std::bind([]()
	{
		std::cout << "Hello ";
	});

	std::cout << "Sending command 'd'\n";
	commandqueue::sendCommand(d);

	command l = commandqueue::receiveCommand();

	std::cout << "Preparing to do first function\n";

	l.dothis();

	l = commandqueue::receiveCommand();

	std::cout << "Preparing to do second function\n";

	l.dothis();

	return 0;
}