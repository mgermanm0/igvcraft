#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include "igvInterfaz.h"
#define PI 3.14159265358979323846
#include "orientacion.h"
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
	interfaz.minimapa.set(IGV_PERSPECTIVA, igvPunto3D(25, 25, 25), igvPunto3D(25, 7, 25), igvPunto3D(-1, 0, 0),
		60.0, 1.0, 0.2, -1*3);
	interfaz.minimapa.setCamaraASeguir(&interfaz.camara);
	interfaz.actual = &interfaz.camara;

}

void igvInterfaz::configura_entorno(int argc, char** argv,
			                              int _ancho_ventana, int _alto_ventana,
			                              int _pos_X, int _pos_Y, string _titulo){
	// inicialización de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;
	//PlaySound( (LPCWSTR)".\\sound\\caramel.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	
	// inicialización de la ventana de visualización
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(_ancho_ventana,_alto_ventana);
  glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_titulo.c_str());
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
  glClearColor(1.0,1.0,1.0,0.0); // establece el color de fondo de la ventana

  
  glEnable(GL_LIGHTING); // activa la iluminacion de la escena
  glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion
  glEnable(GL_TEXTURE_2D);
  

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		interfaz.camara.moverAdelante(interfaz.dt);
		interfaz.minimapa.seguir(interfaz.dt);
		interfaz.camara.aplicar();
		interfaz.minimapa.aplicar();
		
		break;
	case 'a':
		interfaz.camara.moverIzquierda(interfaz.dt);
		interfaz.minimapa.seguir(interfaz.dt);
		interfaz.camara.aplicar();
		interfaz.minimapa.aplicar();
		break;
	case 's':
		interfaz.camara.moverAtras(interfaz.dt);
		interfaz.minimapa.seguir(interfaz.dt);
		interfaz.camara.aplicar();
		interfaz.minimapa.aplicar();
		break;
	case 'd':
		interfaz.camara.moverDerecha(interfaz.dt);
		interfaz.minimapa.seguir(interfaz.dt);
		interfaz.camara.aplicar();
		interfaz.minimapa.aplicar();
		break;
	case 'p':
		if (interfaz.actual == &interfaz.camara) interfaz.actual = &interfaz.minimapa;
		else interfaz.actual = &interfaz.camara;
		break;
	case 'l':
		interfaz.escena.cambiarRGB();
		break;
	case 'n':
		interfaz.escena.tipo = NORMAL;
		break;
	case 'c':
		interfaz.escena.tipo = SELCHUNK;
		break;
	case 'k':
		interfaz.escena.tipo = SELBLOQUE;
		break;
	case 'f':
		interfaz.escena.tipo = SELCARA;
		break;
	case '1':
		interfaz.seleccionPl = TIERRA;
		break;
	case '2':
		interfaz.seleccionPl = CESPED;
		break;
	case '3':
		interfaz.seleccionPl = PIEDRA;
		break;
	case '4':
		interfaz.seleccionPl = MADERA;
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
	if (interfaz.modo == SELECCIONAR) {
		// Apartado A: Para que funcione habrá que dibujar la escena sin efectos, sin iluminación, sin texturas ...
		glDisable(GL_LIGHTING); // desactiva la iluminacion de la escena
		glDisable(GL_DITHER);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_CULL_FACE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Apartado A: Reestablece los colores como no seleccionado


		// Apartado A: aplica la cámara
		interfaz.actual->aplicar();

		// Apartado A: visualiza los BV cada uno de un color
		interfaz.escena.visualizarMundoSeleccion();

		// Apartado A: Obtener el color del pixel seleccionado
		GLubyte pixel[3];
		glReadPixels(interfaz.cursorX, interfaz.cursorY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
		std::cout << "\nColor seleccionado Chunk: " << (float)pixel[0] << "," << (float)pixel[1] << "," << (float)pixel[2] << "\n";
		igvColor pxColor((float)pixel[0], (float)pixel[1], (float)pixel[2]);
		Chunk** frontera = interfaz.escena.getFronteraByColor(pxColor);
		interfaz.escena.selChunk = frontera;
		/*if (frontera != nullptr) {
			for (int i = 0; i < 9; i++)
			{
				if(frontera[i] != nullptr) frontera[i]->marcar();
			}
		}*/

		if (frontera != nullptr) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			interfaz.actual->aplicar();
			frontera[CENTRO]->drawChunkSeleccionCubo();
			glReadPixels(interfaz.cursorX, interfaz.cursorY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
			//std::cout << "\nColor seleccionado Cubo: " << (float)pixel[0] << "," << (float)pixel[1] << "," << (float)pixel[2] << "\n";
			igvColor pxColor((float)pixel[0], (float)pixel[1], (float)pixel[2]);
			Cubo* cuboSeleccinado = frontera[CENTRO]->getCubo(pxColor);
			interfaz.escena.selCubo = cuboSeleccinado;
			if (cuboSeleccinado != nullptr) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				interfaz.actual->aplicar();
				cuboSeleccinado->visualizaCarasCuboSeleccion();
				glReadPixels(interfaz.cursorX, interfaz.cursorY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
				//std::cout << "\nColor seleccionado Cara cubo: " << (float)pixel[0] << "," << (float)pixel[1] << "," << (float)pixel[2] << "\n";
				igvColor pxColor((float)pixel[0], (float)pixel[1], (float)pixel[2]);
				if (interfaz.accionActual == PONER) frontera[CENTRO]->colocarCubo(pxColor, frontera, cuboSeleccinado, interfaz.seleccionPl);
				else if (interfaz.accionActual == QUITAR && cuboSeleccinado->puedoRomper()) frontera[CENTRO]->quitarCubo(cuboSeleccinado);
			}
		}
		interfaz.modo = IGV_VISUALIZAR;
		interfaz.accionActual = NADA;

		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
	}
	else {
		interfaz.actual->aplicar();
		interfaz.escena.visualizar();
		glutSwapBuffers();
	}
	
}
void igvInterfaz::set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y) {
	switch (boton) {
	case GLUT_LEFT_BUTTON:
		if (estado == GLUT_DOWN) {
			interfaz.cursorX = x;
			interfaz.cursorY = interfaz.alto_ventana - y;
			interfaz.modo = SELECCIONAR;
			interfaz.accionActual = PONER;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (estado == GLUT_DOWN) {
			interfaz.cursorX = x;
			interfaz.cursorY = interfaz.alto_ventana - y;
			interfaz.modo = SELECCIONAR;
			interfaz.accionActual = QUITAR;
		}
		break;
	default:
		interfaz.accionActual = NADA;
		break;
	}
	glutPostRedisplay();
}


void igvInterfaz::set_glutPassiveMotionFunc(GLint x, GLint y) {
	if (interfaz.skipEvento) {
		interfaz.skipEvento = false;
		return;
	}
	if (interfaz.actual == &interfaz.camara) {
		glutWarpPointer(interfaz.ancho_ventana / 2, interfaz.alto_ventana / 2); 
		double nuevox = (x - (interfaz.ancho_ventana / 2)) * interfaz.dt;
		double nuevoy = ((interfaz.alto_ventana / 2) - y) * interfaz.dt;
		interfaz.camara.mirar(nuevox, nuevoy);
		interfaz.camara.aplicar();
		interfaz.skipEvento = true;
	}
	glutPostRedisplay();

	

}

void igvInterfaz::set_timer(int)
{
	if(interfaz.actual == &interfaz.camara) glutWarpPointer(interfaz.ancho_ventana / 2, interfaz.alto_ventana / 2);
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
