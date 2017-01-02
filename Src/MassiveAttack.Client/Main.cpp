#include "../MassiveAttack.Client.Engine/Main.h"
#include "../MassiveAttack.Client.Engine/SDLWindow.h"

#pragma comment(lib, "../Debug/MassiveAttack.Client.Engine.lib")

int main(int argc, char *argv[])
{
	SDLWindow sdl_window;

	sdl_window.Init();

	sdl_window.MainLoop();

	return 0;
}