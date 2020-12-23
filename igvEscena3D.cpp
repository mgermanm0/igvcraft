#include <cstdlib>
#include <stdio.h>
#include <cmath>

#include "Mundo.h"
#include "igvEscena3D.h"
#include "igvMallaTriangulos.h"
#include "igvCilindro.h"
#include "Cubo.h"
#include "Chunk.h"
#include <iostream>
#include "igvFuenteLuz.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;

	//Crear un mundo
	mundo = new Mundo(0, 10, 0, 10, 2, 5, 2);
}

igvEscena3D::~igvEscena3D() {
	if (mundo) delete mundo;
	delete malla;
}


// Metodos publicos 

void pintar_ejes(void) {
	GLfloat rojo[] = { 1,0,0,1.0 };
	GLfloat verde[] = { 0,1,0,1.0 };
	GLfloat azul[] = { 0,0,1,1.0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
	glBegin(GL_LINES);
	glVertex3f(1000, 0, 0);
	glVertex3f(-1000, 0, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, verde);
	glBegin(GL_LINES);
	glVertex3f(0, 1000, 0);
	glVertex3f(0, -1000, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();
}

void pintar_cruceta(void) {
	GLfloat rojo[] = { 1,0,0,1.0 };
	GLfloat verde[] = { 0,1,0,1.0 };
	GLfloat azul[] = { 0,0,1,1.0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
	glBegin(GL_LINES);
	glVertex3f(1000, 0, 0);
	glVertex3f(-1000, 0, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, verde);
	glBegin(GL_LINES);
	glVertex3f(0, 1000, 0);
	glVertex3f(0, -1000, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();
}

void igvEscena3D::visualizar(bool normal, bool gouraud) {
	GLfloat color_malla[] = { 0,0.50,0 };
	// crear luces
	igvFuenteLuz luzDireccional(GL_LIGHT0, igvPunto3D(20, 20, 20), igvColor(0, 0, 0, 1), igvColor(1, 1, 1, 1), igvColor(1, 1, 1, 1), 1, 0, 0);
	luzDireccional.aplicar();

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	if (ejes) pintar_ejes();
	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena

	

	glPushMatrix();
	double lado = 1;
	float color[] = { 0,0,0 };
	mundo->drawWorld();
	//Chunk* obtenido = mundo->getChunk(x, z);
	//Cubo* cubo = obtenido->getCubo(igvPunto3D(x, 3, z));
	//glTranslatef(0, 2, 0);
	//float color[] = { 1,0,0 };
	//glMaterialfv(GL_FRONT, GL_EMISSION, color);
	//cubo->visualizaCuboSinColor();
	glPopMatrix();
	x++;
	if (x >= 50) {
		x = 0;
		z++;
		if (z >= 50) {
			z = 0;
		}	
	}
	glPopMatrix(); // restaura la matriz de modelado
}

void igvEscena3D::incrementaAngulo(char eje, double incremento) {
	switch (eje) {
	case 'X':
		anguloX += incremento;
		break;
	case 'Y':
		anguloY += incremento;
		break;
	case 'Z':
		anguloZ += incremento;
		break;
	}
}