#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <queue>
#include <functional>
#include <vector>
#include <memory>
#include <map>
#include "command.h"


class commandqueue
{
private:

	//The priority queue for handling the commands
	std::priority_queue<command, std::vector<command>,  std::function<bool(command,command)>> commands;
	//The map of registered functions to commands
	std::map<CommandType, std::function<void()>> FunctionMap;

	//priority queue accessors
	void push(command a);
	command poptop();
	
	//constructor
	commandqueue()
	{
		std::function<bool(command,command)> compare = [](command a, command b){return a.priority > b.priority;};
		commands = std::priority_queue<command, std::vector<command>, decltype(compare)>(compare);
	};

	//made up my own word "Registree"
	template<typename Registree>
	void map(CommandType& commandtype, Registree&& registree);

public:

	static void sendCommand(command a);
	static command receiveCommand();
	static commandqueue& getinstance()
	{
		static commandqueue instance;
		return instance;
	}

	template<typename Registree>
	static void register(CommandType& commandtype, Registree&& registree);
};

#endif