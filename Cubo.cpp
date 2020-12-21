#include "Cubo.h"
#include <cmath>
#include "igvPunto3D.h"
#include <iostream>
#define PI 3.14159265358979323846 

Cubo::Cubo() :igvMallaTriangulos()
{
}

Cubo::Cubo(double lado, igvPunto3D& coords, float* color, TipoBloque tipo): coords(coords), color(color), lado(lado), tipo(tipo)
{
	
	long int vnum = 8;
	long int tnum = 12;
	long int tamavertices = vnum * 3;
	long int tamatriangulos = tnum * 3;
	int alturas = 2;
	int divU = 4;
	this->vertices = new float[tamavertices];
	this->triangulos = new unsigned int[tamatriangulos];
	this->normales = new float[tamavertices];
	this->num_vertices = vnum;
	this->num_triangulos = tnum;

	float ang;
	float incrementoA = 2 * PI / 4;
	float diag = sqrt(pow(lado, 2) + pow(lado, 2));
	float y = 0;
	for (int i = 0; i < alturas; i++) {
		ang = 45 * PI / 180;
		for (int j = 0; j < divU; j++) {
			int nPunto = (4 * i + j) * 3;
			float x = cos(ang) * diag/2.0f;
			float z = sin(ang) * diag/2.0f;

			vertices[nPunto] = x;
			vertices[nPunto + 1] = y;
			vertices[nPunto + 2] = z;
			ang += incrementoA;

		}
		y+=lado;
	}

	int nTriangulo = 0;
	for (int i = 0; i < alturas-1; i++) {
		for (int j = 0; j < divU; j++) {

			//Variables auxiliares para formar el triangulo

			//Punto al cual le formar� sus dos tri�ngulos
			int nPunto = divU * i + j;

			//Altura de los puntos que se encuentran arriba del anterior (es decir, a partir de que �ndice son puntos superiores)
			int altura = divU * (i + 1);

			//punto superior al punto descrito por nPunto
			int superior = nPunto + divU;

			//Punto adyadcente al punto descrito por nPunto
			int siguiente = nPunto + 1;

			/**
			* Formaci�n de tri�ngulos
			* 5--------4
			* |	       |
			* |        |
			* |        |
			* |        |
			* 1--------0
			*
			* 0,1,2,3 son 4 v�rtices de nuestro cilindro con divU = 4 y divA = 2. Nos imaginamos un rect�ngulo formado por estos.
			* Queremos formar los dos tri�ngulos que dividen al rect�ngulo y que contienen al v�rtice 0.
			*
			* Tri�ngulo 1:
			* 5--------4	A partir del v�rtice 0, en sentido antihorario, el tri�ngulo que queremos obtener es:
			*  \       |    T0_1 = {5,4,0}. Nuestro bucle "for" est� en la iteraci�n 0 (i = 0, j = 0).
			*    \     |    por lo tanto: nPunto = 4*0+0 = 0;
			*      \   |	Los puntos superiores a 0 comenzar�n a partir del �ndice:
			*        \ |    altura = 4*(0+1) = 4
			*          0	El que est� justo encima del v�rtice 0 es:
			*               superior = 0 + 4 = 4
			*               Y el siguiente punto adyadcente al v�rtice 0 es:
			*               siguiente = 0 + 1 = 1
			* Sabiendo estos par�metros, podemos calcular facilmente ambos tri�ngulos, en este ejemplo el tri�ngulo 1 ser�a (en sentido antihorario):
			* v�rtice 0: V0 = superior = 4
			* v�rtice 1: V1 = (superior + 1) % divU + altura = 5 % 4 + 4 = 1 + 4 = 5
			*  - (superior + 1 ) ser�a el v�rtice adyadcente al v�rtice que est� justo encima de nPunto (0 en este caso)
			*  - Es necesario hacer "%divU" ya que en el caso de que el v�rtice "superior" coincida con el �ltimo
			*    v�rtice de esa altura (por ejemplo, si superior fuese 7), su adyadcente se nos podr�a ir a otro v�rtice cuya altura es superior
			*    a la que nos interesa y no el inicial de su altura, es decir:
			*            superior = 7 -> (7 + 1) + 4 = 8 + 4 = 12 MAL
			*                         -> (7 + 1) % 4 + 4 = 8%4 + 4 = 0 + 4 = 4 BIEN
			* v�rtice 3: V3 = nPunto = 0.
			*
			* El tr�angulo 2 se construye de manera similar, solo que ahora necesitamos el v�rtice
			* adyadcente al v�rtice indicado por nPunto.
			*/

			triangulos[nTriangulo] = superior;
			triangulos[nTriangulo + 1] = (superior + 1) % divU + altura;
			triangulos[nTriangulo + 2] = nPunto;
			nTriangulo += 3;

			triangulos[nTriangulo] = (superior + 1) % divU + altura;
			triangulos[nTriangulo + 1] = siguiente % divU + divU * i;
			triangulos[nTriangulo + 2] = nPunto;
			nTriangulo += 3;
		}
	}

	//tapa
	for (int i = 0; i < alturas; i++) {
		int nPunto = 4 * i;
			triangulos[nTriangulo] = nPunto + 2;
			triangulos[nTriangulo + 1] = nPunto + 1;
			triangulos[nTriangulo + 2] = nPunto;
			nTriangulo += 3;

			triangulos[nTriangulo] = nPunto + 3;
			triangulos[nTriangulo + 1] = nPunto + 2;
			triangulos[nTriangulo + 2] = nPunto;
			nTriangulo += 3;

	}
	
}

Cubo::~Cubo()
{
	if (color) delete[] color;
}

igvPunto3D* Cubo::getCoords()
{
	return &coords;
}

float* Cubo::getColor()
{
	return color;
}

TipoBloque Cubo::getTipo()
{
	return tipo;
}

bool Cubo::puedoRomper()
{
	return esDestruible;
}

void Cubo::visualizarCubo()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, color);
	glTranslatef(coords[X] + lado/2.0, coords[Y], coords[Z] + lado/2.0);
	visualizar();
	glPopMatrix();
}

void Cubo::visualizaCuboSinColor()
{
	float color2[] = { 1,0,0 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, color2);
	glTranslatef(coords[X] + lado / 2.0, coords[Y] + 0.5, coords[Z] + lado / 2.0);
	visualizar();
	glPopMatrix();
}

std::ostream& operator<<(std::ostream& os, const Cubo& cubo)
{
	os << "Coordenadas de bloque: " << cubo.coords[X] << ", " << cubo.coords[Y] << ", " << cubo.coords[Z] << '\n';
	os << "Color: " << cubo.color[X] << ", " << cubo.color[Y] << ", " << cubo.color[Z] << '\n';
	os <<  "Lado: " << cubo.lado;
	return os;
}
