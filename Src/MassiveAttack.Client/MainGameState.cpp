#include "MainGameState.h"

LEVELGEOMETRY* MainGameState::GetGeometry()
{
	return m_level;
}

bool MainGameState::Init(string argument)
{
	Level level;

	auto levelResult = level.LoadLevel((char*)argument.c_str());

	if (levelResult.HasError()) {
		return false;
	}

	return true;
}
