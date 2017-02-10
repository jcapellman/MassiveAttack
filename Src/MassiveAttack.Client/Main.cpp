#include "../MassiveAttack.Client.Engine/Main.h"
#include "../MassiveAttack.Client.Engine/SDLWindow.h"
#include "MainGameState.h"
#include <iostream>

#pragma comment(lib, "../Debug/MassiveAttack.Client.Engine.lib")

int main(int argc, char *argv[])
{
	SDLWindow sdl_window;

	sdl_window.Init();

	MainGameState * main_game_state;

	if (!main_game_state->Init())
	{
		cout << "Failed to hit game state" << endl;

		return 0;
	}

	sdl_window.SetGameState(main_game_state);

	sdl_window.MainLoop();

	return 0;
}