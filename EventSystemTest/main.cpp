#include <iostream>
#include "robotbase.h"
#include "examplerobotobject.cpp"
#include "CommandType.h"
#include "command.h"
#include "commandqueue.h"

void world()
{
	std::cout << "world\n";
}

void hello()
{
	std::cout << "hello ";
}


int main()
{
	examplerobotobject gato;
	//commandqueue::init();
	std::cout << "Starting now!\n";
	

	std::function<void()> example = [] ()
	{
		std::cout << "World!\n";
	};


	command c;
	c.priority = 2;
	c.dothis = example;
	c.commandtype = CommandType::DRIVEFORWARD;

	commandqueue::sendCommand(c);

	command d;
	d.priority = 1;
	d.dothis = std::bind([](){hello();});
	d.commandtype = CommandType::DRIVEFORWARD;

	commandqueue::sendCommand(d);



	command l = commandqueue::receiveCommand();


	l.dothis();

	l = commandqueue::receiveCommand();


	l.dothis();

	l = commandqueue::receiveCommand();
	l.dothis();

	return 0;
}