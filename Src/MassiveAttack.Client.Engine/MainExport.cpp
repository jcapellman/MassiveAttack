#include "MainExport.h"
#include "SDLWindow.h"

MASSIVEATTACKENGINE_API void MassiveAttackClientEngine::MainEngine::RunEngine()
{
	SDLWindow sdlWindow;

	sdlWindow.Init();

	sdlWindow.MainLoop();
}
