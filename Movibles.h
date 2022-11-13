#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Colisionable.h"
#include "BloqueFijo.h"
#include "BloquesDestruibles.h"
#include <string.h>
#include <random>
#include <iostream>
using namespace sf;
using namespace std;
class Movibles : public Colisionable, public Drawable
{
public:
	void choqueBloque();
	void choqueBloque(BloqueFijo* bd);
	void choqueBloque(BloqueDestruibles* bd);
	bool reacomodo(BloqueDestruibles* bd);
	bool reacomodo(BloqueFijo* bd);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual FloatRect getBounds() const;
	Sprite getSprite();

	bool getMuriendo() { return _muriendo; }
	bool getEstado() { return _estado; }
	void setMuriendo(bool muere) { _muriendo = muere; }
	void setEstado(bool a) { _estado = a; }

	
protected:
	Vector2f _velocidad;
	Texture _txt;
	Sprite _sprite;

	SoundBuffer* _bufCamina;
	Sound* _caminar;
	SoundBuffer* _bufPer;
	Sound* _sonPerderVida;
	int __timerCamina;
	int _path = 1;
	int __timerMuerte = 60 * 2;
	bool _muriendo;
	bool _estado;
};

