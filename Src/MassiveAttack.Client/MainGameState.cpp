#include "MainGameState.h"

LEVELGEOMETRY* MainGameState::GetGeometry()
{
	return m_level;
}

ReturnSet<bool> MainGameState::Init(string argument)
{
	try {
		auto level = Level();

		auto levelResult = level.LoadLevel(const_cast<char*>(argument.c_str()));

		if (levelResult.HasError()) {
			return ReturnSet<bool>(false);
		}

		m_level = levelResult.ReturnValue;

		return ReturnSet<bool>(true);
	} catch (exception ex)
	{
		return ReturnSet<bool>(ex);
	}
}
