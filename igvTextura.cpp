#include "igvTextura.h"
#include <string>
// Metodos constructores y destructor

igvTextura::igvTextura(std::string fichero) {
	ancho = 0;
	alto = 0;

	SDL_Surface* imagen = NULL;

	if (!glIsTexture(idTextura)) {

		imagen = IMG_Load(&fichero[0]);
		if (!imagen)
		{
			/* Fallo de carga de la imagen */
			printf("Error al cargar la imagen: %s\n", IMG_GetError());
			return;

		}
		ancho = imagen->w;
		alto = imagen->h;
		/* Muestra alguna información sobre la imagen */
		//printf("Cargando %s: %dx%d %dbpp\n", fichero, imagen->w, imagen->h, imagen->format->BitsPerPixel);
		// Apartado G: Añadir aquí el código para cargar como textura OpenGL la imagen */
		//	- Generar el identificador de textura y asignarlo al atributo idTextura (glGenTextures)
		glGenTextures(1, &idTextura);
		//	- Enlazar el identificador creado a GL_TEXTURE_2D (glBindTexture)
		glBindTexture(GL_TEXTURE_2D, idTextura);
		//  - Especificar la textura, asignádole como textura el array imagen (glTexImage2D)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagen->w, imagen->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagen->pixels);
		//  - Modo de aplicación de la textura (glTexEnvf)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//	- Parámetros de la textura: repetición y filtros (glTexParameteri)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		SDL_FreeSurface(imagen);
	}
}

void igvTextura::aplicar(void) {
  glBindTexture(GL_TEXTURE_2D, idTextura);
}

igvTextura::~igvTextura() {
  glDeleteTextures(1, &idTextura); 
}
