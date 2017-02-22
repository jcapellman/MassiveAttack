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
	virtual ReturnSet<int> Load(char * fileName) = 0;
	virtual void Play(int soundID, bool loop = false) = 0;
};

#endif