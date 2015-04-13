//author: Michal Witkowski
#include <iostream>
#include "cAuto.h"
#include "cPrzeszkoda.h"
#include <GL/freeglut.h>
#include<time.h>
#include <list>

int widthh = 1;		//zmienna globalna do ustalenia wspolrzednych z pikseli na swiat open GL
int heightt = 1;	//zmienna globalna do ustalenia wspolrzednych z pikseli na swiat open GL
float V;		//zmienna przechowujaca predkosc

using namespace std;
list<cPrzeszkoda> przeszkody;	//lista przeszkod
list<cPrzeszkoda> sciany;		//lista scian
list<cPrzeszkoda> bonuskolor;	//lista bonusu zmieniajacego kolor
list<cPrzeszkoda> bonuswielkosc;		//lista bonusu zmianiajacego wielkosc
list<cPrzeszkoda> bonuspredkosc;	//lista bonusu zmieniajacego predkoss
int czasprzeszkody = 0;			//zmienne przechowujaca czas ostatniego dodania 
int czaskolorbonus = 0;
int czaswielkoscbonus = 0;
int czaspredkoscbonus = 0;
cAuto pojazd;
/* GLUT callback Handlers */
static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;
	widthh = width;
	heightt = height;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void idle(void)
{
	glutPostRedisplay();
}



static void display(void)
{
	// clear the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	pojazd.draw();
	///////////////////////////////////////////////////przeszkody
	for (list<cPrzeszkoda>::iterator it = przeszkody.begin(); it != przeszkody.end(); it++)	//iterowanie po liscie przeszkod
	{
		it->draw();		//rysowanie przeszkody
		if (pojazd.kolizja(*it))	//jak kolizja to przeszkoda sie usuwa a autoa wraca do poczatku ukladu wspolrzednych
		{
			
			pojazd.pozycjax = 0;
			pojazd.pozycjay = 0;
			pojazd.kat = 0;
			it = przeszkody.erase(it);
			break;
		}
		
	}

	if (glutGet(GLUT_ELAPSED_TIME) > czasprzeszkody + 4000)		//przeszkody pojawiaja sie co 4 sekundy i w losowych miejscach
	{
		przeszkody.push_back(cPrzeszkoda(float(rand()) / RAND_MAX * 4 - 2.25, float(rand()) / RAND_MAX * 4 - 2.25, 0.15, 0.15));
		czasprzeszkody = glutGet(GLUT_ELAPSED_TIME);  //przechowanie czasu w ktorym zostala dodana przeszkoda 
	}

	/////////////////////////////////////////bounus kolor
	for (list<cPrzeszkoda>::iterator it = bonuskolor.begin(); it != bonuskolor.end(); it++)	//iterowanie po liscie bonusu koloru
	{
		it->drawbonuszolty();		//rysowanie bonusu
		if (pojazd.kolizja(*it))	//jak zajdzie kolizja to zmiana koloru a bonus usuwa sie 
		{

			if (pojazd.kolorG > 1.0 || pojazd.kolorB > 0.9)	//ograniczenie zeby auto nie bylo biale i zeby dzialalo bo kolory maja maksymalna warotsc 1.0. oraniczenie zeby nie przekroczyc wartosci 1.0
			{
				pojazd.kolorR = 0.1;
				pojazd.kolorG = 0.0;
				pojazd.kolorB = 0.0;
			}
			pojazd.kolorR = 0.1;
			pojazd.kolorR += 0.1;
			pojazd.kolorG += 0.1;
			pojazd.kolorB += 0.1;
			it = bonuskolor.erase(it);
			break;
		}

	}

	if (glutGet(GLUT_ELAPSED_TIME) > czaskolorbonus + 5000)		//bonus pojawia sie co 5 sekund w losowym miejscu
	{
		bonuskolor.push_back(cPrzeszkoda(float(rand()) / RAND_MAX * 4.5 - 2.25, float(rand()) / RAND_MAX * 4.5 - 2.25, 0.3, 0.3));
		czaskolorbonus = glutGet(GLUT_ELAPSED_TIME);		//przechowanie czasu w ktorym zostal dodany bonus koloru
	}

	/////////////////////////////////////////////////////bonus wielkosc

	for (list<cPrzeszkoda>::iterator it = bonuswielkosc.begin(); it != bonuswielkosc.end(); it++)	//iterowanie po liscie bonusu wielkosci
	{
		it->drawbonusziolony();		//rysowanie bonusu
		if (pojazd.kolizja(*it))		//jak zajdzie kolizja bo auto sie powieksza a bonus sie usuwa
		{
			if (pojazd.dlugosc > 3.0 || pojazd.szerokosc > 2.0)		//ograniczenia zeby auto nie roslo w nieskonczonosc. jak osiagnie rozmiary w warunku to wraca do rozmiarow poczatkowych
			{
				pojazd.dlugosc = 0.5;
				pojazd.szerokosc = 1.0;
			}
			
			pojazd.dlugosc += 0.1;
			pojazd.szerokosc += 0.1;
			it = bonuswielkosc.erase(it);
			break;
		}

	}

	if (glutGet(GLUT_ELAPSED_TIME) > czaswielkoscbonus + 6000)		//bonus zwiekszajacy wielkosc auta. bonusy pojawiaja sie co 6 sekund
	{
		bonuswielkosc.push_back(cPrzeszkoda(float(rand()) / RAND_MAX * 4 - 2.25, float(rand()) / RAND_MAX * 4 - 2.25, 0.3, 0.3));
		czaswielkoscbonus = glutGet(GLUT_ELAPSED_TIME);		//przechowanie czasu w ktorym dodano bonus
	}
	///////////////////////////////////bonus predkosc
	for (list<cPrzeszkoda>::iterator it = bonuspredkosc.begin(); it != bonuspredkosc.end(); it++)	//petla iterujaca po liscie bonusu predkosci
	{
		it->drawbonusczerwony();		//rysowanie bonusu
		if (pojazd.kolizja(*it))		//sprawdzenie kolizji. jak jest kolizja to predkosc wzrasta a bonus sie usuwa
		{
			V += 0.051;
			it = bonuspredkosc.erase(it);
			break;
		}

	}

	if (glutGet(GLUT_ELAPSED_TIME) > czaspredkoscbonus + 10000)		//bonus pojawia sie co 10 sekund i w losowych miejscach
	{
		bonuspredkosc.push_back(cPrzeszkoda(float(rand()) / RAND_MAX * 4 - 2.25, float(rand()) / RAND_MAX * 4 - 2.25, 0.3, 0.3));
		czaspredkoscbonus = glutGet(GLUT_ELAPSED_TIME);		//przecowanie czasu w ktorym nastapilo dodanie bonusu
	}

	///////////////////////////////////////////sciany
	for (list<cPrzeszkoda>::iterator it = sciany.begin(); it != sciany.end(); it++)		//petla iterujaca po liscie scian
	{
		it->draw();		//rysowanie sciany
		if (pojazd.kolizja(*it))	//sprawdzenie kolizji. jak kolizja to auto przemieszczane jest do poczatku ukladu wspolrzednych
		{

			pojazd.pozycjax = 0;
			pojazd.pozycjay = 0;
			pojazd.kat = 0;
		}

	}

	glPopMatrix();


	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)		//poruszanie sie auta
{
	if (key == 'w')
	{
		if (V < 1)		//przyspieszanie ale jest narzucona predkosc maksymalna
		{
			V += 0.005;
		}
		pojazd.pozycjay += (sin(pojazd.kat*3.14 / 180.0))*V;
		pojazd.pozycjax += (cos(pojazd.kat*3.14 / 180.0))*V;

	}
	else if (key == 's')
	{
		V = 0.02;
		pojazd.pozycjay -= V*sin(pojazd.kat*3.14 / 180.0);
		pojazd.pozycjax -= V*cos(pojazd.kat*3.14 / 180.0);

	}
	else if (key == 'a')
	{
		V = 0.001;			//zmiana predkosci przy skrecie bo skreca w miejscu i potem zaczyna jechac. Po to jest to zeby zaczynal jechac od malej predkosci a nie od razu od szybszej
		pojazd.kat += 5;
	}
	else if (key == 'd')
	{
		V = 0.001;			//zmiana predkosci przy skrecie bo skreca w miejscu i potem zaczyna jechac. Po to jest to zeby zaczynal jechac od malej predkosci a nie od razu od szybszej
		pojazd.kat -= 5;
	}

}

void mouse(int button, int button_state, int x, int y)		//obsluga myszki
{
	float szerokosc, wysokosc;
	szerokosc = float(x) / widthh * 7 - 3.5;		//zamiana wspolrzednych z pikseli na swiat open GL
	wysokosc = -(float(y) / heightt * 5 - 2.5);
	//cout << szerokosc << "," << wysokosc << endl;

	for (list<cPrzeszkoda>::iterator it = przeszkody.begin(); it != przeszkody.end(); it++)	//usuwanie przeszkod za pomoca klikniecia
	{
		if (szerokosc > it->pozycjax - 0.075&&szerokosc<it->pozycjax + 0.075&& wysokosc>it->pozycjay - 0.075&&wysokosc < it->pozycjay + 0.075)	//usuwanie jesli wspolrzedne kliknieia mieszcze sie w przeszkodzie
		{
			it = przeszkody.erase(it);
			break;
		}
	}
}

int main(int argc, char *argv[])
{

	srand(time(NULL));
	// it's still possible to use console to print messages
	printf("Hello openGL world!");
	// the same can be done with cout / cin
	sciany.push_back(cPrzeszkoda(0, 2.46, 7, 0.1));		//stworzenie scian. Sa one w innej liscie jako przeszkody dlatego ze lista przeszkod jest tylko brana pod uwage do usuniecia a scian nie 
	sciany.push_back(cPrzeszkoda(0, -2.53, 7, 0.1));
	sciany.push_back(cPrzeszkoda(3.31, 0, 0.1, 7));
	sciany.push_back(cPrzeszkoda(-3.37, 0, 0.1, 7));



	glutInitWindowSize(800, 600);
	glutInitWindowPosition(40, 40);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("OpenGLUT Shapes");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	// set white as the clear colour
	glClearColor(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glutMainLoop();

	return 0;
}