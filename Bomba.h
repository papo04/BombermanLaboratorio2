#pragma once
#include "Inamovibles.h"
using namespace sf;
class Bomba : public Inamovibles
{
public:
	Bomba();
	void crearExplotar(bool &actLLama);
	void crearBomba(Vector2f posicion);
	void setSpritePosition(Vector2f posicion);

private:
	int _timer;
};

