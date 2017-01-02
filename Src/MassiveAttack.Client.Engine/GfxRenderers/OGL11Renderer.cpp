#include "OGL11Renderer.h"

ReturnSet<int> OGL11Renderer::LoadTexture(SDL_Surface * surface) {
	GLuint textureID;

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

	SDL_FreeSurface(surface);

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
	dlID = glGenLists(1);

	glNewList(dlID, GL_COMPILE);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.1f, 0.1f);

	glVertex3f(100.0f, -1.0f, 100.0f);
	glVertex3f(100.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.4f, 0.4f);

	glVertex3f(100.0f, 5.0f, 100.0f);
	glVertex3f(100.0f, 5.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.6f);

	glVertex3f(100.0f, 5.0f, 100.0f);
	glVertex3f(100.0f, -1.0f, 100.0f);
	glVertex3f(0.0f, -1.0f, 100.0f);
	glVertex3f(0.0f, 5.0f, 100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.6f, 1.0f, 0.6f);

	glVertex3f(100.0f, 5.0f, 0.0f);
	glVertex3f(100.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glEnd();

	glEndList();

	return ReturnSet<bool>(true);
}