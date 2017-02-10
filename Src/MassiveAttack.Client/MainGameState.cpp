#include "MainGameState.h"

LEVELGEOMETRY* MainGameState::GetGeometry()
{
	return m_level;
}

bool MainGameState::Init()
{
	Level level;

	auto levelResult = level.LoadLevel("E1M1.map");

	if (levelResult.HasError()) {
		return false;
	}

	return true;
}
