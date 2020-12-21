#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "igvInterfaz.h"
#define PI 3.14159265358979323846
extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
                             // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz () {}

igvInterfaz::~igvInterfaz () {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
	// crear cámaras
	interfaz.camara.set(IGV_PERSPECTIVA, igvPunto3D(25,7,25),igvPunto3D(25,7,24),igvPunto3D(0,1,0),
		                                60.0, 1.0 , 0.2, -1*3);
	interfaz.minimapa.set(IGV_PERSPECTIVA, igvPunto3D(25, 25, 25), igvPunto3D(25, 7, 25), igvPunto3D(1, 0, 0),
		60.0, 1.0, 0.2, -1 * 3);
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
  glutSetCursor(GLUT_CURSOR_NONE);
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
		interfaz.camara.moverAdelante(interfaz.dt);
		interfaz.camara.aplicar();
		break;
	case 'a':
		interfaz.camara.moverIzquierda(interfaz.dt);
		interfaz.camara.aplicar();
		break;
	case 's':
		interfaz.camara.moverAtras(interfaz.dt);
		interfaz.camara.aplicar();
		break;
	case 'd':
		interfaz.camara.moverDerecha(interfaz.dt);
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

	// Apartado A: antes de aplicar las transformaciones de cámara y proyección hay que comprobar el modo para sólo visualizar o seleccionar:
	if (interfaz.modo == IGV_SELECCIONAR) {
		// Apartado A: Para que funcione habrá que dibujar la escena sin efectos, sin iluminación, sin texturas ...
		glDisable(GL_LIGHTING); // desactiva la iluminacion de la escena
		glDisable(GL_DITHER);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_CULL_FACE);
		// Apartado A: Reestablece los colores como no seleccionado


		// Apartado A: aplica la cámara
		interfaz.camara.aplicar();

		// Apartado A: visualiza los BV cada uno de un color


		// Apartado A: Obtener el color del pixel seleccionado
		GLubyte pixel[3];
		glReadPixels(interfaz.cursorX, interfaz.cursorY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

		// Apartado A: Comprobar el color del objeto que hay en el cursor mirando en la tabla de colores y asigna otro color al objeto seleccionado



		// Apartado A: Cambiar a modo de visualización de la escena
		interfaz.modo = IGV_VISUALIZAR;

		// Apartado A: Habilitar de nuevo la iluminación
		glEnable(GL_LIGHTING);
	}
	else {
		// aplica las transformaciones en función de los parámetros de la cámara
		interfaz.camara.aplicar();
		// visualiza la escena
		interfaz.escena.visualizar(false,false);

		// refresca la ventana
		glutSwapBuffers();
	}
}
void igvInterfaz::set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y) {
	// Apartado A: comprobar que se ha pulsado el botón izquierdo 
	if (boton == GLUT_LEFT_BUTTON) {
		// Apartado A: guardar que el boton se ha presionado o se ha soltado, si se ha pulsado hay que
		// pasar a modo IGV_SELECCIONAR
		if (estado == GLUT_DOWN) {
			std::cout << "Boton pulsado y presionado";
			interfaz.boton_retenido = true;

			interfaz.modo = IGV_SELECCIONAR;

			// Apartado A: guardar el pixel pulsado
			interfaz.cursorX = x;
			interfaz.cursorY = interfaz.alto_ventana - y;
		}
		else {
			interfaz.boton_retenido = false;
		}


		// Apartado A: renovar el contenido de la ventana de vision 
		glutPostRedisplay();
	}
}


void igvInterfaz::set_glutPassiveMotionFunc(GLint x, GLint y) {
	if (interfaz.skipEvento) {
		interfaz.skipEvento = false;
		return;
	}
	glutWarpPointer(interfaz.ancho_ventana / 2, interfaz.alto_ventana / 2); //esta funcion genera un evento al mover el raton que no me interesa.
	//std::cout << "dt: " << dt << "\n";

		double nuevox = (x - (interfaz.ancho_ventana / 2)) * interfaz.dt;
		double nuevoy = ((interfaz.alto_ventana / 2) - y) * interfaz.dt;
		interfaz.camara.mirar(nuevox, nuevoy);
		interfaz.camara.aplicar();
		interfaz.skipEvento = true;

	glutPostRedisplay();

	

}

void igvInterfaz::set_timer(int)
{
	int t = glutGet(GLUT_ELAPSED_TIME);
	interfaz.dt = (t - interfaz.tUltimoFotograma) / 1000.0;
	interfaz.tUltimoFotograma = t;
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, set_timer, 0);
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutPassiveMotionFunc(set_glutPassiveMotionFunc);
	glutMouseFunc(set_glutMouseFunc);
	glutTimerFunc(1000/60,set_timer,0);
}
