#pragma once

#ifndef __ISFXRENDERER__
#define __ISFXRENDERER__

#include "../Main.h"
#include "../Common/ReturnSet.h"

class ISfxRenderer {
public:
	virtual string GetName() = 0;
	virtual ReturnSet<bool> Init(int numChannels) = 0;
	virtual ReturnSet<bool> Shutdown() = 0;
	virtual ReturnSet<bool> Load(string fileName) = 0;
	virtual void Play(string fileName, bool loop = false) = 0;
};

#endif