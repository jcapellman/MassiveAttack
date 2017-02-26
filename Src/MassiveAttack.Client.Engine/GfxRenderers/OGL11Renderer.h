#pragma once

#ifndef __OGL11RENDERER__
#define __OGL11RENDERER__

#include "IGfxRenderer.h"
#include <gl\gl.h>
#include <gl\glu.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")

#include "../Helpers/Level.h"
#include "../Helpers/ModManager.h"

class OGL11Renderer : public IGfxRenderer {
public:
	string GetName() override
	{
		return "OpenGL 1.1";
	}

	ReturnSet<bool> Init(int width, int height, ModManager * modManager) override;
	void Render(RENDER_PARAMETERS rParams) override;
	ReturnSet<bool> LoadLevel(LEVELGEOMETRY * level) override;
	void AddUpdateText(string key, string content, string fontName, int x, int y, float size, SDL_Color foregroundColor) override;
	ReturnSet<bool> Shutdown() override;
	void ClearRenderQueue() override;
private:
	static GLenum getTextureFormat(Uint8 bpp, Uint32 rmask);

	ReturnSet<int> LoadTexture(string fileName) override;
	void LoadTextureDefinitions();

	unordered_map<int, string> _textureDB;
	vector<GLuint> m_displayLists;

	ModManager * m_modManager;

	int m_width;
	int m_height;
};

#endif