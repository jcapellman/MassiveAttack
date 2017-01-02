#pragma once

#ifndef __ISFXRENDERER__
#define __ISFXRENDERER__

#include "../Main.h"
#include "../Common/ReturnSet.h"

class ISfxRenderer {
public:
	virtual string GetName() = 0;
	virtual ReturnSet<bool> Init() = 0;
	virtual ReturnSet<bool> Shutdown() = 0;
	virtual ReturnSet<int> LoadSound(char * fileName) = 0;
	virtual void PlaySound(int soundID) = 0;
};

#endif