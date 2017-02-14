#include "MainGameState.h"

LEVELGEOMETRY* MainGameState::GetGeometry()
{
	return m_level;
}

bool MainGameState::Init(string argument)
{
	auto level = Level();

	auto levelResult = level.LoadLevel(const_cast<char*>(argument.c_str()));

	if (levelResult.HasError()) {
		return false;
	}

	m_level = levelResult.ReturnValue;

	return true;
}
