#include <iostream>
#include <queue>
//#include <lambda>
#include <functional>
#include <vector>
#include <memory>
#include "robotbase.h"
#include "examplerobotobject.cpp"

struct command{
	int priority;
	std::function<void()> dothis;
};

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
	
	command f;
	f.priority = 3;
	f.dothis = std::bind([&gato]()
	{
		gato.halt();
	});
	commandqueue.push(f);

	command e = commandqueue.top();

	e.dothis();

	

	commandqueue.pop();

	e = commandqueue.top();

	e.dothis();
	

	commandqueue.pop();

	e = commandqueue.top();

	e.dothis();

	commandqueue.pop();

	

	return 0;
}