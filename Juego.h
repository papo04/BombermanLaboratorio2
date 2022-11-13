#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "BloquesDestruibles.h"
#include"Bomba.h"
#include "Fuego.h"
#include "Mapa.h"
#include "Enemigo.h"
#include "Estadistica.h"
#include <list>
#include <algorithm>
#include <stdio.h>
#include <iostream>



using namespace std;
using namespace sf;

class Juego
{
public:
	Juego() { _acelerar = false; _contadorCrear = 0; _contadorEnemigosEliminados = 0; _dosBombas = false; }
	Juego(RenderWindow* _ventana1);
	void gamePlay(RenderWindow* _ventana1);
	void dibujar(RenderWindow* _ventana1);
	
	bool getVictoria() { return _victoria; }
	int getVidas() { return _vidas; }
	void setVidas(int vidas) { _vidas = vidas; }
	int getPuntaje() { return _puntaje; }
	void setPuntaje(int puntaje) { _puntaje = puntaje; }
	int getEnemigosVivos();

	void pantallaGameOver(RenderWindow *);
	void mostarStage(RenderWindow* _ventana1, int numeroStage);
protected:

	Texture _txStage;
	Sprite _stage;

	Sprite _fondo;
	Texture _txtFondo;
	Sprite _fondoGameOver;
	Texture _txtFondoGameOver;

	Text textoPuntaje;
	Font fuenteTextoPuntaje;

	//Player  _player1;
	list <Player> _players;
	list <Enemigo> _enemigos;
	BloqueDestruibles* _bloquesito = new BloqueDestruibles(13, 11);
	int _vidas = 3;
	//Bomba* _bomba;
	Bomba* _bombas = new Bomba[2];
	bool _dosBombas;
	int _timer;
	Fuego* _fuegos = new Fuego[2];
	Fuego* _fuegosV = new Fuego[2];
	int _timer2;
	Mapa* _mapa1;
	int _randomNumero = 4;
	int _contadorCrear;
	int _tiempoBombas;
	bool _acelerar;
	int _timerVelocidad;
	int _timerBoostBomba;
	int _contadorEnemigosEliminados;
	int _puntaje;
	int _tiempoLimite;
	bool _victoria = false;

	bool _gameOver = false;
	SoundBuffer *_bufBomba;
	Sound *_sonBomba;

	SoundBuffer *_bufItem;
	Sound* _sonItem;

	SoundBuffer* _bufGameOver;
	Sound* _sonidoGameOver;

	Text _textoPuntaje;
	Font _fuente;
	Text _textoVidas;

	int _totalDestruibles;
	int _enemigosAMatar = 3;

	int timerGameOver = 60 * 4;
	int _timerStage = 60 * 4;

	SoundBuffer* _bufStage;
	Sound *_sonidoStage;

	Music _musica;
};

