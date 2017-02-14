#ifndef __MAINGAMESTATE__
#define __MAINGAMESTATE__

#include "../MassiveAttack.Client.Engine/IGameStates.h"
#include "../MassiveAttack.Client.Engine/Level.h"

class MainGameState : public IGameStates
{
public:
	virtual ~MainGameState() = default;
	LEVELGEOMETRY* GetGeometry() override;

	bool Init(string argument) override;

	MainGameState()
	{
		m_level = nullptr;
	}
private:
	LEVELGEOMETRY * m_level;
};

#endif
