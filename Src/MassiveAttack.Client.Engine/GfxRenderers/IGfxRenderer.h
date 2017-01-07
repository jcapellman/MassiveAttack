#pragma once

#ifndef __IGFXRENDERER__
#define __IGFXRENDERER__

#include "../Main.h"
#include "../Common/ReturnSet.h"

struct LEVELGEOMETRY;

class IGfxRenderer {
public:
	virtual string GetName() = 0;
	virtual ReturnSet<bool> Init(int width, int height) = 0;
	virtual ReturnSet<bool> Shutdown() = 0;
	virtual ReturnSet<bool> LoadGeometry(LEVELGEOMETRY * level) = 0;
	virtual void Render(float xpos, float zpos, float walkbias, float yrot, float xrot) = 0;
private:
	virtual ReturnSet<int> LoadTexture(const char * fileName) = 0;
};

#endif