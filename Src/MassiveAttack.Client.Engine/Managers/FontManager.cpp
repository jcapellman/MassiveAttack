#include "FontManager.h"
#include <SDL.h>
#include "../Common/ReturnSet.h"

ReturnSet<SDL_Surface*> FontManager::RenderText(string fontName, string text, int size, SDL_Color foregroundColor) const
{
	fontName = m_modManager->GetPath(FONTS, fontName);

	auto font = TTF_OpenFont(fontName.c_str(), size);

	auto textSurface = TTF_RenderText_Blended(font, text.c_str(), foregroundColor);
	
	SDL_SetSurfaceAlphaMod(textSurface, 0xFF);
	SDL_SetColorKey(textSurface, SDL_TRUE, 0xFF);

	return ReturnSet<SDL_Surface*>(textSurface);
}
