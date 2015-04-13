#ifndef AUTO
#define AUTO
#include"cPrzeszkoda.h"
class cAuto
{
public:
	float pozycjax, pozycjay;
	float szerokosc, dlugosc;
	float kat;
	float kolorR, kolorG, kolorB;
	cAuto();
	void draw();
	bool kolizjapunktu(float punktx,float punkty);
	bool kolizja(cPrzeszkoda element);

};
#endif