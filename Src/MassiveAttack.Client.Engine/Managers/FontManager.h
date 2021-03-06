#ifndef __FONTMANAGER__
#define __FONTMANAGER__

#include "../Main.h"
#include "../Common/ReturnSet.h"
#include "../Helpers/ModManager.h"

class FontManager
{
public:
	explicit FontManager(ModManager * modManager)
	{
		m_modManager = modManager;
	}

	ReturnSet<SDL_Surface*> RenderText(string fontName, string text, int size, SDL_Color foregroundColor) const;
private:
	ModManager * m_modManager;
};

#endif