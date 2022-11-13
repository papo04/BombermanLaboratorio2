#pragma once
#include "Juego.h"
class Nivel3 : public Juego
{
public:
	Nivel3(RenderWindow*,int,int);
	void pantallaVictoria(RenderWindow* _ventana1);
private:
	Sprite _pantallaFinal;
	Texture _txPantalla;
	int _timerVictoria = 60 * 5;

	SoundBuffer* _bufVictoria;
	Sound* _sonidoVictoria;
};

