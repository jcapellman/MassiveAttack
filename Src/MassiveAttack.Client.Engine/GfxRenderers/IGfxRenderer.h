#pragma once

#ifndef __IGFXRENDERER__
#define __IGFXRENDERER__

#include "../Main.h"
#include "../Common/ReturnSet.h"
#include "../Helpers/RenderParameters.h"
#include "../Helpers/ModManager.h"
#include "../Managers/FontManager.h"

struct LEVELGEOMETRY;

class IGfxRenderer {
public:
	virtual string GetName() = 0;
	virtual ReturnSet<bool> Init(int width, int height, ModManager * modManager) = 0;
	virtual ReturnSet<bool> Shutdown() = 0;
	virtual ReturnSet<bool> LoadLevel(LEVELGEOMETRY * level) = 0;
	virtual void Render(RENDER_PARAMETERS rParams) = 0;
	virtual void ClearRenderQueue() = 0;
	virtual void AddUpdateText(string key, string content, string fontName, int x, int y, float size, SDL_Color foregroundColor) = 0;
private:
	virtual ReturnSet<int> LoadTexture(string fileName) = 0;
protected:
	FontManager * m_fontManager;
};

#endif