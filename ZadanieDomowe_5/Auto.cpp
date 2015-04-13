#include"cAuto.h"
#include <GL/freeglut.h>
#include<math.h>
#include <iostream>

using namespace std;
cAuto::cAuto()
{
	pozycjax = 0;
	pozycjay = 0;
	szerokosc = 1.0;
	dlugosc = 0.5;
	kat = 0;
	kolorR = 1.0;
	kolorG = 0;
	kolorB = 0;


}

void cAuto::draw()		//rysowanie auta
{
	glPushMatrix();
	// TODO
	// test functions below (glTranslated, glRotated, glColor3d) - what happen when you change their arguments?
	// does their order change the result?
	glTranslated(pozycjax,pozycjay, 0.0);
	
	glRotated(kat, 0.0, 0.0, 1.0);

	glColor3d(kolorR, kolorG, kolorB);

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

bool cAuto::kolizjapunktu(float punktx,float punkty)		//kolizja auta z punktem
{
	float A[4], B[4], C[4];		//wspolczynniki rowanania prostej

	float x[4], y[4];		//cztery proste(przod ,tyl i boki auta. kazdy bok auta to inna prosta

	float odleglosc[4];    //odleglosc punktu od prostej

	float kat_rad = kat / 180.0*3.1415;		//zamiana stopni na radiany

	x[0] = cos(kat_rad)*(-szerokosc / 2) - sin(kat_rad)*(dlugosc / 2) + pozycjax;		//wyznacznie prostych. kazdy element tablicy to jedna prosta
	x[1] = cos(kat_rad)*(szerokosc / 2) - sin(kat_rad)*(dlugosc / 2) + pozycjax;
	x[2] = cos(kat_rad)*(szerokosc / 2) - sin(kat_rad)*(-dlugosc / 2) + pozycjax;
	x[3] = cos(kat_rad)*(-szerokosc / 2) - sin(kat_rad)*(-dlugosc / 2) + pozycjax;

	y[0] = sin(kat_rad)*(-szerokosc / 2) + cos(kat_rad)*(dlugosc / 2) + pozycjay;
	y[1] = sin(kat_rad)*(szerokosc / 2) + cos(kat_rad)*(dlugosc / 2) + pozycjay;
	y[2] = sin(kat_rad)*(szerokosc / 2) + cos(kat_rad)*(-dlugosc / 2) + pozycjay;
	y[3] = sin(kat_rad)*(-szerokosc / 2) + cos(kat_rad)*(-dlugosc / 2) + pozycjay;

	for (int i = 0; i < 4; i++)		//oblicznaie wspolczynnikow dla kazdej prostej
	{
		A[i] = (y[i] - y[(i + 1) % 4]);
		B[i] = (x[(i + 1) % 4] - x[i]);
		C[i] = (x[i] - x[(i + 1) % 4])*y[i] + (y[(i + 1) % 4] - y[i])*x[i];
		odleglosc[i] = abs(A[i] * punktx + B[i] * punkty + C[i]) / (sqrt(A[i] * A[i] + B[i] * B[i]));
		//std::cout << odleglosc[i] << " ";
	}
	//std::cout << std::endl;



	if (odleglosc[0] < dlugosc&&odleglosc[2] < dlugosc &&odleglosc[1] < szerokosc && odleglosc[3] < szerokosc)		//zwraca 1 jak zajdzie kolizja punktu z autem
	{
		return 1;
	}

	return 0;
}
bool cAuto::kolizja(cPrzeszkoda element)
{
	float A[4], B[4], C[4];		//tak samo jak z punktem ale tu robimy tak ze kolizja auta z cala przeszkoda

	float x[4], y[4];

	float odleglosc[4];

	float kat_rad = kat / 180.0*3.1415;

	x[0] = cos(kat_rad)*(-szerokosc / 2) - sin(kat_rad)*(dlugosc / 2) + pozycjax;
	x[1] = cos(kat_rad)*(szerokosc / 2) - sin(kat_rad)*(dlugosc / 2) + pozycjax;
	x[2] = cos(kat_rad)*(szerokosc / 2) - sin(kat_rad)*(-dlugosc / 2) + pozycjax;
	x[3] = cos(kat_rad)*(-szerokosc / 2) - sin(kat_rad)*(-dlugosc / 2) + pozycjax;

	y[0] = sin(kat_rad)*(-szerokosc / 2) + cos(kat_rad)*(dlugosc / 2) + pozycjay;
	y[1] = sin(kat_rad)*(szerokosc / 2) + cos(kat_rad)*(dlugosc / 2) + pozycjay;
	y[2] = sin(kat_rad)*(szerokosc / 2) + cos(kat_rad)*(-dlugosc / 2) + pozycjay;
	y[3] = sin(kat_rad)*(-szerokosc / 2) + cos(kat_rad)*(-dlugosc / 2) + pozycjay;

	for (int i = 0; i < 4; i++)
	{
		A[i] = (y[i] - y[(i + 1) % 4]);
		B[i] = (x[(i + 1) % 4] - x[i]);
		C[i] = (x[i] - x[(i + 1) % 4])*y[i] + (y[(i + 1) % 4] - y[i])*x[i];
	}

	const float raster = 0.05;		//podzielenie przeszkody na punkty(przeszkoda to zbior punktow)
	for (float x = 0.0; x <= element.szerokosc; x += raster)
	{
		for (float y = 0.0; y <= element.dlugosc; y += raster)
		{
			float punktx = x + element.pozycjax - element.szerokosc / 2;
			float punkty = y + element.pozycjay - element.dlugosc / 2;
			for (int i = 0; i < 4; i++)
			{

				odleglosc[i] = abs(A[i] * punktx + B[i] * punkty + C[i]) / (sqrt(A[i] * A[i] + B[i] * B[i]));
			}

			if (odleglosc[0] < dlugosc&&odleglosc[2] < dlugosc &&odleglosc[1] < szerokosc && odleglosc[3] < szerokosc)		//jak kolizja to zwraca 1 
			{
				return 1;
			}
		}
	}
	return 0;
}