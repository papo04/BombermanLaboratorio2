#include "Mapa.h"
#include <time.h>
#include <stdlib.h>

Mapa::Mapa()
{
	generarMapa();
}
void Mapa::generarMapa() {

	random_device rd;
	int cont = 0;
	int random = 1;
	_contRandom = 0;
	for (int i = 0; i < 13; i++) { // 2 ES BLOQUE FIJO, 0 ES LIBRE Y 1 ROMPIBLE
		for (int j = 0; j < 13; j++) {
			if (i == 0 || j == 0 || i == 12 || j == 12) {
				_mat[i][j] = 2;
			}
			else if (i % 2 == 0 && j % 2 == 0) {
				_mat[i][j] = 2;
			}
			else if (i == 1 && j == 1 || i == 1 && j == 2 || i == 2 && j == 1) {
				_mat[i][j] = 0;
			}
			else if ((i==11 && (j==11 || j==10)) || (j==11 && (i==11 || i==10))) {
				_mat[i][j] = 0;
			}
			else if (cont < 100) {
				mt19937 gen(rd());
				uniform_int_distribution<> dis(0, 1);
				random = dis(gen);
				_mat[i][j] =random;
				cont++;
				if ( random == 1) {
					_contRandom++;
				}
			}
		}
	}
	int posD = 0, posF = 0;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			if (_mat[i][j] == 1) {
				_bd[posD] = new BloqueDestruibles(i, j);
				posD++;
			}
			else if (_mat[i][j] == 2) {
				_bf[posF] = new BloqueFijo(i,j);
				posF++;
			}
		}
	}
	
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, posD-1);
	int inspeccion = dis(gen);
	_bv1.setPosicionSprite(_bd[inspeccion]->getSprite().getPosition());
	_bv1.getSprite().move(2.5, 2.5);//centra el boost
	mt19937 gen2(rd());
	uniform_int_distribution<> dis2(0, posD-1);
	inspeccion = dis2(gen2);
	_bv2.setPosicionSprite(_bd[inspeccion]->getSprite().getPosition());
	_bv2.getSprite().move(2.5, 2.5);//centra el boost
	mt19937 gen3(rd());
	uniform_int_distribution<> dis3(0, posD-1);
	inspeccion = dis3(gen3);
	_bb1.setPosicionSprite(_bd[inspeccion]->getSprite().getPosition());
	_bb1.getSprite().move(2.5, 2.5);//centra el boost
	mt19937 gen4(rd());
	uniform_int_distribution<> dis4(0, posD-1);
	inspeccion = dis4(gen4);
	_bb2.setPosicionSprite(_bd[inspeccion]->getSprite().getPosition());
	_bb2.getSprite().move(2.5, 2.5);//centra el boost
	mt19937 gen5(rd());
	uniform_int_distribution<> dis5(0, posD-1);
	inspeccion = dis5(gen5);
	_puertaVictoria.setPosicionSprite(_bd[inspeccion]->getSprite().getPosition());
	_puertaVictoria.getSprite().move(2.5, 2.5);//centra el boost
}
void Mapa::dibujarVelocidad(RenderWindow* v) {
		if (_bv1.getEstado())
			v->draw(_bv1);
		if (_bv2.getEstado())
			v->draw(_bv2);
}
void Mapa::dibujarBoostBomba(RenderWindow* v) {
	if (_bb1.getEstado())
		v->draw(_bb1);
	if (_bb2.getEstado())
		v->draw(_bb2);
}

int Mapa::getNumeroDestruibles()
{
	int cont = 0;
	for (int i = 0; i < _contRandom; i++) {
		if (_bd[i]->getEstado())
			cont++;
	}
	return cont;
}

void Mapa::dibujarFijos(RenderWindow* v)
{
	for (int i = 0; i < 73; i++) {
		v->draw(*_bf[i]);
	}
}
void Mapa::dibujarDestruibles(RenderWindow* v) {
	for (int i = 0; i < _contRandom; i++) {
		if (_bd[i]->getEstado())
			v->draw(*_bd[i]);
	}
}

bool Mapa::comprobarColisionAmbos(Colisionable& c) {
	for (int i = 0; i < 73; i++) {
		if (c.isColision(*_bf[i])) {
			return true;
		}
	}
	for (int i = 0; i < _contRandom; i++) {
		if (c.isColision(*_bd[i])) {
			if (_bd[i]->getEstado()) {
				return true;
			}
		}
	}
	return false;
}

void Mapa::comprobarColisionDestruir(Colisionable& c) {
	for (int i = 0; i < _contRandom; i++) {
		if (c.isColision(*_bd[i])) {
			if (_bd[i]->getEstado()) {
				_bd[i]->setEstado(false);
			}
		}
	}
}

bool Mapa::comprobarColisionVelocidad(Colisionable& c) {
	if (c.isColision(_bv1)) {
		if (_bv1.getEstado()) {
			_bv1.setEstado(false);
			return true;
		}
	}
	if (c.isColision(_bv2)) {
		if (_bv2.getEstado()) {
			_bv2.setEstado(false);
			return true;
		}
	}
	return false;
}
bool Mapa::comprobarColisionBoostBomba(Colisionable& c) {
	if (c.isColision(_bb1)) {
		if (_bb1.getEstado()) {
			_bb1.setEstado(false);
			return true;
		}
	}
	if (c.isColision(_bb2)) {
		if (_bb2.getEstado()) {
			_bb2.setEstado(false);
			return true;
		}
	}
}
BloqueDestruibles* Mapa::comprobarChoqueDestruible(Colisionable& c) {
	for (int i = 0; i < _contRandom; i++) {
		if (c.isColision(*_bd[i])) {
			if (_bd[i]->getEstado()) {
				return _bd[i];
			}
		}
	}
	return nullptr;
}

BloqueFijo* Mapa::comprobarChoqueFijo(Colisionable& c)
{
	for (int i = 0; i < 73; i++) {
		if (c.isColision(*_bf[i])) {
			return _bf[i];
		}
	}
	return nullptr;
}
void Mapa::dibujarPuertaVictoria(RenderWindow* v) {
	v->draw(_puertaVictoria);
}
bool Mapa::comprobarColisionPuerta(Colisionable& c) {
	if (_puertaVictoria.getEstado()) {
		if (c.isColision(_puertaVictoria)) {
			return true;
		}
	}
	return false;
}