#ifndef __TEXTUREMANAGER__
#define __TEXTUREMANAGER__

#include "Main.h"
#include "ReturnSet.h"

class TextureManager
{
public:
	ReturnSet<SDL_Surface*> LoadTexture(char * fileName);
};

#endif