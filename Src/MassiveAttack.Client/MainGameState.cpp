#include "MainGameState.h"

LEVELGEOMETRY* MainGameState::GetGeometry()
{
	return m_level;
}

ReturnSet<bool> MainGameState::Init(string argument)
{
	try {
		auto level = Level();

		auto levelResult = level.LoadLevel(const_cast<char*>(argument.c_str()));

		if (levelResult.HasError()) {
			throw exception(levelResult.ExceptionString().c_str());
		}

		m_level = levelResult.ReturnValue;

		return ReturnSet<bool>(true);
	} catch (exception ex)
	{
		return ReturnSet<bool>(ex);
	}
}

void MainGameState::PassKeyEvent(Sint32 sym, RENDER_PARAMETERS * render_parameters)
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

			break;
		case SDLK_s:
			xpos += static_cast<float>(sin(yrot * PIOVER180)) * 0.5f;
			zpos += static_cast<float>(cos(yrot * PIOVER180)) * 0.5f;

			render_parameters->SetParamFloat(RPARAM_XPOS, xpos);
			render_parameters->SetParamFloat(RPARAM_ZPOS, zpos);

			break;
		default:
			break;
	}
}