#ifndef __MAINGAMESTATE__
#define __MAINGAMESTATE__

#include "../MassiveAttack.Client.Engine/Helpers/Level.h"
#include "../MassiveAttack.Client.Engine/Interfaces/IGameStates.h"
#include "../MassiveAttack.Client.Engine/Helpers/EventQueue.h"
#include <stack>

class MainGameState : public IGameStates
{
public:
	virtual ~MainGameState() = default;
	LEVELGEOMETRY* GetGeometry() override;

	ReturnSet<EventQueue> Init(string argument) override;

	void PassKeyEvent(Sint32 sym, RENDER_PARAMETERS * render_parameters, EventQueue * eventQueue) override;
	void PassMouseEvent(float mouseX, Sint32 motionX, float mouseY, Sint32 motionY, RENDER_PARAMETERS * render_parameters) override;

	MainGameState()
	{
		m_level = nullptr;
	}
private:
	LEVELGEOMETRY * m_level;
};

#endif
