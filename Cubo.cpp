#include "Cubo.h"
#include <cmath>
#include "igvPunto3D.h"
#include <iostream>
#include "igvTextura.h"
#include "igvMaterial.h"
#include "igvColor.h"
#define PI 3.14159265358979323846 

Cubo::Cubo() :igvMallaTriangulos()
{
}

Cubo::Cubo(double lado, igvPunto3D& coords, igvColor& color, tipoCubo tipo, igvTextura* textura) : coords(coords), color(color), lado(lado), tipo(tipo), tex(textura)
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
	this->texarr = new GLfloat[vnum * 2];

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
			float x = cos(ang) * diag / 2.0f;
			float z = sin(ang) * diag / 2.0f;

			vertices[nPunto] = x;
			vertices[nPunto + 1] = y;
			vertices[nPunto + 2] = z;
			ang += incrementoA;

		}
		y += lado;
	}

	int nTriangulo = 0;
	for (int i = 0; i < alturas - 1; i++) {
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

void Cubo::visualizar() {
	/* Apartado B: TODO */
	long int tamatriangulos = 12 * 3;
	igvTextura textur(&std::string(".\\textures\\dirt.png")[0]);
	glPushMatrix();
	for (int i = 0; i < tamatriangulos; i+=6)
	{
		glPushMatrix();
		glBegin(GL_TRIANGLES);
		//std::cout << vertices[triangulos[i] * 3] + 0.5 << " " << vertices[triangulos[i] * 3 + 1] << "\n";

		
		//T2
		glTexCoord2f(0, 0);
		glVertex3f(vertices[triangulos[i + 3 + 1] * 3], vertices[triangulos[i + 3 + 1] * 3 + 1], vertices[triangulos[i + 3 + 1] * 3 + 2]);
		glTexCoord2f(1, 0);
		glVertex3f(vertices[triangulos[i + 3 + 2] * 3], vertices[triangulos[i + 3 + 2] * 3 + 1], vertices[triangulos[i + 3 + 2] * 3 + 2]);
		glTexCoord2f(0, 1);
		glVertex3f(vertices[triangulos[i + 3] * 3], vertices[triangulos[i + 3] * 3 + 1], vertices[triangulos[i + 3] * 3 + 2]);



		glTexCoord2f(1, 0);
		glVertex3f(vertices[triangulos[i + 2] * 3], vertices[triangulos[i + 2] * 3 + 1], vertices[triangulos[i + 2] * 3 + 2]);
		glTexCoord2f(0, 1);
		glVertex3f(vertices[triangulos[i + 1] * 3], vertices[triangulos[i + 1] * 3 + 1], vertices[triangulos[i + 1] * 3 + 2]);
		glTexCoord2f(1, 1);
		glVertex3f(vertices[triangulos[i] * 3], vertices[triangulos[i] * 3 + 1], vertices[triangulos[i] * 3 + 2]);

		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
}

void Cubo::visualizarCaras() {
	
	float colores[] = {
		1,0,0,
		0,1,0,
		0,0,1,
		1,1,0,
		1,0,1,
		0,1,1
	};
	int contColor = 0;
	/* Apartado B: TODO */
	long int tamatriangulos = 12 * 3;
	glPushMatrix();
	for (int i = 0; i < tamatriangulos; i += 6)
	{
		glPushMatrix();
		glColor3fv(&colores[contColor]);
		glBegin(GL_TRIANGLES);
		//std::cout << vertices[triangulos[i] * 3] + 0.5 << " " << vertices[triangulos[i] * 3 + 1] << "\n";


		//T2

		glVertex3f(vertices[triangulos[i + 3 + 1] * 3], vertices[triangulos[i + 3 + 1] * 3 + 1], vertices[triangulos[i + 3 + 1] * 3 + 2]);
		glVertex3f(vertices[triangulos[i + 3 + 2] * 3], vertices[triangulos[i + 3 + 2] * 3 + 1], vertices[triangulos[i + 3 + 2] * 3 + 2]);
		glVertex3f(vertices[triangulos[i + 3] * 3], vertices[triangulos[i + 3] * 3 + 1], vertices[triangulos[i + 3] * 3 + 2]);


		glVertex3f(vertices[triangulos[i + 2] * 3], vertices[triangulos[i + 2] * 3 + 1], vertices[triangulos[i + 2] * 3 + 2]);
		glVertex3f(vertices[triangulos[i + 1] * 3], vertices[triangulos[i + 1] * 3 + 1], vertices[triangulos[i + 1] * 3 + 2]);
		glVertex3f(vertices[triangulos[i] * 3], vertices[triangulos[i] * 3 + 1], vertices[triangulos[i] * 3 + 2]);

		glEnd();
		glPopMatrix();
		contColor+=3;
	}
	glPopMatrix();
}
Cubo::~Cubo()
{
	//if (color) delete[] color;
}

igvPunto3D* Cubo::getCoords()
{
	return &coords;
}

igvColor* Cubo::getColor()
{
	return &color;
}

tipoCubo Cubo::getTipo()
{
	return tipo;
}

bool Cubo::puedoRomper()
{
	return esDestruible;
}

void Cubo::visualizarCubo()
{
	float colorC[] = { color[R] / 255.0, color[G] / 255.0, color[B] / 255.0 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, colorC);
	glTranslatef(coords[X] + lado / 2.0, coords[Y], coords[Z] + lado / 2.0);
	visualizar();
	glPopMatrix();
}

void Cubo::visualizarCuboBB(int tamaX, int tamaY, int tamaZ)
{
	float colorC[] = { color[R] / 255.0, color[G] / 255.0, color[B] / 255.0 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, colorC);
	glTranslatef(coords[X] + tamaX/2.0, coords[Y], coords[Z] + tamaZ/2.0);
	glScalef(tamaX, tamaY, tamaZ);
	igvMallaTriangulos::visualizar();
	glPopMatrix();
}

void Cubo::visualizaCuboChunkColor(float* colorChunk)
{
	glPushMatrix();
	glColor3fv(colorChunk);
	glTranslatef(coords[X] + lado / 2.0, coords[Y], coords[Z] + lado / 2.0);
	igvMallaTriangulos::visualizar();
	glPopMatrix();
}

void Cubo::visualizaCuboSeleccion()
{
	float colorC[] = { color[R] / 255.0, color[G] / 255.0, color[B] / 255.0 };
	glPushMatrix();
	if (marcado) colorC[0] = 1;
	glColor3fv(colorC);
	glTranslatef(coords[X] + lado / 2.0, coords[Y], coords[Z] + lado / 2.0);
	igvMallaTriangulos::visualizar();
	glPopMatrix();
}

void Cubo::visualizaCuboSinColor()
{
	float color2[] = { 1,0,0 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, color2);
	glTranslatef(coords[X] + lado / 2.0, coords[Y], coords[Z] + lado / 2.0);
	visualizar();
	glPopMatrix();
}

void Cubo::marcar()
{
	marcado = true;
}

std::ostream& operator<<(std::ostream& os, const Cubo& cubo)
{
	os << "Coordenadas de bloque: " << cubo.coords[X] << ", " << cubo.coords[Y] << ", " << cubo.coords[Z] << '\n';
	os << "Color: " << cubo.color[X] << ", " << cubo.color[Y] << ", " << cubo.color[Z] << '\n';
	os <<  "Lado: " << cubo.lado;
	return os;
}
