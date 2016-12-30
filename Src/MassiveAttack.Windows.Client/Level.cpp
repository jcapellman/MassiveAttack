#include "Level.h"

GLuint Level::LoadLevel(char* fileName)
{
	GLuint dlID = glGenLists(1);

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

	return dlID;
}