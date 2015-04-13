#include"cPrzeszkoda.h"
#include <GL/freeglut.h>

cPrzeszkoda::cPrzeszkoda()
{
	pozycjax = 0;
	pozycjay = 0;
	szerokosc = 0;
	dlugosc = 0;
}

cPrzeszkoda::cPrzeszkoda(float _pozycjax, float _pozycjay, float _szerokosc, float _dlugosc)
{
	pozycjax = _pozycjax;
	pozycjay = _pozycjay;
	szerokosc = _szerokosc;
	dlugosc = _dlugosc;
}

void cPrzeszkoda::draw()		//rysowanie przeszkody
{
	glPushMatrix();
	// TODO
	// test functions below (glTranslated, glRotated, glColor3d) - what happen when you change their arguments?
	// does their order change the result?
	glTranslated(pozycjax, pozycjay, 0.0);
	//glRotated(0, 1.0, 0.0, 0.0);
	//glRotated(0, 0.0, 1.0, 0.0);
	//glRotated(0, 0.0, 0.0, 1.0);

	

	glColor3d(0.7, 0.0, 0.5);

	glBegin(GL_POLYGON);
	{
		glVertex3d(-szerokosc / 2, dlugosc / 2, 0);
		glVertex3d(szerokosc / 2, dlugosc/ 2, 0);
		glVertex3d(szerokosc / 2, -dlugosc / 2, 0);
		glVertex3d(-szerokosc / 2, -dlugosc / 2, 0);
	}
	glEnd();
	glPopMatrix();
}

void cPrzeszkoda::drawbonuszolty()
{
	glPushMatrix();
	// TODO
	// test functions below (glTranslated, glRotated, glColor3d) - what happen when you change their arguments?
	// does their order change the result?
	glTranslated(pozycjax, pozycjay, 0.0);
	//glRotated(0, 1.0, 0.0, 0.0);
	//glRotated(0, 0.0, 1.0, 0.0);
	//glRotated(0, 0.0, 0.0, 1.0);

	

	glColor3d(1.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	{
		glVertex3d(-szerokosc / 2, dlugosc / 2, 0);
		glVertex3d(szerokosc / 2, dlugosc / 2, 0);
		glVertex3d(szerokosc / 2, -dlugosc / 2, 0);
		glVertex3d(-szerokosc / 2, -dlugosc / 2, 0);
	}
	glEnd();
	glPopMatrix();
}

void cPrzeszkoda::drawbonusziolony()
{
	glPushMatrix();
	// TODO
	// test functions below (glTranslated, glRotated, glColor3d) - what happen when you change their arguments?
	// does their order change the result?
	glTranslated(pozycjax, pozycjay, 0.0);
	//glRotated(0, 1.0, 0.0, 0.0);
	//glRotated(0, 0.0, 1.0, 0.0);
	//glRotated(0, 0.0, 0.0, 1.0);



	glColor3d(0.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	{
		glVertex3d(-szerokosc / 2, dlugosc / 2, 0);
		glVertex3d(szerokosc / 2, dlugosc / 2, 0);
		glVertex3d(szerokosc / 2, -dlugosc / 2, 0);
		glVertex3d(-szerokosc / 2, -dlugosc / 2, 0);
	}
	glEnd();
	glPopMatrix();
}


void cPrzeszkoda::drawbonusczerwony()
{
	glPushMatrix();
	// TODO
	// test functions below (glTranslated, glRotated, glColor3d) - what happen when you change their arguments?
	// does their order change the result?
	glTranslated(pozycjax, pozycjay, 0.0);
	//glRotated(0, 1.0, 0.0, 0.0);
	//glRotated(0, 0.0, 1.0, 0.0);
	//glRotated(0, 0.0, 0.0, 1.0);



	glColor3d(1.0, 0.0, 0.0);

	glBegin(GL_POLYGON);
	{
		glVertex3d(-szerokosc / 2, dlugosc / 2, 0);
		glVertex3d(szerokosc / 2, dlugosc / 2, 0);
		glVertex3d(szerokosc / 2, -dlugosc / 2, 0);
		glVertex3d(-szerokosc / 2, -dlugosc / 2, 0);
	}
	glEnd();
	glPopMatrix();
}