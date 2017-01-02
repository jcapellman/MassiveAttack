#include "MainExport.h"
#include "SDLWindow.h"

#include "GfxRenderers/OGL11Renderer.h"

MASSIVEATTACKENGINE_API void MassiveAttackClientEngine::MainEngine::RunEngine()
{
	SDLWindow sdlWindow;

	sdlWindow.Init();

	sdlWindow.MainLoop();
}

MASSIVEATTACKENGINE_API const char * MassiveAttackClientEngine::MainEngine::GetAvailableGfxRenderers()
{
	OGL11Renderer ogl11_renderer;

	return ogl11_renderer.GetName().c_str();
}