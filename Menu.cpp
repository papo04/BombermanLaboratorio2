#include "Menu.h"
#include <iostream>
#include <conio.h>
#include <SFML/Audio.hpp>


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("fonts/8-bit-hud.ttf")) {
		//error
	}
	opcion[0].setFont(font);
	opcion[0].setFillColor(sf::Color::Magenta);
	opcion[0].setString("PLAY");
	opcion[0].setPosition(sf::Vector2f(width / 2 - opcion[0].getGlobalBounds().width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	opcion[0].setOutlineColor(sf::Color::White);
	opcion[0].setOutlineThickness(1.00);

	opcion[1].setFont(font);
	opcion[1].setFillColor(sf::Color::Black);
	opcion[1].setString("LEADERBOARD");
	opcion[1].setPosition(sf::Vector2f(width / 2 - opcion[1].getGlobalBounds().width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	opcion[1].setOutlineColor(sf::Color::White);
	opcion[1].setOutlineThickness(1.00);

	opcion[2].setFont(font);
	opcion[2].setFillColor(sf::Color::Black);
	opcion[2].setString("CREDITS");
	opcion[2].setPosition(sf::Vector2f(width / 2 - opcion[2].getGlobalBounds().width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	opcion[2].setOutlineColor(sf::Color::White);
	opcion[2].setOutlineThickness(1.00);

	opcion[3].setFont(font);
	opcion[3].setFillColor(sf::Color::Black);
	opcion[3].setString("EXIT");
	opcion[3].setPosition(sf::Vector2f(width / 2 - opcion[3].getGlobalBounds().width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));
	opcion[3].setOutlineColor(sf::Color::White);
	opcion[3].setOutlineThickness(1.00);


	opcion_selected = 0;
}

void Menu::run() {
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Menu");

	sf::Sprite fondo;
	sf::Texture texture;
	texture.loadFromFile("img/fondo.jpg");
	fondo.setTexture(texture);

	sf::Event event;
	while (window->isOpen()) {
		switch (_estado)
		{
		case pide_nombre: {
			ingresar_nombre(window);
		}break;

		case estadistica: {
			pantallaEstadisticas(window);
		}break;

		case creditos: {
			pantallaCreditos(window);

		}break;

		case nulo: {
			Juego* _juego1 = new Juego(window);
			_juego1->mostarStage(window, 1);
			_juego1->gamePlay(window);//transcurre el juego mientras no gane o pierda.
			if (_juego1->getVidas() == 0) {
				//si muere en primer pantalla no pasa de nivel. y asi con los siguientes niveles.
				_juego1->pantallaGameOver(window);
			}
			else {
				Nivel2* _nivel2 = new Nivel2(window, _juego1->getPuntaje(), _juego1->getVidas());
				delete _juego1;
				_nivel2->mostarStage(window, 2);
				_nivel2->gamePlay(window);
				if (_nivel2->getVidas() == 0) {
					_nivel2->pantallaGameOver(window);
				}
				else {
					Nivel3* _nivel3 = new Nivel3(window, _nivel2->getPuntaje(), _nivel2->getVidas());
					delete _nivel2;
					_nivel3->mostarStage(window, 3);
					_nivel3->gamePlay(window);
					if (_nivel3->getVidas() == 0) {
						_nivel3->pantallaGameOver(window);
					}
					else {
						_nivel3->pantallaVictoria(window);
						int puntosAcumulados = _nivel3->getPuntaje();
						// se toma en cuenta los puntos al final del ultimo nivel para el archivo y estadisticas.
						// de acá se toma window para mostrar resultados, siempre nos manejamos con esa ventana.
						// y Solo puntua cuando gana las 3 pantalalas

						//agregar puntaje.
						agregarPuntaje(_nivel3->getPuntaje());
						delete _nivel3;
					}
				}
			}
			_estado = menu;
		}break;

		case menu: {
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					window->close();
				}

				if (event.type == sf::Event::KeyReleased) {
					switch (event.key.code) {
					case sf::Keyboard::Up: {
						MoveUp();
					}break;

					case sf::Keyboard::Down: {
						MoveDown();
					}break;

					case sf::Keyboard::Enter: {
						switch (getOpcionSelected()) {
						case 0: { //Play Game
							_estado = pide_nombre;
							//Ingresar nombre jugador

						}break;

						case 1: {
							_estado = estadistica;
						}break;

						case 2: {
							_estado = creditos;
							//credits.run() //hace falta una clase de creditos
						}break;

						case 3: {
							std::cout << "exit" << std::endl;
							window->close();
							return;
						}break;
						}
					}
					}
				}
				//updates


				window->clear();
				//draws
				window->draw(fondo);
				draw(*window);

				window->display();
			}

		}break;

		}
	}
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(opcion[i]);
	}
}

void Menu::MoveUp()
{
	if (opcion_selected - 1 >= 0) {
		opcion[opcion_selected].setFillColor(sf::Color::Black);
		opcion_selected--;
		opcion[opcion_selected].setFillColor(sf::Color::Magenta);

	}
}

void Menu::MoveDown()
{
	if (opcion_selected + 1 < MAX_NUMBER_OF_ITEMS) {
		opcion[opcion_selected].setFillColor(sf::Color::Black);
		opcion_selected++;
		opcion[opcion_selected].setFillColor(sf::Color::Magenta);

	}
}


int Menu::getOpcionSelected()
{
	return opcion_selected;
}

void Menu::pantallaEstadisticas(RenderWindow* windows)
{
	_vec = listarEstadisticasOrdenadas();

	//window = new sf::RenderWindow(sf::VideoMode(400,100),"Menu");
	sf::Event event;
	sf::Sprite fondo;
	sf::Texture texture;
	texture.loadFromFile("img/fondo.jpg");
	fondo.setTexture(texture);
	Text score[5], titulo, accion;
	Font fuente;
	fuente.loadFromFile("fuente.ttf");

	titulo.setPosition(150, 70);
	//titulo.setColor(Color::Yellow);
	titulo.setOutlineThickness(5);
	titulo.setFillColor(Color::Yellow);
	titulo.setFont(fuente);
	titulo.setCharacterSize(40);
	titulo.setString("5 MEJORES");
	for (int i = 0; i < 5; i++) {
		//score[i].setColor(Color::Yellow);
		score[i].setFont(fuente);
		score[i].setCharacterSize(40);
		score[i].setOutlineThickness(2.5);
		score[i].setOutlineColor(Color::Black);
		score[i].setPosition(160, i * 60 + 200);

		score[i].setString(_vec[i].getNombre() + "      " + to_string(_vec[i].getPuntaje()));
	}
	accion.setFont(fuente);
	accion.setPosition(150, 520);
	accion.setFillColor(Color::Black);
	accion.setOutlineColor(Color::White);
	accion.setOutlineThickness(1);
	accion.setCharacterSize(15);
	accion.setString("Presione Espacio para salir");

	while (_estado == estadistica)
	{
		window->clear();
		//draws
		window->draw(fondo);
		window->draw(Text_nombre);
		for (int i = 0; i < 5; i++) {
			windows->draw(score[i]);
		}
		windows->draw(titulo);
		windows->draw(accion);
		//draw(*window);
		window->display();
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (event.type == Event::KeyPressed) {
			}
			if (event.key.code == Keyboard::Space) {
				_estado = menu;
			}

		}
	}
}

void Menu::pantallaCreditos(RenderWindow* windows)
{
	sf::Event event;
	sf::Sprite fondo;
	sf::Texture texture;
	texture.loadFromFile("img/fondo.jpg");
	fondo.setTexture(texture);
	Text score, titulo, accion;
	Font fuente;
	Estadistica* vec = listarEstadisticasOrdenadas();
	fuente.loadFromFile("fuente.ttf");

	titulo.setPosition(80, 70);
	//titulo.setColor(Color::Yellow);
	titulo.setOutlineThickness(5);
	titulo.setFillColor(Color::Yellow);
	titulo.setFont(fuente);
	titulo.setCharacterSize(40);
	titulo.setString(" CREDITOS:");

	score.setFont(fuente);
	score.setCharacterSize(25);
	score.setOutlineThickness(2.5);
	score.setOutlineColor(Color::Black);
	score.setPosition(80, 160);
	score.setString(" MAGNAVACHI PABLO\n\n VUELTA AGUSTIN \n\n BELTRAN DANTE \n\n BELTRAN TEO");

	accion.setFont(fuente);
	accion.setPosition(150, 520);
	accion.setFillColor(Color::Black);
	accion.setOutlineColor(Color::White);
	accion.setOutlineThickness(1);
	accion.setCharacterSize(15);
	accion.setString("Presione Espacio para salir");

	while (_estado == creditos)
	{
		window->clear();
		//draws
		window->draw(fondo);
		window->draw(Text_nombre);
		windows->draw(score);
		windows->draw(titulo);
		windows->draw(accion);
		//draw(*window);
		window->display();
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (event.type == Event::KeyPressed) {
			}
			if (event.key.code == Keyboard::Space) {
				_estado = menu;
			}

		}
	}
}

void Menu::agregarPuntaje(int puntaje)
{
	Estadistica est;
	est.setNombre(_nombreFinal);
	est.setPuntaje(puntaje);
	est.guardarEnDIsco();
}

int Menu::cantidadRegistrosEstadistica()
{
	FILE* p = fopen("Estadisticas.dat", "rb");
	if (p == nullptr)return 0;
	fseek(p, 0, SEEK_END);
	int cantidad = ftell(p) / sizeof(Estadistica);
	fclose(p);
	return cantidad;
}

Estadistica* Menu::listarEstadisticasOrdenadas()
{
	int cantidad = cantidadRegistrosEstadistica();
	Estadistica* vec = new Estadistica[cantidad];
	Estadistica aux;
	for (int i = 0; i < cantidad; i++) {
		vec[i].leerEnDisco(i);
	}
	for (int i = 0; i < cantidad; i++) {
		for (int j = 0; j < cantidad - 1; j++) {
			if (vec[j].getPuntaje() < vec[j + 1].getPuntaje()) {
				aux = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = aux;
			}
		}
	}
	return vec;
}

void Menu::ingresar_nombre(sf::RenderWindow* window)
{
	char nombre_player[15];
	Font fuente;
	Text titulo;
	fuente.loadFromFile("fuente.ttf");
	titulo.setPosition(100, 120);
	titulo.setOutlineThickness(5);
	titulo.setFillColor(Color::Yellow);
	titulo.setFont(fuente);
	titulo.setCharacterSize(25);
	titulo.setString("INGRESE NOMBRE:");
	//window = new sf::RenderWindow(sf::VideoMode(400,100),"Menu");
	sf::Event event;
	sf::Sprite fondo;
	sf::Texture texture;
	texture.loadFromFile("img/fondo.jpg");
	fondo.setTexture(texture);



	int letras_ingresadas = 0;

	for (int i = 0; i < 15; i++) {
		nombre_player[i] = NULL;
	}

	while (_estado == pide_nombre) {

		window->clear();
		//draws
		window->draw(fondo);
		window->draw(Text_nombre);
		window->draw(titulo);
		//draw(*window);
		window->display();


		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				//window.close();
			}

			if (event.type == sf::Event::KeyReleased) {

				if (letras_ingresadas != 4) {

					switch (event.key.code) {

					case sf::Keyboard::BackSpace: {
						if (letras_ingresadas > 0) {
							letras_ingresadas--;
							nombre_player[letras_ingresadas] = ' ';
							letras_ingresadas--;
						}
					}break;

					case sf::Keyboard::A: {
						nombre_player[letras_ingresadas] = 'A';
					}break;

					case sf::Keyboard::B: {
						nombre_player[letras_ingresadas] = 'B';
					}break;

					case sf::Keyboard::C: {
						nombre_player[letras_ingresadas] = 'C';
					}break;

					case sf::Keyboard::D: {
						nombre_player[letras_ingresadas] = 'D';
					}break;

					case sf::Keyboard::E: {
						nombre_player[letras_ingresadas] = 'E';
					}break;

					case sf::Keyboard::F: {
						nombre_player[letras_ingresadas] = 'F';
					}break;

					case sf::Keyboard::G: {
						nombre_player[letras_ingresadas] = 'G';
					}break;

					case sf::Keyboard::H: {
						nombre_player[letras_ingresadas] = 'H';
					}break;

					case sf::Keyboard::I: {
						nombre_player[letras_ingresadas] = 'I';
					}break;

					case sf::Keyboard::J: {
						nombre_player[letras_ingresadas] = 'J';
					}break;

					case sf::Keyboard::K: {
						nombre_player[letras_ingresadas] = 'K';
					}break;

					case sf::Keyboard::L: {
						nombre_player[letras_ingresadas] = 'L';
					}break;

					case sf::Keyboard::M: {
						nombre_player[letras_ingresadas] = 'M';
					}break;

					case sf::Keyboard::N: {
						nombre_player[letras_ingresadas] = 'N';
					}break;

					case sf::Keyboard::O: {
						nombre_player[letras_ingresadas] = 'O';
					}break;

					case sf::Keyboard::P: {
						nombre_player[letras_ingresadas] = 'P';
					}break;

					case sf::Keyboard::Q: {
						nombre_player[letras_ingresadas] = 'Q';
					}break;

					case sf::Keyboard::R: {
						nombre_player[letras_ingresadas] = 'R';
					}break;

					case sf::Keyboard::S: {
						nombre_player[letras_ingresadas] = 'S';
					}break;

					case sf::Keyboard::T: {
						nombre_player[letras_ingresadas] = 'T';
					}break;

					case sf::Keyboard::U: {
						nombre_player[letras_ingresadas] = 'U';
					}break;

					case sf::Keyboard::V: {
						nombre_player[letras_ingresadas] = 'V';
					}break;

					case sf::Keyboard::W: {
						nombre_player[letras_ingresadas] = 'W';
					}break;

					case sf::Keyboard::X: {
						nombre_player[letras_ingresadas] = 'X';
					}break;

					case sf::Keyboard::Y: {
						nombre_player[letras_ingresadas] = 'Y';
					}break;

					case sf::Keyboard::Z: {
						nombre_player[letras_ingresadas] = 'Z';
					}break;

					case sf::Keyboard::Num0: {
						nombre_player[letras_ingresadas] = '0';
					}break;

					case sf::Keyboard::Num1: {
						nombre_player[letras_ingresadas] = '1';
					}break;

					case sf::Keyboard::Num2: {
						nombre_player[letras_ingresadas] = '2';
					}break;

					case sf::Keyboard::Num3: {
						nombre_player[letras_ingresadas] = '3';
					}break;

					case sf::Keyboard::Num4: {
						nombre_player[letras_ingresadas] = '4';
					}break;

					case sf::Keyboard::Num5: {
						nombre_player[letras_ingresadas] = '5';
					}break;

					case sf::Keyboard::Num6: {
						nombre_player[letras_ingresadas] = '6';
					}break;

					case sf::Keyboard::Num7: {
						nombre_player[letras_ingresadas] = '7';
					}break;

					case sf::Keyboard::Num8: {
						nombre_player[letras_ingresadas] = '8';
					}break;

					case sf::Keyboard::Num9: {
						nombre_player[letras_ingresadas] = '9';
					}break;

					default: {
						letras_ingresadas--;
					}break;
					}

					letras_ingresadas++;
				}


			_nombreFinal = nombre_player;
				if (letras_ingresadas == 4) {//chequea espacios, si se aprieta enter, cambio estado
					if (event.type == sf::Event::KeyReleased) {
						if (event.key.code == sf::Keyboard::Enter) {
							for (int i = 0; i < 4; i++) {
								nombre_player[i] = NULL;
							}
							_estado = nulo;
						}
					}
				}

			}

			if (!font.loadFromFile("fonts/8-bit-hud.ttf")) {
				//error
			}


			Text_nombre.setFont(font);
			Text_nombre.setFillColor(sf::Color::White);
			Text_nombre.setString(nombre_player);
			Text_nombre.setCharacterSize(40);
			Text_nombre.setOutlineThickness(3);
			Text_nombre.setOutlineColor(Color::Black);
			Text_nombre.setPosition(sf::Vector2f(800 / 2 - letras_ingresadas * 30, 600 / 2));
		}
	}
}

