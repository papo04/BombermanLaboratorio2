#pragma once
#include "Inamovibles.h"
class BloqueFijo: public Inamovibles 
{
public:
	BloqueFijo(int a, int b);
	void setTexture();
	void setPosicion(int a, int b);
};

