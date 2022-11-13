#pragma once
#include "Inamovibles.h"

using namespace sf;
class PuertaVictoria : public Inamovibles
{
public:
	PuertaVictoria();

	void setPosicionSprite(Vector2f v) { _sprite.setPosition(v); }
	void abrirPuerta();
};

