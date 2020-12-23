#pragma once
#include "igvMallaTriangulos.h"
#include "tipoCubo.h"
#include "igvPunto3D.h"
#include <iostream>
class Cubo : public igvMallaTriangulos
{
private:
	tipoCubo tipo = VACIO;
	igvTextura* tex;
	igvPunto3D coords;
	float* color;
	bool esDestruible = true;
	float lado = 1;
public:
	Cubo();
	Cubo(double lado, igvPunto3D& coords, float* color, tipoCubo tipo, igvTextura* textura);
	void visualizar();
	~Cubo();
	igvPunto3D* getCoords();
	float* getColor();
	tipoCubo getTipo();
	bool puedoRomper();
	void visualizarCubo();
	void visualizaCuboSinColor();

	friend std::ostream& operator<< (std::ostream& os, const Cubo& cubo);
};

