#include "../MassiveAttack.Client.Engine/Main.h"
#include "../MassiveAttack.Client.Engine/SDLWindow.h"

int main(int argc, char *argv[])
{
	SDLWindow sdlWindow;

	sdlWindow.Init();

	sdlWindow.MainLoop();

	return 0;
}