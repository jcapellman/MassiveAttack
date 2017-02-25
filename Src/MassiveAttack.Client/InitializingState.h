#ifndef __INITIALIZINGSTATE__
#define __INITIALIZINGSTATE__

#include "../MassiveAttack.Client.Engine/Interfaces/IGameStates.h"
#include "../MassiveAttack.Client.Engine/Helpers/EventQueue.h"

class InitializingState : public IGameStates
{
public:
	virtual ~InitializingState() = default;

	ReturnSet<EventQueue> Init(string argument) override;

	void PassKeyEvent(Sint32 sym, RENDER_PARAMETERS * render_parameters, EventQueue * eventQueue) override
	{
		// Do Nothing
	}

	void PassMouseEvent(float mouseX, Sint32 motionX, float mouseY, Sint32 motionY, RENDER_PARAMETERS * render_parameters) override 
	{
		// Do nothing
	}
};

#endif
