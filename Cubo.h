#pragma once
#include "igvMallaTriangulos.h"
#include "tipoCubo.h"
#include "igvPunto3D.h"
#include "igvColor.h"
#include "igvTextura.h"
#include <iostream>
class Cubo : public igvMallaTriangulos
{
private:
	tipoCubo tipo = VACIO;
	igvTextura* tex;
	igvPunto3D coords;
	igvColor color;
	bool esDestruible = true;
	float lado = 1;
	bool marcado = false;
public:
	Cubo();
	Cubo(double lado, igvPunto3D& coords, igvColor& color, tipoCubo tipo, igvTextura* textura);
	~Cubo();
	void visualizar();
	void visualizarCaras();
	igvPunto3D* getCoords();
	igvColor* getColor();
	tipoCubo getTipo();
	bool puedoRomper();
	void visualizarCubo();
	void visualizarCuboBB(int tamaX, int tamaY, int tamaZ);
	void visualizaCuboChunkColor(float* color);
	void visualizaCuboSeleccion();
	void visualizaCuboSinColor();
	void marcar();

	friend std::ostream& operator<< (std::ostream& os, const Cubo& cubo);
};

