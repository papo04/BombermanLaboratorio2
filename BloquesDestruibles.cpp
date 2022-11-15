#include "BloquesDestruibles.h"

BloqueDestruibles::BloqueDestruibles() {
	_txt.loadFromFile("bloqueDestruible.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_estado = true;
}

BloqueDestruibles::BloqueDestruibles(int a, int b)
{
	_txt.loadFromFile("bloqueDestruible.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_sprite.setPosition(a*45+22.5, b*45+22.5);
	_estado =true;
}