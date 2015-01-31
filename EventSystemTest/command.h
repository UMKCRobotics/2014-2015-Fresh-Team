#ifndef COMMAND_H
#define COMMAND_H

#include <functional>
#include "CommandType.h"

struct command{
	int priority;
	std::function<void()> dothis;
	CommandType commandtype;
};



#endif