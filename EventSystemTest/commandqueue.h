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
#include "Logger.h"
#include "command.h"

class commandqueue
{
private:

	//The priority queue for handling the commands
	std::priority_queue<std::string, std::vector<command>,  std::function<bool(command,command)>> commands;
	//The map of registered functions to commands
	std::map<std::string, std::vector<std::function<void(std::string)>>> FunctionMap;

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
		commands = std::priority_queue<std::string, std::vector<command>, decltype(compare)>(compare);
	}

	//check if command type actually exists
	bool CommandTypeExists(std::string commandType)
	{
		if(!FunctionMap.empty()){
			if(FunctionMap.count(commandType) > 0) return true;
		}

		Logger::logError(commandType + " Does not extist in the FunctionMap!");
		return false;
	}



	void map(const std::string& commandtype, std::function<void(std::string)> function)
	{

		if(!CommandTypeExists(commandtype))
		{
			Logger::logMessage(commandtype + " Did not yet exist, creating it now!");
			FunctionMap.emplace(commandtype, std::vector<std::function<void(std::string)>>());
		}

		FunctionMap[commandtype].push_back(function);
	}

public:

	static bool sendNewCommand(command a)
	{
		if(!commandqueue::getinstance().CommandTypeExists(a.commandtype)) return false;

		commandqueue::getinstance().push(a);
		return true;
	}

	
	static void runNextCommand()
	{
		

	}

	static commandqueue& getinstance()
	{
		static commandqueue instance;
		return instance;
	}

	static void registerFunction(std::string& commandtype, std::function<void(std::string)> registerFunction)
	{
		commandqueue::getinstance().map(commandtype, registerFunction);
	}

};

#endif
