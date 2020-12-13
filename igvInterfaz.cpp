#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "igvInterfaz.h"

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
                             // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz () {}

igvInterfaz::~igvInterfaz () {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
	// crear cámaras
	interfaz.camara.set(IGV_PERSPECTIVA, igvPunto3D(30,30,10),igvPunto3D(-20,-20,4),igvPunto3D(0,1,0),
		                                60.0, 1.0 , 0.1, -1*3);
}

void igvInterfaz::configura_entorno(int argc, char** argv,
			                              int _ancho_ventana, int _alto_ventana,
			                              int _pos_X, int _pos_Y, string _titulo){
	// inicialización de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicialización de la ventana de visualización
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(_ancho_ventana,_alto_ventana);
  glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
  glClearColor(1.0,1.0,1.0,0.0); // establece el color de fondo de la ventana

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
  glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
    case 'x': // Apartado A: rotar X positivo 
		interfaz.escena.incrementaAngulo('X', 10);
		break;
    case 'X': // Apartado A: rotar X negativo 
		interfaz.escena.incrementaAngulo('X', -10);
		break;
    case 'y': // Apartado A: rotar Y positivo 
		interfaz.escena.incrementaAngulo('Y', 10);
		break;
    case 'Y': // Apartado A: rotar y negativo 
		interfaz.escena.incrementaAngulo('Y', -10);
		break;
    case 'z': // Apartado A: rotar z positivo 
		interfaz.escena.incrementaAngulo('Z', 10);
		break;
    case 'Z': // Apartado A: rotar Z negativo 
		interfaz.escena.incrementaAngulo('Z', -10);
		break;
	case 'e': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes()?false:true);
	    break;
	case 'n':
		interfaz.normal = !interfaz.normal;
		break;
	case 'N':
		interfaz.normal = !interfaz.normal;
		break;
	case 'g':
		interfaz.gouraud = !interfaz.gouraud;
		break;
	case 'G':
		interfaz.gouraud = !interfaz.gouraud;
		break;
	case 'w':
		interfaz.camara.mover('w');
		interfaz.camara.aplicar();
		break;
	case 'a':
		interfaz.camara.mover('a');
		interfaz.camara.aplicar();
		break;
	case 's':
		interfaz.camara.mover('s');
		interfaz.camara.aplicar();
		break;
	case 'd':
		interfaz.camara.mover('d');
		interfaz.camara.aplicar();
		break;
    case 27: // tecla de escape para SALIR
      exit(1);
    break;
  }
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
  // dimensiona el viewport al nuevo ancho y alto de la ventana
  // guardamos valores nuevos de la ventana de visualizacion
  interfaz.set_ancho_ventana(w);
  interfaz.set_alto_ventana(h);

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	// se establece el viewport
	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();

	//visualiza la escena
	interfaz.escena.visualizar(interfaz.normal, interfaz.gouraud);

	// refresca la ventana
	glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}


void igvInterfaz::set_glutPassiveMotionFunc(GLint x, GLint y) {
	/*
	interfaz.difXMotion = (x - interfaz.difXMotion) * 0.01f;
	interfaz.difYMotion = (y - interfaz.difYMotion) * 0.01f;
	std::cout << interfaz.difXMotion << " " << interfaz.difYMotion << "\n";
	interfaz.camara.rotate(interfaz.difXMotion, interfaz.difYMotion);
	interfaz.camara.aplicar();
		*/
	glutPostRedisplay();

	

}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutPassiveMotionFunc(set_glutPassiveMotionFunc);
}
