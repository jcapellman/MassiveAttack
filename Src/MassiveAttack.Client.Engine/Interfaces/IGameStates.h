#ifndef __IGAMESTATES__
#define __IGAMESTATES__

#include "../Helpers/Level.h"
#include "../Helpers/EventQueue.h"
#include <stack>

class IGameStates {
protected:
	~IGameStates() = default;
public:
	virtual LEVELGEOMETRY* GetGeometry() = 0;
	virtual ReturnSet<EventQueue> Init(string argument) = 0;
	virtual void PassKeyEvent(Sint32 sym, RENDER_PARAMETERS * render_parameters, EventQueue * eventQueue) = 0;
	virtual void PassMouseEvent(float mouseX, Sint32 motionX, float mouseY, Sint32 motionY, RENDER_PARAMETERS * render_parameters) = 0;
};

#endif