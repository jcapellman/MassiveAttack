#ifndef __FONTMANAGER__
#define __FONTMANAGER__

#include "Main.h"
#include "Common/ReturnSet.h"

class FontManager
{
public:
	static ReturnSet<SDL_Surface*> RenderText(string fontName, char * text, int size, SDL_Color foregroundColor, SDL_Color backgroundColor);
};

#endif