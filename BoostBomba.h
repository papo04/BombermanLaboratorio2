#pragma once
#include <SFML/Graphics.hpp>
#include "colisionable.h"

using namespace sf;
class BoostBomba : public Drawable, public Colisionable
{
public:
	BoostBomba();
	FloatRect getBounds() const override;
	void draw(RenderTarget& target, RenderStates states) const override;

	Sprite getSprite() { return _sprite; }
	bool getEstado() { return _estado; }
	void setEstado(bool estado) { _estado = estado; }
	void setPosicionSprite(Vector2f v) { _sprite.setPosition(v); }

private:
	Texture _txt;
	Sprite _sprite;
	bool _estado;
};
