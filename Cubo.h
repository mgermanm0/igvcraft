#pragma once
#include "igvMallaTriangulos.h"
#include "TipoBloque.h"
#include "igvPunto3D.h"
#include <iostream>
using namespace UtilesBloques;
class Cubo : public igvMallaTriangulos
{
private:
	TipoBloque tipo = VACIO;
	igvPunto3D coords;
	float* color;
	bool esDestruible = true;
	float lado = 1;
public:
	Cubo();
	Cubo(double lado, igvPunto3D& coords, float* color, TipoBloque tipo);
	~Cubo();
	igvPunto3D* getCoords();
	float* getColor();
	TipoBloque getTipo();
	bool puedoRomper();
	void visualizarCubo();
	void visualizaCuboSinColor();

	friend std::ostream& operator<< (std::ostream& os, const Cubo& cubo);
};

