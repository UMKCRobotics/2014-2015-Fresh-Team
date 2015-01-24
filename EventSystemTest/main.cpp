#include <iostream>
#include <queue>
//#include <lambda>
#include <functional>
#include <vector>
#include <memory>
#include "robotbase.h"
#include "examplerobotobject.cpp"
#include "anotherrobotobject.cpp"
#include "command.h"


void world()
{
	std::cout << "World\n";
};

void hello()
{
	std::cout << "Hello\n";
};

int main()
{

	examplerobotobject gato;



	auto compare = [](command a, command b)
	{
		return a.priority > b.priority;
	};

	std::priority_queue<command, std::vector<command>, decltype(compare) > commandqueue(compare);

	anotherrobotobject robo = new anotherrobotobject(commandqueue);

	std::function<void()> example = [] ()
	{
		world();
	};

	command c;
	c.priority = 2;
	c.dothis = example;
	commandqueue.push(c);

	command d;
	d.priority = 1;
	d.dothis = std::bind([]()
	{
		hello();
	});
	commandqueue.push(d);

	robo.halt();	

	command e = commandqueue.top();

	e.dothis();

	

	commandqueue.pop();

	e = commandqueue.top();

	e.dothis();
	

	commandqueue.pop();

	e = commandqueue.top();

	e.dothis(gato);

	commandqueue.pop();

	return 0;
}