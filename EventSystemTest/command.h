#ifndef COMMAND_H
#define COMMAND_H

#include <functional>

struct command{
	int priority;
	std::function<void()> dothis;

};

#endif