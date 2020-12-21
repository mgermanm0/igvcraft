#include "Chunk.h"
#include "TipoBloque.h"
#include <map>
Chunk::Chunk()
{
}

Chunk::Chunk(int xMin, int zMin ,int tamaX, int tamaY, int tamaZ, float* colorgen): tamaX(tamaX), tamaY(tamaY), tamaZ(tamaZ)
{
	float lado = 1;
	for (int y = 0; y < tamaY; y++)
	{
		for (int x = 0; x < tamaX; x++)
		{
			for(int z = 0; z < tamaZ; z++){
				float* color = new float[3];
				color[0] = colorgen[0] / 255.0;
				color[1] = colorgen[1] / 255.0;
				color[2] = colorgen[2] / 255.0;
				
				igvPunto3D coords(xMin + x*lado, y*lado, zMin + z*lado);
				Cubo* cubo;
				if(y == (tamaY/2)) cubo = new Cubo(lado, coords, color, UtilesBloques::TIERRA);
				else if (y > (tamaY/2)){
					cubo = new Cubo(lado, coords, color, UtilesBloques::VACIO);
				}
				else {
					cubo = new Cubo(lado, coords, color, UtilesBloques::PIEDRA);
				}
				this->chunk.push_back(cubo);
				colorgen[0] += 1;

				if (colorgen[0] > 255) {
					colorgen[0] = 0;
					if (colorgen[1] > 255) {
						colorgen[1] = 0;
						if (colorgen[2] > 255) {
							printf("NO MAS COLORES");
						}
						else {
							colorgen[2] += 1;
						}
					}
					else {
						colorgen[1] += 1;
					}
				}
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

Cubo* Chunk::getCubo(float* p)
{
	for (int i = 0; i < chunk.size(); i++) {
		float* color = chunk[i]->getColor();
		if (p[0] == color[0] && p[1] == color[1] && p[2] == color[2]) {
			//std::cout << "Cubo seleccionado: " << chunk[i] << "\n";
			return chunk[i];
		}
	}
	return nullptr;
}

void Chunk::drawChunk()
{
	for (int i = 0; i < chunk.size(); i++)
	{
		if(chunk[i]->getTipo() != UtilesBloques::VACIO) chunk[i]->visualizarCubo();
	}

}

void Chunk::drawChunkSinColor()
{
	for (int i = 0; i < chunk.size(); i++)
	{
		chunk[i]->visualizaCuboSinColor();
	}

}