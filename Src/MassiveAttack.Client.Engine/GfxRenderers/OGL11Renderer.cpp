#include "OGL11Renderer.h"
#include "../TextureManager.h"

ReturnSet<int> OGL11Renderer::LoadTexture(char * fileName) {
	TextureManager tm;

	ReturnSet<SDL_Surface*> result = tm.LoadTexture(fileName);

	if (result.HasError())
	{
		return ReturnSet<int>(-1);
	}

	GLuint textureID;

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, result.ReturnValue->w, result.ReturnValue->h, 0, GL_RGB, GL_UNSIGNED_BYTE, result.ReturnValue->pixels);

	SDL_FreeSurface(result.ReturnValue);

	return ReturnSet<int>(textureID);
}

ReturnSet<bool> OGL11Renderer::Shutdown() {
	glDeleteLists(this->dlID, 1);

	return ReturnSet<bool>(true);
}

ReturnSet<bool> OGL11Renderer::Init(int width, int height) {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return ReturnSet<bool>(true);
}

void OGL11Renderer::Render(float xpos, float zpos, float walkbias, float yrot, float xrot) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	GLfloat xtrans = -xpos;
	GLfloat ztrans = -zpos;
	GLfloat ytrans = -walkbias - 0.25f;
	GLfloat sceneroty = 0 - yrot;

	glRotatef(xrot, 1.0f, 0, 0);
	glRotatef(sceneroty, 0, 1.0f, 0);

	glTranslatef(xtrans, 0.0f, ztrans);

	glCallList(dlID);
}

ReturnSet<bool> OGL11Renderer::LoadGeometry(char * fileName) {
	ReturnSet<int> floorResult = LoadTexture("floor.bmp");
	ReturnSet<int> ceilingResult = LoadTexture("ceiling.bmp");

	dlID = glGenLists(1);

	glNewList(dlID, GL_COMPILE);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, floorResult.ReturnValue);

	// Ground
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(100.0f, -1.0f, 100.0f);

		glTexCoord2f(0.0, 20.0);
		glVertex3f(100.0f, -1.0f, 0.0f);

		glTexCoord2f(20, 20);
		glVertex3f(0.0f, -1.0f, 0.0f);

		glTexCoord2f(20, 0.0);
		glVertex3f(0.0f, -1.0f, 100.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, ceilingResult.ReturnValue);

	// Roof
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(100.0f, 5.0f, 100.0f);

		glTexCoord2f(0.0, 5.0);
		glVertex3f(100.0f, 5.0f, 0.0f);

		glTexCoord2f(5.0, 5.0);
		glVertex3f(0.0f, 5.0f, 0.0f);

		glTexCoord2f(5.0, 0.0);
		glVertex3f(0.0f, 5.0f, 100.0f);
	glEnd();

	// Front Wall
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(100.0f, 5.0f, 100.0f);

		glTexCoord2f(0.0, 5.0);
		glVertex3f(100.0f, -1.0f, 100.0f);

		glTexCoord2f(5.0, 5.0);
		glVertex3f(0.0f, -1.0f, 100.0f);

		glTexCoord2f(.0, 0.0);
		glVertex3f(0.0f, 5.0f, 100.0f);
	glEnd();

	// Back Wall
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(100.0f, 5.0f, 0.0f);

		glTexCoord2f(0.0, 5.0);
		glVertex3f(100.0f, -1.0f, 0.0f);
	
		glTexCoord2f(5.0, 5.0);
		glVertex3f(0.0f, -1.0f, 0.0f);
	
		glTexCoord2f(5.0, 0.0);
		glVertex3f(0.0f, 5.0f, 0.0f);
	glEnd();

	glEndList();

	return ReturnSet<bool>(true);
}