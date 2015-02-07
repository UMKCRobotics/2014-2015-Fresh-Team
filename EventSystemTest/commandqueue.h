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
	std::map<std::string, std::function<void(std::string)>> FunctionMap;

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

		Logger::logMessage("CommandQueue was empty");
		
		c.priority = 999;
		c.commanddata = "NULL";
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
		if(!FunctionMap.empty()){
			if(FunctionMap.find(commandType) > 0) return true;
		}

		Logger::logError(commandType + " Does not extist in the FunctionMap!");
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
	static void registerFunction(std::string& commandtype, Registree&& registree)
	{
		commandqueue::getinstance().map(commandtype, registree);
	}

};

#endif
