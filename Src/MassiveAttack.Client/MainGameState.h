#ifndef __MAINGAMESTATE__
#define __MAINGAMESTATE__

#include "../MassiveAttack.Client.Engine/IGameStates.h"
#include "../MassiveAttack.Client.Engine/Level.h"

class MainGameState : public IGameStates
{
public:
	LEVELGEOMETRY* GetGeometry();

	bool Init(string argument);
private:
	LEVELGEOMETRY * m_level;
};

#endif
