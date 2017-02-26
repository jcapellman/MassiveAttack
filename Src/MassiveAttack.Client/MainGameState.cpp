#include "MainGameState.h"
#include "../MassiveAttack.Client.Engine/Helpers/EventQueue.h"

ReturnSet<EventQueue> MainGameState::Init(string argument)
{
	try {
		auto eventQueue = EventQueue();

		eventQueue.AddEvent(LEVEL_LOAD, argument);
		eventQueue.AddEvent(AUDIO_LOAD_SOUND, "player/Footstep.wav");
		eventQueue.AddEvent(AUDIO_LOAD_SOUND, "player/Backstep.wav");
		//eventQueue.AddEvent(TEXT_ADD, "Testing");

		return ReturnSet<EventQueue>(eventQueue);
	} catch (exception ex)
	{
		return ReturnSet<EventQueue>(ex);
	}
}

void MainGameState::PassMouseEvent(float mouseX, Sint32 motionX, float mouseY, Sint32 motionY, RENDER_PARAMETERS * render_parameters)
{
	// TODO Add Gun Aiming
}

void MainGameState::PassKeyEvent(Sint32 sym, RENDER_PARAMETERS * render_parameters, EventQueue * eventQueue)
{
	auto xpos = render_parameters->GetParamFloat(RPARAM_XPOS);

	switch (sym) {
		case SDLK_a:
			xpos -= 0.5f;

			render_parameters->SetParamFloat(RPARAM_XPOS, xpos);
		
			eventQueue->AddEvent(AUDIO_PLAY_SOUND, "player/Backstep.wav");

			break;
		case SDLK_d:
			xpos += 0.5f;

			render_parameters->SetParamFloat(RPARAM_XPOS, xpos);
			eventQueue->AddEvent(AUDIO_PLAY_SOUND, "player/Footstep.wav");

			break;		
		default:
			break;
	}
}