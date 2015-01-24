#include <iostream>
#include <functional>
#include "robotbase.h"
#include "command.h"

class anotherrobotobject : public RobotBase
{
	public:
		anotherrobotobject(std::priorityqueue &thisqueue)
		{
			commandqueue = thisqueue;
		}

		virtual void halt()
		{
			command sendtogato;
			sendtogato.priority = 1;
			sendtogato.dothis = std::bind(	[](RobotBase * object){object.halt();});
			commandqueue.push(sendtogato);
		}

	private:
		std::priorityqueue commandqueue;
};






