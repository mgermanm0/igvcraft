#include "Cubo.h"
#include <cmath>
#include "igvPunto3D.h"
#include <iostream>
#include "igvTextura.h"
#include "igvMaterial.h"
#include "igvColor.h"
#include "caraCubo.h"
#define PI 3.14159265358979323846 

igvColor Cubo::colores[] = {
		igvColor(255,0,0,0),
		igvColor(0,255,0,0),
		igvColor(0,0,255,0),
		igvColor(255,255,0,0),
		igvColor(255,0,255,0),
		igvColor(0,255,255,0)
};

caraCubo Cubo::caras[] = {
	DELANTERA,
	IZQ,
	TRASERA,
	DER,
	TAPA,
	BASE
};
float Cubo::normal[] = {
	0,0,1,
	-1,0,0,
	0,0,-1,
	1,0,0,
	0,1,0,
	0,-1,0
};

Cubo::Cubo() :igvMallaTriangulos()
{
}

Cubo::Cubo(double lado, igvPunto3D& coords, igvColor& color, tipoCubo tipo, bool destructible) : coords(coords), color(color), lado(lado), tipo(tipo), esDestruible(destructible)
{
	long int vnum = 8;
	long int tnum = 12;
	long int tamavertices = vnum * 3;
	long int tamatriangulos = tnum * 3;
	int alturas = 2;
	int divU = 4;
	this->vertices = new float[tamavertices];
	this->triangulos = new unsigned int[tamatriangulos];

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

			triangulos[nTriangulo] = (superior + 1) % divU + altura;
			triangulos[nTriangulo + 1] = siguiente % divU + divU * i;
			triangulos[nTriangulo + 2] = nPunto;
			nTriangulo += 3;




			triangulos[nTriangulo] = superior;
			triangulos[nTriangulo + 1] = (superior + 1) % divU + altura;
			triangulos[nTriangulo + 2] = nPunto;
			nTriangulo += 3;
		}
	}
	//tapa
	for (int i = alturas-1; i >= 0; i--) {
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

caraCubo Cubo::caraSeleccionada(igvColor& color) {
	for (int i = 0; i < 6; i++)
	{
		if (color == colores[i]) return caras[i];
	}
	return NO_ENCONTRADA; //no deberia llegar aqui;
}

void Cubo::visualizar(TextureLoader* tl) {
	/* Apartado B: TODO */
	long int tamatriangulos = 12 * 3;
	glPushMatrix();
	igvTextura* lados = tl->getTextura(tipo);
	igvTextura* tapa = nullptr;
	igvTextura* base = nullptr;
	switch (tipo)
	{
	case CESPED:
		tapa = tl->getTextura(CESPED_TOP);
		base = tl->getTextura(TIERRA);
		break;
	}
	for (int c = 0; c < 6; c++)
	{
		int i = c * 6;
		if (c == 4 && tapa != nullptr) tapa->aplicar();
		else if (c == 5 && base != nullptr) base->aplicar();
		else lados->aplicar();
		glPushMatrix();
		glNormal3fv(&normal[c * 3]);
		glBegin(GL_TRIANGLES);

		glTexCoord2f(1, 0);
		glVertex3f(vertices[triangulos[i] * 3], vertices[triangulos[i] * 3 + 1], vertices[triangulos[i] * 3 + 2]);
		glTexCoord2f(1, 1);
		glVertex3f(vertices[triangulos[i + 1] * 3], vertices[triangulos[i + 1] * 3 + 1], vertices[triangulos[i + 1] * 3 + 2]);
		glTexCoord2f(0, 1);
		glVertex3f(vertices[triangulos[i + 2] * 3], vertices[triangulos[i + 2] * 3 + 1], vertices[triangulos[i + 2] * 3 + 2]);
	
		i += 3;
		glTexCoord2f(0, 0);
		glVertex3f(vertices[triangulos[i] * 3], vertices[triangulos[i] * 3 + 1], vertices[triangulos[i] * 3 + 2]);
		glTexCoord2f(1, 0);
		glVertex3f(vertices[triangulos[i + 1] * 3], vertices[triangulos[i + 1] * 3 + 1], vertices[triangulos[i + 1] * 3 + 2]);
		glTexCoord2f(0, 1);
		glVertex3f(vertices[triangulos[i + 2] * 3], vertices[triangulos[i + 2] * 3 + 1], vertices[triangulos[i + 2] * 3 + 2]);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
}

void Cubo::visualizarCaras() {
	
	int contColor = 0;
	/* Apartado B: TODO */
	long int tamatriangulos = 12 * 3;
	glPushMatrix();
	for (int i = 0; i < tamatriangulos; i += 6)
	{
		colores[contColor].aplicar();
		glBegin(GL_TRIANGLES);


		glVertex3f(vertices[triangulos[i + 2] * 3], vertices[triangulos[i + 2] * 3 + 1], vertices[triangulos[i + 2] * 3 + 2]);
		glVertex3f(vertices[triangulos[i + 1] * 3], vertices[triangulos[i + 1] * 3 + 1], vertices[triangulos[i + 1] * 3 + 2]);
		glVertex3f(vertices[triangulos[i] * 3], vertices[triangulos[i] * 3 + 1], vertices[triangulos[i] * 3 + 2]);

		glVertex3f(vertices[triangulos[i + 3 + 1] * 3], vertices[triangulos[i + 3 + 1] * 3 + 1], vertices[triangulos[i + 3 + 1] * 3 + 2]);
		glVertex3f(vertices[triangulos[i + 3 + 2] * 3], vertices[triangulos[i + 3 + 2] * 3 + 1], vertices[triangulos[i + 3 + 2] * 3 + 2]);
		glVertex3f(vertices[triangulos[i + 3] * 3], vertices[triangulos[i + 3] * 3 + 1], vertices[triangulos[i + 3] * 3 + 2]);

		glEnd();
		contColor++;
	}
	glPopMatrix();
}
Cubo::~Cubo()
{
}

igvPunto3D* Cubo::getCoords()
{
	return &coords;
}

double Cubo::getCoordX()
{
	return coords[X];
}

double Cubo::getCoordY()
{
	return coords[Y];
}

double Cubo::getCoordZ()
{
	return coords[Z];
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

void Cubo::visualizarCubo(TextureLoader* tl)
{
	glPushMatrix();
	glTranslatef(coords[X] + lado / 2.0, coords[Y], coords[Z] + lado / 2.0);
	visualizar(tl);
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

void Cubo::visualizaCarasCuboSeleccion()
{
	glPushMatrix();
	glTranslatef(coords[X] + lado / 2.0, coords[Y], coords[Z] + lado / 2.0);
	visualizarCaras();
	glPopMatrix();
}


void Cubo::marcar()
{
	marcado = true;
}

void Cubo::setTipo(tipoCubo tipo)
{
	this->tipo = tipo;
}

std::ostream& operator<<(std::ostream& os, const Cubo& cubo)
{
	os << "Coordenadas de bloque: " << cubo.coords[X] << ", " << cubo.coords[Y] << ", " << cubo.coords[Z] << '\n';
	os << "Color: " << cubo.color[X] << ", " << cubo.color[Y] << ", " << cubo.color[Z] << '\n';
	os <<  "Lado: " << cubo.lado;
	return os;
}
