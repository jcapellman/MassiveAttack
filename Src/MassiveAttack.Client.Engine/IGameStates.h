#ifndef __IGAMESTATES__
#define __IGAMESTATES__

#include "Level.h"

class IGameStates {
protected:
	~IGameStates() = default;
public:
	virtual LEVELGEOMETRY* GetGeometry() = 0;
	virtual bool Init(string argument) = 0;
};

#endif