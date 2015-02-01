#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <memory>
#include <map>
#include <utility>
#include "command.h"


template<typename CommandType>
class commandqueue
{
private:

	//The priority queue for handling the commands
	std::priority_queue<command, std::vector<command>,  std::function<bool(command,command)>> commands;
	//The map of registered functions to commands
	std::map<CommandType, std::function<void()>> FunctionMap;

	//priority queue accessors
	void push(command a)
	{
		commands.push(a);
	}

	command poptop()
	{
		command c;
		
		if(!commands.empty())
		{
			c = commands.top();
			commands.pop();

			return c;
		}
		
		c.priority = 999;
		c.dothis = [](){std::cout << "No available commands in commandqueue\n";}; //switch this to logger
		c.commandtype = "EMPTY";
		return c;
	}
	
	//constructor
	commandqueue()
	{
		std::function<bool(command,command)> compare = [](command a, command b){return a.priority > b.priority;};
		commands = std::priority_queue<command, std::vector<command>, decltype(compare)>(compare);
	}

	//made up my own word "Registree"
	template<typename Registree>
	void map(const CommandType& commandtype, const Registree&& registree)
	{
		FunctionMap.emplace(commandtype, registree);
	}

public:

	static void sendCommand(command a)
	{
		commandqueue::getinstance().push(a);
	}

	
	static command receiveCommand()
	{
		return commandqueue::getinstance().poptop();
	}

	static commandqueue& getinstance()
	{
		static commandqueue instance;
		return instance;
	}

	template<typename Registree>
	static void registerObject(CommandType& commandtype, Registree&& registree)
	{
		commandqueue::getinstance().map(commandtype, registree);
	}
};

#endif