#pragma once
#include "Colisionable.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Inamovibles : public Drawable, public Colisionable
{
public:
	bool getEstado() { return _estado; }
	void setEstado(bool estado) { _estado = estado; };
	void setPosicionBloque(int x, int y) { _sprite.setPosition(x*45 + 22.5,y * 45 + 22.5); }
	Sprite getSprite() { return _sprite; }
	FloatRect getBounds() const override;
	void draw(RenderTarget& target, RenderStates states) const override;

protected:
	Texture _txt;
	Sprite _sprite;
	bool _estado;
	SoundBuffer *_bufSonido;
	Sound *_sonido;
};