#include <iostream>
#include <queue>
//#include <lambda>
#include <functional>
#include <vector>

struct command{
	int priority;
	std::function<void()> dothis;
};

void world()
{
	std::cout << "World";
}

void hello()
{
	std::cout << "Hello";
}

int main()
{

	auto comp = [](command a, command b){ return a.priority > b.priority;};

	std::priority_queue<command, std::vector<command>, comp> functionqueue> commandqueue;


	std::function<void()> example = [] (){world();};
	command c;
	c.priority = 2;
	c.dothis = example;
	commandqueue.push(c);

	std::function<void()> secexample = [] (){hello();};

	command d;
	d.priority = 1;
	d.dothis = secexample;
	commandqueue.push(d);

	command e = commandqueue.pull();

	e.dothis();

	
	return 0;
}