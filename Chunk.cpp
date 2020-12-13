#include "Chunk.h"
#include <map>
Chunk::Chunk()
{
}

Chunk::Chunk(int xMin, int zMin ,int tamaX, int tamaY, int tamaZ): tamaX(tamaX), tamaY(tamaY), tamaZ(tamaZ)
{
	float lado = 1;
	int r = 0;
	int g = 0;
	int b = 0;
	for (int y = 0; y < tamaY; y++)
	{
		for (int x = 0; x < tamaX; x++)
		{
			for(int z = 0; z < tamaZ; z++){
				float* color = new float[3];
				if (z % 2 == 0) {
					color[0] = r / 255.0;
					color[1] = g / 255.0;
					color[2] = b / 255.0;
				}
				else if (z % 3 == 0) {
					color[0] = g / 255.0;
					color[1] = b / 255.0;
					color[2] = r / 255.0;
				}
				else {
					color[0] = b / 255.0;
					color[1] = r / 255.0;
					color[2] = g / 255.0;
				}
				if (y == tamaY - 1) {
					color[1] = 1;
					color[0] = color[2] = 0;
				}
				igvPunto3D coords(xMin + x*lado, y*lado, zMin + z*lado);
				Cubo* cubo = new Cubo(lado, coords, color);
				this->chunk.push_back(cubo);
				b += 1;
			}
			if (b >= 255) {
				b = 0;
			}
			g++;
		}
		if (g >= 255) {
			g = 0;
		}
		r ++;
		if (r >= 255) {
			printf("NO HAY MAS COLORES QUE ISISTE");
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
			return chunk[i];
		}
	}
    return nullptr;
}

void Chunk::drawChunk()
{
	for (int i = 0; i < chunk.size(); i++)
	{
		chunk[i]->visualizarCubo();
	}

}

void Chunk::drawChunkSinColor()
{
	for (int i = 0; i < chunk.size(); i++)
	{
		chunk[i]->visualizaCuboSinColor();
	}

}