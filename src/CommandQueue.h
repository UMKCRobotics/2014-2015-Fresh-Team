#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <utility>
#include <string>
#include "Logger.h"
#include "Command.h"

class commandqueue
{
private:

	//The priority queue for handling the commands
	std::priority_queue<std::string, std::vector<command>,  std::function<bool(command,command)>> commands;
	//The map of registered functions to commands
	std::map<std::string, std::vector<std::function<void(std::string)>>> FunctionMap;

	//constructor
	commandqueue()
	{
		std::function<bool(command,command)> compare = [](command a, command b){return a.priority > b.priority;};
		commands = std::priority_queue<std::string, std::vector<command>, decltype(compare)>(compare);
	}

	void push(command a) //to commands
	{
		commands.push(a);
	}

	command poptop() //from commands
	{
		command c;
		
		if(!commands.empty())
		{
			c = commands.top();
			commands.pop();

			return c;
		}

//		Logger::logMessage("CommandQueue was empty");
		
		c.priority = 999;
		c.commanddata = "";
		c.commandtype = "EMPTY";
		return c;
	}
	
	//check if command type actually exists
	bool commandTypeExists(std::string commandType) //in functionmap
	{
		if(!FunctionMap.empty()){
			if(FunctionMap.count(commandType) > 0) return true;
		}

		Logger::logMessage(commandType + " Does not exist in the FunctionMap!");
		return false;
	}

	//Adds function to the commandqueue based on commandtype string
	void map(const std::string commandtype, std::function<void(std::string)> function) //to functionmap
	{

		//if the commandtype doesn't exist create it first
		if(!commandTypeExists(commandtype))
		{
			Logger::logMessage(commandtype + " Did not yet exist, creating it now!");
			FunctionMap.emplace(commandtype, std::vector<std::function<void(std::string)>>());
		}

		FunctionMap[commandtype].push_back(function);
	}

	std::vector<std::function<void(std::string)>> getCommandsOfType(std::string commandType) //from functionmap
	{
		//if the commandtype doesn't exist return an empty vector
		if(!commandTypeExists(commandType))
		{
			return std::vector<std::function<void(std::string)>>();
		}

		return FunctionMap[commandType];
	}

public:

	static commandqueue& getinstance() //of this commandqueue
	{
		static commandqueue instance;
		return instance;
	}

	static bool sendNewCommand(command a) //to commands
	{
		if(!commandqueue::getinstance().commandTypeExists(a.commandtype)) return false;

		commandqueue::getinstance().push(a);
		return true;
	}

	static bool sendNewCommand(int priority, std::string commandtype, std::string commanddata) //to commands
	{
		if(!commandqueue::getinstance().commandTypeExists(commandtype)) return false;

		command b;
		b.priority = priority;
		b.commandtype = commandtype;
		b.commanddata = commanddata;

		commandqueue::getinstance().push(b);
		return true;
	}

	static void registerFunction(std::string commandtype, std::function<void(std::string)> functionToRegister) //to functionmap
	{
		commandqueue::getinstance().map(commandtype, functionToRegister);
	}
	
	static void runNextCommand() //in commands from functionmap
	{
		command b = commandqueue::getinstance().poptop();
		if(b.commandtype != "EMPTY")
		{
			std::vector<std::function<void(std::string)>> commandToRun = commandqueue::getinstance().getCommandsOfType(b.commandtype);

			if(commandToRun.empty()) return;

			std::for_each(commandToRun.begin(), commandToRun.end(), [b](std::function<void(std::string)> actWith){
				actWith(b.commanddata);
			});
		}
	}

};

#endif
