#include "Inamovibles.h"

FloatRect Inamovibles::getBounds() const
{

	return _sprite.getGlobalBounds();
}

void Inamovibles::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(_sprite, states);
}
