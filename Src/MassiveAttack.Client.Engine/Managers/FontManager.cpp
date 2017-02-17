#include "FontManager.h"
#include <SDL.h>
#include "../Common/ReturnSet.h"

ReturnSet<SDL_Surface*> FontManager::RenderText(string fontName, char * text, int size, SDL_Color foregroundColor, SDL_Color backgroundColor)
{
	fontName = FONTS_ROOT_PATH + fontName;

	auto font = TTF_OpenFont(fontName.c_str(), size);

	auto textSurface = TTF_RenderText_Shaded(font, text, foregroundColor, backgroundColor);

	return ReturnSet<SDL_Surface*>(textSurface);
}
