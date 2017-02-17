#ifndef __MAINGAMESTATE__
#define __MAINGAMESTATE__

#include "../MassiveAttack.Client.Engine/Helpers/Level.h"
#include "../MassiveAttack.Client.Engine/Interfaces/IGameStates.h"

class MainGameState : public IGameStates
{
public:
	virtual ~MainGameState() = default;
	LEVELGEOMETRY* GetGeometry() override;

	ReturnSet<bool> Init(string argument) override;

	MainGameState()
	{
		m_level = nullptr;
	}
private:
	LEVELGEOMETRY * m_level;
};

#endif
