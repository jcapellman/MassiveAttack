#ifndef __LEVEL__
#define __LEVEL__

#include "../Common/ReturnSet.h"
#include "../GfxRenderers/IGfxRenderer.h"
#include "../Common/ReturnSet.h"
#include "ModManager.h"

struct LEVELGEOMETRY
{
	int textureID;
	int Scale;

	float X1;
	float Y1;
	float Z1;

	float X2;
	float Y2;
	float Z2;

	float X3;
	float Y3;
	float Z3;

	float X4;
	float Y4;
	float Z4;
};

class Level {
	public:
		explicit Level(ModManager * modManager)
		{
			m_modManager = modManager;
		}

		ReturnSet<LEVELGEOMETRY*> LoadLevel(string fileName);

		string GetSkyBoxTexture() const
		{
			return m_skybox_name;
		}
	private:
		ModManager * m_modManager;

		string m_skybox_name;
};

#endif