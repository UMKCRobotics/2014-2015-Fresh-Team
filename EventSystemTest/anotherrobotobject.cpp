#include <iostream>
#include <functional>
#include "robotbase.h"
#include "command.h"

class anotherrobotobject : public RobotBase
{
	public:
		template <class T>
		anotherrobotobject(std::priority_queue<T> &thisqueue)
		{
			commandqueue = thisqueue;
		}

		virtual void halt()
		{
			command sendtogato;
			sendtogato.priority = 1;
			sendtogato.dothis = std::bind(	[](RobotBase * object){object->halt();});
			commandqueue.push(sendtogato);
		}

	private:
		template <class T>
		std::priority_queue<command, std::vector<command>, decltype(compare)> commandqueue;
};






