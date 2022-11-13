#include "Fuego.h"

Fuego::Fuego()
{
	_txt.loadFromFile("codigo1.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_estado = false;
	
	_bufSonido = new SoundBuffer;
	_bufSonido->loadFromFile("fuego.wav");
	_sonido = new Sound;
	_sonido->setBuffer(*_bufSonido);
	_sonido->setVolume(30);
	_timer = 2 * 60;
}

void Fuego::setSpritePosition(Vector2f posicion)
{
	_sprite.setPosition(posicion);
}

void Fuego::crearLlama()
{
	if (_timer == 119) {
		if (!_bufSonido->loadFromFile("fuego.wav")) {}
		_sonido->play();
	}
	if (_timer > 90) {
		_txt.loadFromFile("codigo1.png");
		_sprite.setTexture(_txt);
		_timer--;
	}
	else if (_timer > 60) {
		_txt.loadFromFile("codigo2.png");
		_sprite.setTexture(_txt);
		_timer--;
	}
	else if (_timer > 30) {
		_txt.loadFromFile("codigo3.png");
		_sprite.setTexture(_txt);
		_timer--;
	}
	else if (_timer > 0) {
		_txt.loadFromFile("codigo4.png");
		_sprite.setTexture(_txt);
		_timer--;
	}
	else if (_timer == 0) {
		_estado = false;
		_txt.loadFromFile("vacio.png");
		_sprite.setTexture(_txt);
		_timer = 60 * 2;
	}
}

void Fuego::rotarVertical()
{
	_sprite.setRotation(270);
}
