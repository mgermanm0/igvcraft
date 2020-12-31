#pragma once
#include "igvMallaTriangulos.h"
#include "tipoCubo.h"
#include "igvPunto3D.h"
#include "igvColor.h"
#include "igvTextura.h"
#include "caraCubo.h"
#include "TextureLoader.h"
#include "igvMaterial.h"
#include <iostream>
class Cubo : public igvMallaTriangulos
{
private:
	tipoCubo tipo = VACIO;
	igvPunto3D coords;
	igvColor color;
	bool esDestruible = true;
	float lado = 1;
	bool marcado = false;
public:
	static igvColor colores[];
	static caraCubo caras[];
	static float normal[];
	Cubo();
	Cubo(double lado, igvPunto3D& coords, igvColor& color, tipoCubo tipo, bool destructible);
	~Cubo();
	caraCubo caraSeleccionada(igvColor& color);
	void visualizar(TextureLoader* tl);
	void visualizarCaras();
	igvPunto3D* getCoords();
	double getCoordX();
	double getCoordY();
	double getCoordZ();
	igvColor* getColor();
	tipoCubo getTipo();
	bool puedoRomper();
	void visualizarCubo(TextureLoader* tl);
	void visualizaCuboChunkColor(float* color);
	void visualizaCuboSeleccion();
	void visualizaCarasCuboSeleccion();
	void marcar();
	void setTipo(tipoCubo tipo);
	friend std::ostream& operator<< (std::ostream& os, const Cubo& cubo);
};

