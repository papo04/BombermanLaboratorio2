#pragma once
#include <SFML/Graphics.hpp>
#include "BloqueFijo.h"
#include "BloquesDestruibles.h"
#include "BoostVelocidad.h"
#include <random>
#include <iostream>
#include "BoostBomba.h"
#include "PuertaVictoria.h"
using namespace std;
using namespace sf;
class Mapa 
{
public:
	Mapa();
	void generarMapa();
	void setEstadoPV(bool estado) { _puertaVictoria.setEstado(estado); }
	bool getEstadoPV() { return _puertaVictoria.getEstado(); }
	void abrirPuerta() { _puertaVictoria.abrirPuerta(); };
	Vector2f getPositionPuerta() { return _puertaVictoria.getSprite().getPosition(); }
	int getNumeroDestruibles();

	void dibujarFijos(RenderWindow *v);
	void dibujarDestruibles(RenderWindow* v);
	void dibujarVelocidad(RenderWindow* v);
	void dibujarBoostBomba(RenderWindow* v);
	void dibujarPuertaVictoria(RenderWindow* v);


	BloqueDestruibles* comprobarChoqueDestruible(Colisionable& c);
	

	BloqueFijo* comprobarChoqueFijo(Colisionable& c);

	bool comprobarColisionAmbos(Colisionable& c);
	void comprobarColisionDestruir(Colisionable& c);
	bool comprobarColisionVelocidad(Colisionable& c);
	bool comprobarColisionBoostBomba(Colisionable& c);
	bool comprobarColisionPuerta(Colisionable& c);
	
	
private:
	int ** _mat;
	BloqueFijo * _bf;
	BloqueDestruibles * _bd;
	BoostVelocidad _bv1, _bv2;
	BoostBomba _bb1, _bb2;
	PuertaVictoria _puertaVictoria;
	int _contRandom;
};

