#pragma once

#ifndef __ISFXRENDERER__
#define __ISFXRENDERER__

#include "../Main.h"
#include "../Common/ReturnSet.h"
#include "../Helpers/ModManager.h"

class ISfxRenderer {
public:
	virtual string GetName() = 0;
	virtual ReturnSet<bool> Init(int numChannels, ModManager * modManager) = 0;
	virtual ReturnSet<bool> Shutdown() = 0;
	virtual ReturnSet<bool> LoadSound(string fileName) = 0;
	virtual ReturnSet<bool> LoadMusic(string fileName) = 0;
	virtual void PlaySound(string fileName, bool loop = false) = 0;
	virtual void PlayMusic() = 0;
};

#endif