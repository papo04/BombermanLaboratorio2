#pragma once
#include "Inamovibles.h"
using namespace sf;
class Fuego : public Inamovibles
{
private:
	int _timer;
public:
	Fuego();
	void setSpritePosition(Vector2f posicion);
	void crearLlama();
	void rotarVertical();
};

