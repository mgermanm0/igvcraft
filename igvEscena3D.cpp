#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include "Mundo.h"
#include "igvEscena3D.h"
#include "igvMallaTriangulos.h"
#include "Cubo.h"
#include "Chunk.h"
#include <iostream>
#include "igvFuenteLuz.h"
#include "orientacion.h"
// Metodos constructores 

igvEscena3D::igvEscena3D() {

	//Crear un mundo
	mundo = new Mundo(0, 25, 0, 25, 5, 25, 5);
}

igvEscena3D::~igvEscena3D() {
	if (mundo) delete mundo;
	if (tloader) delete tloader;
}



void igvEscena3D::visualizar() {
	glPushMatrix();
	// crear luces

	if (!tloader) {
		tloader = new TextureLoader();
		mundo->setTextureLoader(tloader);
	}

	igvFuenteLuz luz0(GL_LIGHT0, igvPunto3D(10, 100, 10), igvColor(0, 0, 0.2, 0), igvColor(contLuz < 10 ? 1 : 0, contLuz < 20 && contLuz > 10 ? 1 : 0, contLuz < 30 && contLuz > 20 ? 1 : 0, 1), igvColor(contLuz == 1000 ? 1 : 0, contLuz == 2000 ? 1 : 0, contLuz == 3000 ? 1 : 0, 1), 1, 0, 0, igvPunto3D(0, -1, 0), 120, 80);
	igvFuenteLuz luz1(GL_LIGHT1, igvPunto3D(10, 100, 10), igvColor(0, 0, 0.2, 0), igvColor(1,1,1,1), igvColor(1,1,1,1), 1, 0, 0, igvPunto3D(0, -1, 0), 120, 80);
	luz0.apagar();
	if (rgb) {
		if (!luz0.esta_encendida()) { 
			luz1.apagar(); 
			luz0.encender();
		}

		contLuz %= 30;
		contLuz++;
	}
	else {
		if (!luz1.esta_encendida()) {
			luz0.apagar();
			luz1.encender();
		}
	}
	luz1.aplicar();
	luz0.aplicar();
	//igvFuenteLuz foco1(GL_LIGHT1, igvPunto3D(10, 10, 10), igvColor(0, 0, 0, 1), igvColor(1, 1, 1, 1), igvColor(1, 1, 1, 1), 1, 0, 0, igvPunto3D(0, -1, 0), 45, 30);
	//foco1.aplicar();

	/* Apartado D: definir y aplicar las propiedades de material indicadas en el guión de prácticas */
	igvMaterial material(igvColor(1, 1, 1), igvColor(1, 1, 1), igvColor(1, 1, 1), 60);
	material.aplicar();
	
	switch (tipo) {
	case NORMAL:
		mundo->drawWorld();
		break;
	case SELCHUNK:
		mundo->drawWorldChunksVB();
		break;
	case SELBLOQUE:
		selChunk[CENTRO]->drawChunkSeleccionCubo();
		break;
	case SELCARA:
		selCubo->visualizaCarasCuboSeleccion();
		break;
	}
	glPopMatrix();
}

void igvEscena3D::cambiarRGB()
{
	rgb = !rgb;
}

void igvEscena3D::visualizarMundoSeleccion()
{
	mundo->drawWorldChunksVB();
}

Chunk* igvEscena3D::getChunkByColor(igvColor& color) {
	return mundo->getChunkSeleccion(color);
}

Chunk** igvEscena3D::getFronteraByColor(igvColor& color) {
	return mundo->getChunkSeleccionFrontera(color);
}
