#pragma once

#ifndef __OGL11RENDERER__
#define __OGL11RENDERER__

#include "IGfxRenderer.h"
#include <gl\gl.h>
#include <gl\glu.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")

#include "../Level.h"

class OGL11Renderer : public IGfxRenderer {
public:
	string GetName() {
		return "OpenGL 1.1";
	}

	ReturnSet<bool> Init(int width, int height);
	void Render(RENDER_PARAMETERS rParams);
	ReturnSet<bool> LoadGeometry(LEVELGEOMETRY * level);
	ReturnSet<bool> Shutdown();
private:
	ReturnSet<int> LoadTexture(string fileName);
	void LoadTextureDefinitions();

	unordered_map<int, string> _textureDB;
	vector<GLuint> m_displayLists;
};

#endif