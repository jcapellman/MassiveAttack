#pragma once

#ifndef __OGL11RENDERER__
#define __OGL11RENDERER__

#include "IGfxRenderer.h"
#include <gl\gl.h>
#include <gl\glu.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")

typedef struct LEVELGEOMETRY
{
	char FileName[255];
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

class OGL11Renderer : public IGfxRenderer {
public:
	string GetName() {
		return "OpenGL 1.1";
	}

	ReturnSet<bool> Init(int width, int height);
	void Render(float xpos, float zpos, float walkbias, float yrot, float xrot);
	ReturnSet<bool> LoadGeometry(char * fileName);
	ReturnSet<bool> Shutdown();
private:
	ReturnSet<int> LoadTexture(const char * fileName);

	GLuint dlID;
};

#endif