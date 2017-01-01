#pragma once

#ifndef __IGFXRENDERER__
#define __IGFXRENDERER__

#include "Main.h"
#include "ReturnSet.h"

class IGfxRenderer {
public:
	virtual string GetName() = 0;
	virtual ReturnSet<bool> Init(int width, int height) = 0;
	virtual ReturnSet<bool> Shutdown() = 0;
	virtual ReturnSet<bool> LoadGeometry(char * fileName) = 0;
	virtual void Render(float xpos, float zpos, float walkbias, float yrot) = 0;
private:
	virtual ReturnSet<int> LoadTexture(SDL_Surface * surface) = 0;
};

#endif