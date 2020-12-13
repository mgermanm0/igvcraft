#include "igvCilindro.h"
#include <cmath>
#include <iostream>
#define PI 3.14159265358979323846 

igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV)
{
	/* Apartado B: Construir la malla de tri�ngulos para representar el cilindro */
	//cos alfa es X y sen alfa es y
	//pasar a radianes
	long int vnum = divV * divU + divU;
	long int tnum = divU*divV*2;
	long int tamavertices = vnum * 3;
	long int tamatriangulos = tnum * 3;

	this->vertices = new float[tamavertices];
	this->triangulos = new unsigned int[tamatriangulos];
	this->normales = new float[tamavertices];
	this->num_vertices = vnum;
	this->num_triangulos = tnum;

	float ang;
	float incrementoA = 2 * PI / divU;
	float incrementoH = a / divV;
	
	for (int i = 0; i <= divV; i++) {
		ang = 0;
		float y = i * incrementoH;
		for (int j = 0; j < divU; j++) {
			int nPunto = (divU * i + j) * 3;
			float x = cos(ang) * r;
			float z = sin(ang) * r;

			vertices[nPunto] = x;
			vertices[nPunto + 1] = y;
			vertices[nPunto + 2] = z;
			ang += incrementoA;
		}
	}

	int nTriangulo = 0;
	for (int i = 0; i < divV; i++) {
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


	/* Apartado C: A�adir el vector de normales */
	//divido entre r para obtener vectores unitarios
	for (int i = 0; i <= divV; i++) {
		for (int j = 0; j < divU; j++) {
			int nPunto = (divU * i + j) * 3;
			if (divV == 0) {
				//normalizar
				normales[nPunto] = vertices[nPunto] / r;
				normales[nPunto + 1] = vertices[nPunto + 1];
				normales[nPunto + 2] = vertices[nPunto + 2] / r;
			}
			else {
				normales[nPunto] = vertices[nPunto];
				normales[nPunto + 1] = vertices[nPunto + 1];
				normales[nPunto + 2] = vertices[nPunto + 2];
			}
		}
	}

}

igvCilindro::~igvCilindro()
{
}
