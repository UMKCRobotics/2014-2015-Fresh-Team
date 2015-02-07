#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <memory>
#include <map>
#include <utility>
#include <string>
#include "logger.h"
#include "command.h"

class commandqueue
{
private:

	//The priority queue for handling the commands
	std::priority_queue<std::string, std::vector<command>,  std::function<bool(command,command)>> commands;
	//The map of registered functions to commands
	std::map<std::string, std::function<void()>> ObjectMap;

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

	//check if command type actually exists
	bool CommandTypeExists(std::string commandType)
	{
		if(!ObjectMap.empty()){
			if(ObjectMap.find(commandType) > 0) return true;
		}

		logger.logError(commandType + " Does not extist in the FunctionMap!");
		return false;
	}

	//made up my own word "Registree"
	template<typename Registree>
	void map(const std::string& commandtype, const Registree&& registree)
	{
		FunctionMap.emplace(commandtype, registree);
	}

public:

	static bool sendNewCommand(command a)
	{
		if(!commandqueue::getinstance().CommandTypeExists(a.commandtype)) return false;

		commandqueue::getinstance().push(a);
		return true;
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
	static void registerObject(std::string& commandtype, Registree&& registree)
	{
		commandqueue::getinstance().map(commandtype, registree);
	}

};

#endif

//to consider: I may not need an actual "command objecst"