#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "igvMallaTriangulos.h"
#include "Chunk.h"
#include "Mundo.h"

typedef enum {
	NORMAL,
	SELCHUNK,
	SELBLOQUE,
	SELCARA
} tipoVisualizacion;

class igvEscena3D {
protected:
	// Atributos
	bool rgb = false;
	TextureLoader* tloader = nullptr;
	Mundo* mundo = nullptr;
	int contLuz = 0;
public:

	tipoVisualizacion tipo = NORMAL;
	Chunk** selChunk;
	Cubo* selCubo;

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// Métodos
	// método con las llamadas OpenGL para visualizar la escena
	void visualizar();
	void cambiarRGB();

	void visualizarMundoSeleccion();
	Chunk* getChunkByColor(igvColor& color);

	Chunk** getFronteraByColor(igvColor& color);


};

#endif
