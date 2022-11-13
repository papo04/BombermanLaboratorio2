#include "BoostBomba.h"

BoostBomba::BoostBomba() {
	_txt.loadFromFile("boostBomba.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_estado = true;
}
FloatRect BoostBomba::getBounds() const
{
	return _sprite.getGlobalBounds();
}

void BoostBomba::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(_sprite, states);
}