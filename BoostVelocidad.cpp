#include "BoostVelocidad.h"

BoostVelocidad::BoostVelocidad() {
	_txt.loadFromFile("velocidad.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_estado = true;
}


FloatRect BoostVelocidad::getBounds() const
{
	return _sprite.getGlobalBounds();
}

void BoostVelocidad::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(_sprite, states);
}
