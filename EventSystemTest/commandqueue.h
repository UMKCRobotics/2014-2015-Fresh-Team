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

	std::function<bool(command a, command b)> compare;

	std::priority_queue<command, std::vector<command>, decltype(compare)> commands;

	void push(command a);
	command poptop();
	void setcompare();

public:

	static void init();
	static void sendCommand(command a);
	static command receiveCommand();
	static commandqueue& getinstance()
	{
		static commandqueue instance;
		return instance;
	}
};

#endif