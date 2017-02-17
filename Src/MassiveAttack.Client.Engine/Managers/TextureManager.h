#ifndef __TEXTUREMANAGER__
#define __TEXTUREMANAGER__

#include "../Main.h"
#include "../Common/ReturnSet.h"

class TextureManager
{
public:
	static ReturnSet<SDL_Surface*> LoadTexture(char * fileName);
};

#endif