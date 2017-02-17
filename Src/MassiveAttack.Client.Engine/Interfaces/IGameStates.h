#ifndef __IGAMESTATES__
#define __IGAMESTATES__

#include "../Helpers/Level.h"

class IGameStates {
protected:
	~IGameStates() = default;
public:
	virtual LEVELGEOMETRY* GetGeometry() = 0;
	virtual ReturnSet<bool> Init(string argument) = 0;
};

#endif