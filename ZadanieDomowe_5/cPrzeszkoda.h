#ifndef PRZESZKODA
#define PRZESZKODA

class cPrzeszkoda
{
public:
	float pozycjax, pozycjay;
	float szerokosc, dlugosc;

	cPrzeszkoda();
	cPrzeszkoda(float _pozycjax, float _pozycjay,float _szerokosc,float _dlugosc);
	void draw();
	void drawbonuszolty();
	void drawbonusczerwony();
	void drawbonusziolony();


};

#endif
