#include "Chunk.h"
#include "TipoBloque.h"
#include "tipoCubo.h"
#include "TextureLoader.h"
#include <map>
Chunk::Chunk()
{
}

Chunk::Chunk(int xMin, int zMin ,int tamaX, int tamaY, int tamaZ, igvColor& colorgen, TextureLoader& loader): tamaX(tamaX), tamaY(tamaY), tamaZ(tamaZ), color(colorgen)
{
	esquina.set(xMin, 0, zMin);
	float lado = 1;
	int r = 10;
	int g = 0;
	int b = 0;
	for (int y = 0; y < tamaY; y++)
	{
		for (int x = 0; x < tamaX; x++)
		{
			for(int z = 0; z < tamaZ; z++){
				igvColor* colorCubo = new igvColor(r, g, b);
				
				igvPunto3D coords(xMin + x*lado, y*lado, zMin + z*lado);
				Cubo* cubo;
				if(y == (tamaY/2)) cubo = new Cubo(lado, coords, *colorCubo, CESPED, loader.getTextura(TIERRA));
				else if (y > (tamaY/2)){
					cubo = new Cubo(lado, coords, *colorCubo, VACIO , loader.getTextura(TIERRA));
				}
				else {
					cubo = new Cubo(lado, coords, *colorCubo, PIEDRA, loader.getTextura(TIERRA));
				}
				this->chunk.push_back(cubo);
				b++;
				if (b > 255) {
					b = 0;
					if (r > 255) {
						r = 0;
						if (g > 255) {
							g = 0;
							printf("NO MAS COLORES");
						}
						else g++;
					}
					else r++;
				}
				else b++;
			}
		}
	}
}

Chunk::~Chunk()
{
	for (auto cubo : chunk) {
		delete cubo;
	}

	chunk.clear();
}

int Chunk::getTam()
{
	return chunk.size();
}

igvColor* Chunk::getColor()
{
	return &color;
}

Cubo* Chunk::getCubo(igvPunto3D p)
{
	for (int i = 0; i < chunk.size(); i++) {
		if (p == *(chunk[i]->getCoords())) {
			//std::cout << "Cubo seleccionado por coords: " << *(chunk[i]) << "\n";
			return chunk[i];
		}
	}
    return nullptr;
}

Cubo* Chunk::getCubo(igvColor& p)
{
	for (int i = 0; i < chunk.size(); i++) {
		igvColor* colorCubo = chunk[i]->getColor();
		if (p == *colorCubo) {
			//std::cout << "Cubo seleccionado: " << chunk[i] << "\n";
			return chunk[i];
		}
	}
	return nullptr;
}

void Chunk::drawColorBox()
{
	float cx = color[R] / 255.0f;
	float cz = color[B] / 255.0f;
	
	float* color = new float[3]{ cx,0,cz };
	if (marcado) color[0] = 1;
	glPushMatrix();
	for (int i = 0; i < chunk.size(); i++)
	{
		if (chunk[i]->getTipo() != VACIO) chunk[i]->visualizaCuboChunkColor(color);
	}
	glPopMatrix();
}

void Chunk::marcar()
{
	marcado = true;
}

void Chunk::drawChunk()
{
	for (int i = 0; i < chunk.size(); i++)
	{
		if(chunk[i]->getTipo() != VACIO) chunk[i]->visualizaCuboSinColor();
	}

}

void Chunk::drawChunkSeleccionCubo()
{
	for (int i = 0; i < chunk.size(); i++)
	{
		if (chunk[i]->getTipo() != VACIO) chunk[i]->visualizaCuboSeleccion();
	}

}

void Chunk::drawChunkSinColor()
{
	for (int i = 0; i < chunk.size(); i++)
	{
		chunk[i]->visualizaCuboSinColor();
	}

}