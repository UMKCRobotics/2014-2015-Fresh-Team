#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <queue>
#include <functional>
#include <vector>
#include <memory>
#include "command.h"


class commandqueue
{
private:

	std::priority_queue<command, std::vector<command>,  std::function<bool(command,command)>> commands;

	void push(command a);
	command poptop();
	
	commandqueue()
	{
		std::function<bool(command,command)> compare = [](command a, command b){return a.priority > b.priority;};
		commands = std::priority_queue<command, std::vector<command>, decltype(compare)>(compare);
	};

public:

	static void sendCommand(command a);
	static command receiveCommand();
	static commandqueue& getinstance()
	{
		static commandqueue instance;
		return instance;
	}
};

#endif