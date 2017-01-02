#include "MainExport.h"
#include "SDLWindow.h"

#include "GfxRenderers/OGL11Renderer.h"

void RunEngine()
{
	SDLWindow sdlWindow;

	sdlWindow.Init();

	sdlWindow.MainLoop();
}

const char * GetAvailableGfxRenderers()
{
	OGL11Renderer ogl11_renderer;

	return ogl11_renderer.GetName().c_str();
}