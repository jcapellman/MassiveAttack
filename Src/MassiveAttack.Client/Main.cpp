#include "../MassiveAttack.Client.Engine/Main.h"
#include "../MassiveAttack.Client.Engine/SDLWindow.h"
#include "MainGameState.h"
#include <iostream>

#pragma comment(lib, "../Debug/MassiveAttack.Client.Engine.lib")

int main(int argc, char *argv[])
{
	SDLWindow sdl_window;

	sdl_window.Init("Massive Attack");
	
	auto main_game_state = new MainGameState();
	
	if (!main_game_state->Init("E1M1.map"))
	{
		cout << "Failed to load level" << endl;

		return 0;
	}
	
	sdl_window.SetGameState(main_game_state);
	
	sdl_window.MainLoop();

	return 0;
}