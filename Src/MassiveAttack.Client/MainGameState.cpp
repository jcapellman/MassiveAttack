#include "MainGameState.h"
#include "../MassiveAttack.Client.Engine/Helpers/EventQueue.h"

ReturnSet<EventQueue> MainGameState::Init(string argument)
{
	try {
		auto eventQueue = EventQueue();

		eventQueue.AddEvent(LEVEL_LOAD, argument);
		eventQueue.AddEvent(AUDIO_LOAD_SOUND, "player/Footstep.wav");
		eventQueue.AddEvent(AUDIO_LOAD_SOUND, "player/Backstep.wav");

		return ReturnSet<EventQueue>(eventQueue);
	} catch (exception ex)
	{
		return ReturnSet<EventQueue>(ex);
	}
}

void MainGameState::PassMouseEvent(float mouseX, Sint32 motionX, float mouseY, Sint32 motionY, RENDER_PARAMETERS * render_parameters)
{
	if (mouseX != motionX) {
		auto yrot = render_parameters->GetParamFloat(RPARAM_YROT);

		if (mouseX > motionX)
		{
			yrot += 0.5f;
		}
		else
		{	
			yrot -= 0.5f;
		}

		render_parameters->SetParamFloat(RPARAM_YROT, yrot);
	}

	if (mouseY != motionY) {
		auto xrot = render_parameters->GetParamFloat(RPARAM_XROT);

		if (mouseY > motionY && xrot > -100)
		{
			xrot -= 0.5f;
		}
		else if (mouseY < motionY && xrot < 100)
		{
			xrot += 0.5f;
		}

		render_parameters->SetParamFloat(RPARAM_XROT, xrot);
	}
}

void MainGameState::PassKeyEvent(Sint32 sym, RENDER_PARAMETERS * render_parameters, EventQueue * eventQueue)
{
	auto yrot = render_parameters->GetParamFloat(RPARAM_YROT);
	auto xpos = render_parameters->GetParamFloat(RPARAM_XPOS);
	auto zpos = render_parameters->GetParamFloat(RPARAM_ZPOS);

	switch (sym) {
		case SDLK_RIGHT:
			render_parameters->SetParamFloat(RPARAM_YROT, yrot - 1.5f);
			break;
		case SDLK_LEFT:
			render_parameters->SetParamFloat(RPARAM_YROT, yrot + 1.5f);
			break;
		case SDLK_a:
			xpos -= static_cast<float>(sin(yrot * PIOVER180)) * 10.5f;
			zpos += static_cast<float>(cos(yrot * PIOVER180)) * 0.5f;

			render_parameters->SetParamFloat(RPARAM_XPOS, xpos);
			render_parameters->SetParamFloat(RPARAM_ZPOS, zpos);

			break;
		case SDLK_d:
			xpos += static_cast<float>(sin(yrot * PIOVER180)) * 10.5f;
			zpos -= static_cast<float>(cos(yrot * PIOVER180)) * 0.5f;

			render_parameters->SetParamFloat(RPARAM_XPOS, xpos);
			render_parameters->SetParamFloat(RPARAM_ZPOS, zpos);

			break;
		case SDLK_w:
			xpos -= static_cast<float>(sin(yrot * PIOVER180)) * 0.5f;
			zpos -= static_cast<float>(cos(yrot * PIOVER180)) * 0.5f;

			render_parameters->SetParamFloat(RPARAM_XPOS, xpos);
			render_parameters->SetParamFloat(RPARAM_ZPOS, zpos);

			eventQueue->AddEvent(AUDIO_PLAY_SOUND, "player/Footstep.wav");
			break;
		case SDLK_s:
			xpos += static_cast<float>(sin(yrot * PIOVER180)) * 0.5f;
			zpos += static_cast<float>(cos(yrot * PIOVER180)) * 0.5f;

			render_parameters->SetParamFloat(RPARAM_XPOS, xpos);
			render_parameters->SetParamFloat(RPARAM_ZPOS, zpos);

			eventQueue->AddEvent(AUDIO_PLAY_SOUND, "player/Backstep.wav");

			break;
		default:
			break;
	}
}