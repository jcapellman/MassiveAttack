#pragma once

#ifndef __OGL11RENDERER__
#define __OGL11RENDERER__

#include "IGfxRenderer.h"
#include <gl\gl.h>
#include <gl\glu.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")

class OGL11Renderer : public IGfxRenderer {
public:
	string GetName() {
		return "OpenGL 1.1";
	}

	ReturnSet<bool> Init(int width, int height);
	void Render(float xpos, float zpos, float walkbias, float yrot, float xrot);
	ReturnSet<bool> LoadGeometry(char * fileName);
	ReturnSet<int> LoadTexture(char * fileName);
	ReturnSet<bool> Shutdown();
private:
	GLuint dlID;
};

#endif