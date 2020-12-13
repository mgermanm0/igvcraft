#include "igvCilindro.h"
#include <cmath>
#include <iostream>
#define PI 3.14159265358979323846 

igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV)
{
	/* Apartado B: Construir la malla de triángulos para representar el cilindro */
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

			//Punto al cual le formaré sus dos triángulos
			int nPunto = divU * i + j;

			//Altura de los puntos que se encuentran arriba del anterior (es decir, a partir de que índice son puntos superiores)
			int altura = divU * (i + 1);

			//punto superior al punto descrito por nPunto
			int superior = nPunto + divU;

			//Punto adyadcente al punto descrito por nPunto
			int siguiente = nPunto + 1;

			/**
			* Formación de triángulos
			* 5--------4
			* |	       |
			* |        |
			* |        |
			* |        |
			* 1--------0
			*
			* 0,1,2,3 son 4 vértices de nuestro cilindro con divU = 4 y divA = 2. Nos imaginamos un rectángulo formado por estos.
			* Queremos formar los dos triángulos que dividen al rectángulo y que contienen al vértice 0.
			*
			* Triángulo 1:
			* 5--------4	A partir del vértice 0, en sentido antihorario, el triángulo que queremos obtener es:
			*  \       |    T0_1 = {5,4,0}. Nuestro bucle "for" está en la iteración 0 (i = 0, j = 0).
			*    \     |    por lo tanto: nPunto = 4*0+0 = 0;
			*      \   |	Los puntos superiores a 0 comenzarán a partir del índice:
			*        \ |    altura = 4*(0+1) = 4
			*          0	El que está justo encima del vértice 0 es:
			*               superior = 0 + 4 = 4
			*               Y el siguiente punto adyadcente al vértice 0 es:
			*               siguiente = 0 + 1 = 1
			* Sabiendo estos parámetros, podemos calcular facilmente ambos triángulos, en este ejemplo el triángulo 1 sería (en sentido antihorario):
			* vértice 0: V0 = superior = 4
			* vértice 1: V1 = (superior + 1) % divU + altura = 5 % 4 + 4 = 1 + 4 = 5
			*  - (superior + 1 ) sería el vértice adyadcente al vértice que está justo encima de nPunto (0 en este caso)
			*  - Es necesario hacer "%divU" ya que en el caso de que el vértice "superior" coincida con el último
			*    vértice de esa altura (por ejemplo, si superior fuese 7), su adyadcente se nos podría ir a otro vértice cuya altura es superior
			*    a la que nos interesa y no el inicial de su altura, es decir:
			*            superior = 7 -> (7 + 1) + 4 = 8 + 4 = 12 MAL
			*                         -> (7 + 1) % 4 + 4 = 8%4 + 4 = 0 + 4 = 4 BIEN
			* vértice 3: V3 = nPunto = 0.
			*
			* El tríangulo 2 se construye de manera similar, solo que ahora necesitamos el vértice
			* adyadcente al vértice indicado por nPunto.
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


	/* Apartado C: Añadir el vector de normales */
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
