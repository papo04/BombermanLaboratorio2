#pragma once
#include "Movibles.h"
class Player : public Movibles
{
public:
	Player();
	void cmd(Event event,bool acelerar);
	void animacionCaminar(int direccion);
	void morir(int&);

	bool getTocandoBomba(int nBomba) { return _tocandoBomba[nBomba]; }
	void setTocandoBomba(bool tocando,int nBomba) { _tocandoBomba[nBomba] = tocando; }
	void setGanando(bool ganando) { _ganando = ganando; }
	bool getGanando() { return _ganando; }

private:
	bool _tocandoBomba[2] = {};
	bool _ganando = false;
};