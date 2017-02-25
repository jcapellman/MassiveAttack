#include "../MassiveAttack.Client.Engine/Main.h"
#include "../MassiveAttack.Client.Engine/SDLWindow.h"
#include "MainGameState.h"
#include <iostream>

#pragma comment(lib, "../Debug/MassiveAttack.Client.Engine.lib")

int main(int argc, char *argv[])
{
	SDLWindow sdl_window;
	auto errLogger = ErrorLogger();

	sdl_window.Init("Massive Attack");
	
	auto main_game_state = new MainGameState();
	
	auto initresult = main_game_state->Init("E1M1.map");

	if (initresult.HasError())
	{
		errLogger.WriteError("Failed to load level: " + initresult.ExceptionString());

		return 0;
	}
	
	sdl_window.SetGameState(main_game_state, initresult.ReturnValue);
	
	sdl_window.MainLoop();

	return 0;
}