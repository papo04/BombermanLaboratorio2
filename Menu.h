#pragma once
#include <SFML/Graphics.hpp>
#include "Juego.h";
#include "Nivel2.h"
#include "Nivel3.h"

#define MAX_NUMBER_OF_ITEMS 4

enum estado {
	pide_nombre, estadistica, creditos, menu, nulo
};

class Menu
{
public:
	Menu(float width, float height);
	void run();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int getOpcionSelected();

	void pantallaEstadisticas(RenderWindow* windows);
	void pantallaCreditos(RenderWindow* windows);
	void agregarPuntaje(int puntaje);
	int cantidadRegistrosEstadistica();
	Estadistica* listarEstadisticasOrdenadas();

private:
	estado _estado = menu;
	int opcion_selected;
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text opcion[MAX_NUMBER_OF_ITEMS];
	string _nombreFinal;
	sf::Text Text_nombre;
	void ingresar_nombre(sf::RenderWindow* window);
	Estadistica* _vec;
};

