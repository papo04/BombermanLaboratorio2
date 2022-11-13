#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "colisionable.h"

using namespace sf;
class BoostVelocidad : public Drawable, public Colisionable
{
public:
	BoostVelocidad();
	Sprite getSprite() { return _sprite; }
	FloatRect getBounds() const override;
	void draw(RenderTarget& target, RenderStates states) const override;

	bool getEstado() { return _estado; }
	void setEstado(bool estado) { _estado = estado; }
	void setPosicionSprite(Vector2f v) { _sprite.setPosition(v); }

private:
	Texture _txt;
	Sprite _sprite;
	bool _estado;
};

