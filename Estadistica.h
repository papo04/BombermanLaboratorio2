#pragma once
#include <iostream>
using namespace std;

class  Estadistica
{
public:
	 int getPuntaje() { return _puntajeTotal; }
	 string getNombre() { return _nombre; }
	 void setPuntaje(int puntaje) { _puntajeTotal = puntaje; }
	 void setNombre(string nombre) { strcpy(_nombre, nombre.c_str()); }

	 bool guardarEnDIsco() {
		 FILE* p = fopen("Estadisticas.dat", "ab");
		 if (p == nullptr)return false;
		 bool ok = fwrite(this, sizeof(Estadistica), 1, p);
		 fclose(p);
		 return ok;
	 }

	 bool leerEnDisco(int pos) {
		 FILE* p = fopen("Estadisticas.dat", "rb");
		 if (p == nullptr)return false;
		 fseek(p, sizeof(Estadistica) * pos, SEEK_SET);
		 bool ok = fread(this, sizeof(Estadistica),1, p);
		 fclose(p);
		 return ok;
	 }

private:
	int _puntajeTotal;
	char _nombre[5];
};