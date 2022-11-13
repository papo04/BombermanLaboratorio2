#include "Juego.h"


Juego::Juego(RenderWindow* _ventana1)
{

	_ventana1->setFramerateLimit(60);

	_txtFondo.loadFromFile("fondo.png");
	_fondo.setTexture(_txtFondo);

	_txtFondoGameOver.loadFromFile("gameOver.jpg");
	_fondoGameOver.setTexture(_txtFondoGameOver);


	_fuegosV[0].rotarVertical();
	_fuegosV[1].rotarVertical();

	Enemigo* _enemigo1 = new Enemigo(maxi);
	Enemigo* _enemigo2 = new Enemigo(maxi);
	Enemigo* _enemigo3 = new Enemigo(maxi);

	_enemigos.push_back(*_enemigo1);
	_enemigos.push_back(*_enemigo2);
	_enemigos.push_back(*_enemigo3);


	Player* _player1 = new Player;
	_players.push_back(*_player1);

	_bufBomba = new SoundBuffer;
	_sonBomba = new Sound;
	_bufBomba->loadFromFile("ponerBomba.wav");
	_sonBomba->setBuffer(*_bufBomba);
	_sonBomba->setVolume(50);

	_bufItem = new SoundBuffer;
	_sonItem = new Sound;
	_bufItem->loadFromFile("item.wav");
	_sonItem->setBuffer(*_bufItem);
	_sonItem->setVolume(50);

	_bufStage = new SoundBuffer;
	_sonidoStage = new Sound;

	_bufStage->loadFromFile("stage.wav");
	_sonidoStage->setBuffer(*_bufStage);

	_bufGameOver = new SoundBuffer;
	_sonidoGameOver = new Sound;

	_bufGameOver->loadFromFile("gameOver.wav");
	_sonidoGameOver->setBuffer(*_bufGameOver);

	_musica.openFromFile("juego.wav");
	_musica.setLoop(true);
	_musica.setVolume(20);
	

	_timer = 0;

	_timer2 = 0;
	_mapa1 = new Mapa;
	_randomNumero = 4;
	_contadorCrear = 0;			//contar muerte de pj

	_dosBombas = false;
	_timerBoostBomba = 0;
	_tiempoBombas = 0;

	_fuente.loadFromFile("fuente.ttf");
	_textoVidas.setFont(_fuente);
	_textoVidas.setScale(0.3, 0.3);
	_textoVidas.setPosition(590, 45);
	_textoPuntaje.setFont(_fuente);
	_textoPuntaje.setScale(0.5, 0.5);
	_textoPuntaje.setPosition(590, 90);

	_vidas = 3;
	_puntaje = 0;
	_totalDestruibles = _mapa1->getNumeroDestruibles();
	_enemigosAMatar = 3;


	_acelerar = false;
	_timerVelocidad = 0;

	_contadorEnemigosEliminados = 0;

	_tiempoLimite = 5 * 60 * 60;

}

void Juego::gamePlay(RenderWindow* _ventana1)
{
	_musica.play();
	while (!_gameOver) {
		sf::Event event;
		while (_ventana1->pollEvent(event)) {
			if (event.type == Event::Closed) {
				_ventana1->close();
			}
		}
		/*if (_victoria == true) {
			_ventana1->close();
		}*/
		_tiempoLimite--;
		//CMD

		list<Player>::iterator play;
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (!play->getMuriendo()) {
				play->cmd(event, _acelerar);
			}
			else {
				if (play->getEstado())
					play->morir(_contadorCrear);
			}
		}


		//fin de las 3 vidas y partida, luego cambiar
		if (_vidas == 0) {
			//va pantalla de game over
			_gameOver = true;//regresa al menu, sin puntos ni estadisticas
		}
		//crea nuevo pj, nueva vida en esquina
		//Los numeros pares de _contadorCrear son cuando el pj esta vivo y los impares cuando está muerto
		if (_contadorCrear % 2 != 0) {
			Player* _player = new Player;
			_vidas--;
			_players.push_back(*_player);
			_contadorCrear++;
		}
		//Colision con boosterVelocidad (20 seg)
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (_mapa1->comprobarColisionVelocidad(*play)) {
				_timerVelocidad = 20 * 60;
				_acelerar = true;
				if(_bufItem->loadFromFile("item.wav")){}
				_sonItem->play();
			}
		}
		_timerVelocidad--;
		if (_timerVelocidad <= 0) {
			_acelerar = false;
		}
		//Colision con boosterBOmba (20 seg)
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (_mapa1->comprobarColisionBoostBomba(*play)) {
				_timerBoostBomba = 20 * 60;
				_dosBombas = true;
				if(!_bufItem->loadFromFile("item.wav")){}
				_sonItem->play();
			}
		}
		_timerBoostBomba--;
		if (_timerBoostBomba <= 0) {
			_dosBombas = false;
		}


		//CMD del enemigo, si esta vivo o muriendo.
		list<Enemigo>::iterator it;
		for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
			if (it->getEstado())
				it->cmd();
			else {
				it->morir();
			}
		}
		//Colisiones con bloques de PJ
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (_mapa1->comprobarChoqueDestruible(*play) != nullptr) {
				play->choqueBloque(_mapa1->comprobarChoqueDestruible(*play));
			}
			if (_mapa1->comprobarChoqueFijo(*play) != nullptr) {
				play->choqueBloque(_mapa1->comprobarChoqueFijo(*play));
			}
		}
		//Colsiones con bloques del Enemigo
		for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
			if (_mapa1->comprobarChoqueDestruible(*it) != nullptr && it->getMuriendo() == false && it->getTipo() != kloster) {

				it->choqueBloque(_mapa1->comprobarChoqueDestruible(*it));
			}
			if (_mapa1->comprobarChoqueFijo(*it) != nullptr && it->getMuriendo() == false) {

				it->choqueBloque(_mapa1->comprobarChoqueFijo(*it));
			}
		}
		// Destruccion de bloques flojos
		for (int i = 0; i < 2; i++) {
			if (_fuegos[i].getEstado()) {
				_mapa1->comprobarColisionDestruir(_fuegos[i]);
			}
			if (_fuegosV[i].getEstado()) {
				_mapa1->comprobarColisionDestruir(_fuegosV[i]);
			}
		}


		//poner bomba, solo si no esta muriendo y naturalmente no muerto
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (!_dosBombas) {
				if (Keyboard::isKeyPressed(Keyboard::Space) && _bombas[0].getEstado() == false && play->getMuriendo() == false && _fuegos[0].getEstado() == false && _fuegosV[0].getEstado()==false) {
					if(!_bufBomba->loadFromFile("ponerBomba.wav")){}
					_sonBomba->play();
					bool estado;
					_bombas[0].crearExplotar(estado);
					_bombas[0].setSpritePosition(play->getSprite().getPosition());
					play->setTocandoBomba(true, 0);
				}
			}
			else {
				for (int i = 0; i < 2; i++) {
					if (Keyboard::isKeyPressed(Keyboard::Space) && play->getMuriendo() == false && _fuegos[i].getEstado() == false && _fuegosV[i].getEstado() == false) {
						if (_bombas[i].getEstado() == false && _tiempoBombas < 0) {
							if(!_bufBomba->loadFromFile("ponerBomba.wav")){}
							_sonBomba->play();
							bool estado = false;
							_bombas[i].crearExplotar(estado);
							_bombas[i].setSpritePosition(play->getSprite().getPosition());
							play->setTocandoBomba(true, i);
							_tiempoBombas = 60;
						}
					}
				}
				//tiempo entre 2 bombas
				_tiempoBombas--;
			}
		}
		//contacto con bomba de pj
		for (play = _players.begin(); play != _players.end(); ++play) {
			for (int i = 0; i < 2; i++) {
				if (play->getTocandoBomba(i) && !(play->isColision(_bombas[i])) && _bombas[i].getEstado()) {
					play->setTocandoBomba(false, i);
				}
			}
		}
		for (play = _players.begin(); play != _players.end(); ++play) {
			for (int i = 0; i < 2; i++) {
				if (!(play->getTocandoBomba(i)) && play->isColision(_bombas[i]) && _bombas[i].getEstado()) {
					play->choqueBloque();
				}
			}
		}
		//contacto con bomba de enemigo
		for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
			for (int i = 0; i < 2; i++) {
				if (it->isColision(_bombas[i]) && _bombas[i].getEstado()) {
					it->choqueBloque();
				}
			}
		}

		for (int i = 0; i < 2; i++) {
			if (_bombas[i].getEstado() == true) {
				bool estado = false;
				_bombas[i].crearExplotar(estado);
				_fuegos[i].setEstado(estado);
				if (_fuegos[i].getEstado()) {
					_fuegos[i].setSpritePosition(_bombas[i].getSprite().getPosition());
				}
				_fuegosV[i].setEstado(estado);
				if (_fuegosV[i].getEstado()) {
					_fuegosV[i].setSpritePosition(_bombas[i].getSprite().getPosition());
				}
			}
		}
		for (int i = 0; i < 2; i++) {
			if (_fuegos[i].getEstado() && _fuegosV[i].getEstado()) {
				_fuegos[i].crearLlama();
				_fuegosV[i].crearLlama();
			}
		}

		//colision y muerte del pj, primero por fuego, luego por chocar enemigos
		for (play = _players.begin(); play != _players.end(); ++play) {
			for (int i = 0; i < 2; i++) {
				if ((_fuegos[i].isColision(*play) && _fuegos[i].getEstado()) || (_fuegosV[i].isColision(*play) && _fuegosV[i].getEstado())) {
					play->setMuriendo(true);
				}
			}
		}
		for (play = _players.begin(); play != _players.end(); ++play) {
			for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
				if (it->isColision(*play) && it->getEstado()) {
					play->setMuriendo(true);

				}
			}
		}
		//colision y muerte de los enemigos con el fuego.
		list<Enemigo>::iterator it2;
		for (it2 = _enemigos.begin(); it2 != _enemigos.end(); ++it2) {
			for (int i = 0; i < 2; i++) {
				if ((_fuegos[i].isColision(*it2) && _fuegos[i].getEstado() && it2->getMuriendo() == false) || (_fuegosV[i].isColision(*it2) && _fuegosV[i].getEstado() && it2->getMuriendo() == false)) {
					it2->setEstado(false);
				}
			}
		}
		//Puerta de la victoria
		_contadorEnemigosEliminados = 0;
		for (it2 = _enemigos.begin(); it2 != _enemigos.end(); ++it2) {
			if (it2->getMuriendo()) {
				_contadorEnemigosEliminados++;
			}
		}
		if (_contadorEnemigosEliminados > 2) {
			_mapa1->setEstadoPV(true);
		}
		if (_mapa1->getEstadoPV()) {
			_mapa1->abrirPuerta();
		}
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (_mapa1->comprobarColisionPuerta(*play)) {
				_gameOver = true;
			}
		}
		if (_enemigosAMatar == 0) {
			//
		}
		//comprobar puntajes por numero de destruibles restantes. Enemigos dan 5 pts
		int destruiblesActuales = _mapa1->getNumeroDestruibles();
		if (_totalDestruibles > destruiblesActuales) {
			_puntaje += (_totalDestruibles - destruiblesActuales);
			_totalDestruibles = destruiblesActuales;
		}
		int enemigosVivosActuales = getEnemigosVivos();
		if (_enemigosAMatar > enemigosVivosActuales) {
			_puntaje += (_enemigosAMatar - enemigosVivosActuales) * 10;
			_enemigosAMatar -= (_enemigosAMatar - enemigosVivosActuales);
		}
		_textoVidas.setString("VIDAS: " + to_string(_vidas));
		_textoPuntaje.setString("PUNTAJE: " + to_string(_puntaje));
		dibujar(_ventana1);
	}
	_musica.stop();
}

void Juego::dibujar(RenderWindow* _ventana1)
{
	_ventana1->clear();
	_ventana1->draw(_fondo);

	_ventana1->draw(_textoVidas);
	_ventana1->draw(_textoPuntaje);

	_mapa1->dibujarVelocidad(_ventana1);
	_mapa1->dibujarBoostBomba(_ventana1);

	_mapa1->dibujarPuertaVictoria(_ventana1);


	_mapa1->dibujarDestruibles(_ventana1);

	for (int i = 0; i < 2; i++) {
		if (_fuegos[i].getEstado()) {
			_ventana1->draw(_fuegos[i]);
		}
		if (_fuegosV[i].getEstado()) {
			_ventana1->draw(_fuegosV[i]);
		}
	}

	_mapa1->dibujarFijos(_ventana1);

	for (int i = 0; i < 2; i++) {
		if (_bombas[i].getEstado() == true) {
			_ventana1->draw(_bombas[i]);
		}
	}

	list<Player>::iterator play;
	for (play = _players.begin(); play != _players.end(); ++play) {
		_ventana1->draw(*play);
	}
	list<Enemigo>::iterator it;
	for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
		_ventana1->draw(*it);
	}
	_ventana1->display();
}
int Juego::getEnemigosVivos()
{
	int cont = 0;
	list<Enemigo>::iterator it;
	for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
		if (it->getEstado() == true) {
			cont++;
		}
	}
	return cont;
}


void Juego::pantallaGameOver(RenderWindow* _ventana1)
{
	while (timerGameOver > 0) {
		if (timerGameOver == 239) {
			if(!_bufGameOver->loadFromFile("gameOver.wav")){}
			_sonidoGameOver->play();
		}

		_ventana1->clear();
		_ventana1->draw(_fondoGameOver);
		_ventana1->display();
		timerGameOver--;
		Event event;
		while (_ventana1->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				_ventana1->close();
			}
		}
	}
}

void Juego::mostarStage(RenderWindow* _ventana1, int numeroStage)
{
	string cadena = "stage" + to_string(numeroStage) + ".jpg";
	_txStage.loadFromFile(cadena);
	_stage.setTexture(_txStage);
	
	while (_timerStage > 0) {
		if (_timerStage == 230) {
			if (!_bufStage->loadFromFile("stage.wav")) {}
			_sonidoStage->setVolume(70);
			_sonidoStage->play();
		}
		_ventana1->clear();
		_ventana1->draw(_stage);
		_ventana1->display();
		_timerStage--;
		Event event;
		while (_ventana1->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				_ventana1->close();
			}
		}
	}
}

