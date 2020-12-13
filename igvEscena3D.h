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

class igvEscena3D {
protected:
	// Atributos
	bool ejes;
	Mundo* mundo;
	// Apartado A: Añadir aquí los atributos con los ángulos de rotación en X, Y y Z.
	double anguloX = 0;
	double anguloY = 0;
	double anguloZ = 0;

	int x = 0;
	int z = 0;
public:
	// atributos públicos
	igvMallaTriangulos* malla; // malla de triángulos asociada a la escena

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// Métodos
	// método con las llamadas OpenGL para visualizar la escena
	void visualizar(bool normal, bool gouraud);

	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };

	// Apartado A: métodos para incrementar los ángulos
	void incrementaAngulo(char eje, double incremento);
	// Apartado A: métodos para obtener los valores de los ángulos

};

#endif
