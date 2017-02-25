#include "InitializingState.h"
#include "../MassiveAttack.Client.Engine/Helpers/EventQueue.h"

ReturnSet<EventQueue> InitializingState::Init(string argument)
{
	try {
		auto eventQueue = EventQueue();

		return ReturnSet<EventQueue>(eventQueue);
	}
	catch (exception ex)
	{
		return ReturnSet<EventQueue>(ex);
	}
}
