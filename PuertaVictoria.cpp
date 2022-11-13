#include "PuertaVictoria.h"

PuertaVictoria::PuertaVictoria() {
	_txt.loadFromFile("PuertaVictoria1.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_estado = false;
}
void PuertaVictoria::abrirPuerta() {
	_txt.loadFromFile("PuertaVictoria2.png");
	_sprite.setTexture(_txt);
}
