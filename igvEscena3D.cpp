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

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;

	//Crear un mundo
	mundo = new Mundo(0, 50, 0, 50, 5, 5, 5);
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

void igvEscena3D::visualizar(bool normal, bool gouraud) {
	GLfloat color_malla[] = { 0,0.50,0 };
	// crear luces
	GLfloat luz0[4] = { 7,7,7,1 }; // luz puntual para visualizar el cubo

	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	if (ejes) pintar_ejes();
	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena

	

	glPushMatrix();
	mundo->drawWorld();
	glPopMatrix();
	glPushMatrix();
	Chunk* obtenido = mundo->getChunk(x, z);
	Cubo* cubo = obtenido->getCubo(igvPunto3D(x, 3, z));
	glTranslatef(0, 2, 0);
	float color[] = { 1,0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, color);
	cubo->visualizaCuboSinColor();
	glPopMatrix();
	std::cout << x  << " " << z << "\n";
	Sleep(100);
	x++;
	if (x >= 20) {
		x = 0;
		z++;
		if (z >= 20) {
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