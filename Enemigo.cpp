#include "Enemigo.h"

Enemigo::Enemigo(Tipo tipo) {

	_velocidad = { 0,0 };

	_txt.loadFromFile("globo1.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin((_sprite.getGlobalBounds().width) / 2, (_sprite.getGlobalBounds().height) / 2);
	_sprite.setPosition(517.5, 517.5);
	random = 0;
	_estado = true;
	_muriendo = false;
	_tipo = tipo;
	_buf = new SoundBuffer;
	_sonido = new Sound;
}

void Enemigo::cmd()
{
	float mov = 2;
	if (_tipo == brian) {
		mov = 6;
	}
	_velocidad = {};
	random_device rd;
	if (_tiempoMov == 0) {
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, 4);
		random = dis(gen);
		_tiempoMov = 60;
	}
	_tiempoMov--;

	switch (random)
	{
	case 1:

		_velocidad.y = -1 * mov;
		animacionCaminar(1);
		break;
	case 2:

		_velocidad.y = mov;
		animacionCaminar(2);
		break;

	case 3:

		_velocidad.x = -1 * mov;
		animacionCaminar(4);
		break;
	case 0:

		_velocidad.x = mov;
		animacionCaminar(3);
		break;
	}
	_sprite.move(_velocidad);

	//BORDES
	//float margenAncho = 47 + _sprite.getGlobalBounds().width / 2, margenAlto = 47 + _sprite.getGlobalBounds().height / 2;
	//if (_sprite.getPosition().x < margenAncho) {
	//	_sprite.setPosition(margenAncho, _sprite.getPosition().y);
	//}
	//if (_sprite.getPosition().x > 800 - margenAncho) {
	//	_sprite.setPosition(800 - margenAncho, _sprite.getPosition().y);
	//}
	//if (_sprite.getPosition().y < margenAlto) {
	//	_sprite.setPosition(_sprite.getPosition().x, margenAlto);
	//}
	//if (_sprite.getPosition().y > 600 - margenAlto - 10) {
	//	_sprite.setPosition(_sprite.getPosition().x, 600 - margenAlto - 10);
	//}
}
void Enemigo::morir() {


	switch (_tipo)
	{
	case maxi:
		if (__timerMuerte == 119) {
			_buf->loadFromFile("maxi.wav");
			_sonido->setBuffer(*_buf);
			_sonido->play();
		}
		if (!_estado) {
			if (__timerMuerte > 100) {
				_txt.loadFromFile("maxiMuerte1.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 70) {
				_txt.loadFromFile("maxiMuerte2.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 50) {

				_txt.loadFromFile("maxiMuerte3.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 30) {
				_sprite.move(-_velocidad);
				_txt.loadFromFile("maxiMuerte4.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 10) {
				_txt.loadFromFile("maxiMuerte5.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 0) {

				_txt.loadFromFile("maxiMuerte6.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else {
				_txt.loadFromFile("vacio.png");
				_sprite.setTexture(_txt);
				_muriendo = true;
			}

		}
		break;
	case brian:
		if (__timerMuerte == 119) {
			_buf->loadFromFile("brian.wav");
			_sonido->setBuffer(*_buf);
			_sonido->play();
		}
		if (!_estado) {
			if (__timerMuerte > 100) {
				_txt.loadFromFile("brianMuerte1.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 70) {
				_txt.loadFromFile("brianMuerte2.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 50) {

				_txt.loadFromFile("brianMuerte3.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 30) {
				_sprite.move(-_velocidad);
				_txt.loadFromFile("brianMuerte4.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 10) {
				_txt.loadFromFile("brianMuerte5.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 0) {

				_txt.loadFromFile("brianMuerte6.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else {
				_txt.loadFromFile("vacio.png");
				_sprite.setTexture(_txt);
				_muriendo = true;
			}

		}
		break;
	case kloster:
		if (__timerMuerte == 119) {
			_buf->loadFromFile("kloster.wav");
			_sonido->setBuffer(*_buf);
			_sonido->play();
		}
		if (!_estado) {
			if (__timerMuerte > 100) {
				_txt.loadFromFile("KlosterMuerte1.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 70) {
				_txt.loadFromFile("KlosterMuerte2.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 50) {

				_txt.loadFromFile("KlosterMuerte3.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 30) {
				_sprite.move(-_velocidad);
				_txt.loadFromFile("KlosterMuerte4.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 10) {
				_txt.loadFromFile("KlosterMuerte5.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else if (__timerMuerte > 0) {

				_txt.loadFromFile("KlosterMuerte6.png");
				_sprite.setTexture(_txt);

				__timerMuerte--;
			}
			else {
				_txt.loadFromFile("vacio.png");
				_sprite.setTexture(_txt);
				_muriendo = true;
			}

		}
		break;
	default:
		break;
	}
	
}

void Enemigo::animacionCaminar(int direccion)
{
	string cadena;
	switch (_tipo)
	{
	case maxi:
		cadena = "maxi";
		break;
	case brian:
		cadena = "brian";
		break;
	case kloster:
		cadena = "kloster";
		break;
	default:
		break;
	}

	if (__timerCamina > 0) {
		switch (direccion)
		{
		case 1:
			cadena += to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		case 2:
			cadena += to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		case 3:
			cadena += to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		}
	}
	else {
		__timerCamina = 30;
		if (_path < 3) {
			_path++;
		}
		else {
			_path = 1;
		}
	}
	__timerCamina--;
}
