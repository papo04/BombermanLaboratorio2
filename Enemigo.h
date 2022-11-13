#pragma once
#include "Movibles.h"
enum Tipo{maxi=0,brian,kloster};
class Enemigo :public Movibles
{
public:
	Enemigo(){}
	Enemigo(Tipo);
	void cmd();
	void morir();
	Tipo getTipo() { return _tipo; }
	void animacionCaminar(int direccion);

private:
	int random =0;
	int _tiempoMov = 60;
	Tipo _tipo = maxi;

	SoundBuffer * _buf;
	Sound * _sonido;
};

