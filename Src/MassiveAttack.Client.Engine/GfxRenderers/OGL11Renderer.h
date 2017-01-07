#pragma once

#ifndef __OGL11RENDERER__
#define __OGL11RENDERER__

#include "IGfxRenderer.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include <unordered_map>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")

#include "../Level.h"

class OGL11Renderer : public IGfxRenderer {
public:
	string GetName() {
		return "OpenGL 1.1";
	}

	ReturnSet<bool> Init(int width, int height);
	void Render(float xpos, float zpos, float walkbias, float yrot, float xrot);
	ReturnSet<bool> LoadGeometry(LEVELGEOMETRY * level);
	ReturnSet<bool> Shutdown();
private:
	ReturnSet<int> LoadTexture(const char * fileName);
	void LoadTextureDefinitions();

	GLuint dlID;

	unordered_map<int, string> _textureDB;
};

#endif