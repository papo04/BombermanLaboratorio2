#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{
	__timerCamina = 20;
	_velocidad = { 0,0 };
	_bufCamina = new SoundBuffer();
	_bufCamina->loadFromFile("caminar.wav");
	_caminar = new Sound();
	_caminar->setBuffer(*_bufCamina);
	_caminar->setVolume(35);
	_bufPer = new SoundBuffer();
	_bufPer->loadFromFile("perderVida.wav");
	_sonPerderVida = new Sound();
	_sonPerderVida->setBuffer(*_bufPer);
	_sonPerderVida->setVolume(70);
	_txt.loadFromFile("down1.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin((_sprite.getGlobalBounds().width ) / 2, (_sprite.getGlobalBounds().height) / 2);
	_muriendo = false;
	_estado = true;
}

void Player::cmd(Event evento, bool acelerar)
{
	float mov = 2;
	_velocidad = {};
	if (acelerar==true) {
		mov = 5;
	}

	switch (evento.type)
	{
	case Event::KeyPressed:
		
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			//_sprite.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - mov);
			_velocidad.y = -1 * mov;
			animacionCaminar(1);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			//_sprite.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + mov);
			_velocidad.y = mov;
			animacionCaminar(2);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {
			//_sprite.setPosition(_sprite.getPosition().x-mov, _sprite.getPosition().y);
			_velocidad.x = -1 * mov;
			animacionCaminar(4);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			//_sprite.setPosition(_sprite.getPosition().x+mov, _sprite.getPosition().y);
			_velocidad.x = mov;
			animacionCaminar(3);

		}
		break;
	case Event::KeyReleased:
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			//_velocidad.y = -1 * mov;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			//_sprite.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + mov);
			//_velocidad.y = mov;

		}
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {

			//_velocidad.x = -1 * mov;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {

			//_velocidad.x = mov;

		}
		break;
	}
	_sprite.move(_velocidad);

	if (evento.KeyReleased) {
		_sprite.setPosition(_sprite.getPosition());
	}
	//BORDES
	float margenAncho = 47 + _sprite.getGlobalBounds().width / 2, margenAlto = 47 + _sprite.getGlobalBounds().height / 2;
	if (_sprite.getPosition().x < margenAncho) {
		_sprite.setPosition(margenAncho, _sprite.getPosition().y);
	}
	if (_sprite.getPosition().x > 800 - margenAncho) {
		_sprite.setPosition(800 - margenAncho, _sprite.getPosition().y);
	}
	if (_sprite.getPosition().y < margenAlto) {
		_sprite.setPosition(_sprite.getPosition().x, margenAlto);
	}
	if (_sprite.getPosition().y > 600 - margenAlto-10) {
		_sprite.setPosition(_sprite.getPosition().x, 600 - margenAlto-10);
	}
}
void Player::animacionCaminar(int direccion) {

	string cadena;
	if (__timerCamina == 19) {
		if(!_bufCamina->loadFromFile("caminar.wav")){}
		_caminar->play();
	}
	
	if (__timerCamina > 0) {
		switch (direccion)
		{
		case 1:
			cadena = "up" + to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		case 2:
			cadena = "down" + to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		case 3:
			cadena = "right" + to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		case 4:
			cadena = "left" + to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
		}
	}
	else {
		__timerCamina = 20;
		if (_path < 3) {
			_path++;
		}
		else {
			_path = 1;
		}
	}
	__timerCamina--;
}


void Player::morir(int &contadorMuerto) {
	if (__timerMuerte == 119) {
		if (!_bufPer->loadFromFile("perderVida.wav")) {}
		_sonPerderVida->play();
	}
	if (__timerMuerte > 100) {
		//_sprite.move(-_velocidad);
		_txt.loadFromFile("death1.png");
		_sprite.setTexture(_txt);

		__timerMuerte--;
	}
	else if (__timerMuerte > 80) {
		//_sprite.move(-_velocidad);
		_txt.loadFromFile("death2.png");
		_sprite.setTexture(_txt);

		__timerMuerte--;
	}
	else if (__timerMuerte > 60) {
		//_sprite.move(-_velocidad);
		_txt.loadFromFile("death3.png");
		_sprite.setTexture(_txt);

		__timerMuerte--;
	}
	else if (__timerMuerte > 40) {
		//_sprite.move(-_velocidad);
		_txt.loadFromFile("death4.png");
		_sprite.setTexture(_txt);

		__timerMuerte--;
	}
	else if (__timerMuerte > 20) {
		//_sprite.move(-_velocidad);
		_txt.loadFromFile("death5.png");
		_sprite.setTexture(_txt);

		__timerMuerte--;
	}
	else if (__timerMuerte > 0) {
		//_sprite.move(-_velocidad);
		_txt.loadFromFile("death6.png");
		_sprite.setTexture(_txt);

		__timerMuerte--;
	}
	else {
		_txt.loadFromFile("vacio.png");
		_sprite.setTexture(_txt);
		_estado = false;
		contadorMuerto++;
	}
}