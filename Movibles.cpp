#include "Movibles.h"

void Movibles::choqueBloque() {
    _sprite.move(-_velocidad);
}
void Movibles::choqueBloque(BloqueDestruibles* bd)
{
    if (bd != nullptr) {
        if (!reacomodo(bd)) {
            _sprite.move(-_velocidad);
        }
    }

}
void Movibles::choqueBloque(BloqueFijo* bd)
{
    if (bd != nullptr) {
        if (!reacomodo(bd)) {
            _sprite.move(-_velocidad);
        }
    }
}
bool Movibles::reacomodo(BloqueDestruibles* bd)
{
    int margen = 35;
    float posPJx = _sprite.getPosition().x;
    float posPJy = _sprite.getPosition().y;
    float posBDx = bd->getSprite().getPosition().x;
    float posBDy = bd->getSprite().getPosition().y;
    float anchoPJ = _sprite.getGlobalBounds().width;
    float altoPJ = _sprite.getGlobalBounds().height;
    float anchoBD = bd->getBounds().width;
    float altoBD = bd->getBounds().height;
    float difAlto = bd->getBounds().height - _sprite.getGlobalBounds().height;

    if (_velocidad.y != 0) {
        if ((posPJx - posBDx) >= (anchoBD - margen)) {
            //pj arriba o abajo, correccion al costado derecho
            _sprite.setPosition(posBDx + anchoBD, posPJy);
            return true;
        }
        else if ((posBDx - posPJx) >= (anchoBD - margen)) {
            _sprite.setPosition(posBDx - anchoBD, posPJy);
            return true;
        }
    }
    if (_velocidad.x != 0) {
        if ((posPJy - posBDy) >= (altoBD - margen)) {

            _sprite.setPosition(posPJx, posBDy + altoBD);
            return true;
        }
        else if ((posBDy - posPJy) >= (altoBD - margen)) {
            _sprite.setPosition(posPJx, posBDy - altoBD);
            return true;
        }
    }
    return false;
}
bool Movibles::reacomodo(BloqueFijo* bd) {
    int margen = 32;
    float posPJx = _sprite.getPosition().x;
    float posPJy = _sprite.getPosition().y;
    float posBDx = bd->getSprite().getPosition().x;
    float posBDy = bd->getSprite().getPosition().y;
    float anchoPJ = _sprite.getGlobalBounds().width;
    float altoPJ = _sprite.getGlobalBounds().height;
    float anchoBD = bd->getBounds().width;
    float altoBD = bd->getBounds().height;
    float difAlto = bd->getBounds().height - _sprite.getGlobalBounds().height;

    if (_velocidad.y != 0) {
        if ((posPJx - posBDx) >= (anchoBD - margen)) {
            //pj arriba o abajo, correccion al costado derecho
            _sprite.setPosition(posBDx + anchoBD, posPJy);
            return true;
        }
        else if ((posBDx - posPJx) >= (anchoBD - margen)) {
            _sprite.setPosition(posBDx - anchoBD, posPJy);
            return true;
        }
    }
    if (_velocidad.x != 0) {
        if ((posPJy - posBDy) >= (altoBD - margen)) {

            _sprite.setPosition(posPJx, posBDy + altoBD);
            return true;
        }
        else if ((posBDy - posPJy) >= (altoBD - margen)) {
            _sprite.setPosition(posPJx, posBDy - altoBD);
            return true;
        }
    }
    return false;
}
void Movibles::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

FloatRect Movibles::getBounds() const
{

	return _sprite.getGlobalBounds();
}

Sprite Movibles::getSprite()
{
	return _sprite;
}
