#include "Mundo.h"

Mundo::Mundo()
{
}

Mundo::Mundo(int xMin, int xMax, int zMin, int zMax, int tamaChunkX, int tamaChunkY, int tamaChunkZ)
{
	int bloquesX = xMax - xMin;
	int bloquesZ = zMax - zMin;
	int numDivX = ceil(bloquesX / (float)tamaChunkX);
	int numDivZ = ceil(bloquesZ / (float)tamaChunkZ);

	int rectificarXmax = xMax + (numDivX * tamaChunkX - bloquesX);
	int rectificarZmax = zMax + (numDivZ * tamaChunkZ - bloquesZ);

	this->xMax = rectificarXmax;
	this->xMin = xMin;
	this->zMax = rectificarZmax;
	this->zMin = zMin;
	this->tamCasillaX = tamaChunkX;
	this->tamCasillaZ = tamaChunkZ;

	mundo.resize(numDivZ);
	float* colorgen = new float[3];
	colorgen[0] = colorgen[1] = colorgen[2] = 0;
	for (int i = 0; i < numDivZ; i++)
	{
		for (int j = 0; j < numDivX; j++) {
			Chunk* chunk = new Chunk(j*tamaChunkX + xMin,i*tamaChunkZ + zMin,tamaChunkX,tamaChunkY,tamaChunkZ, colorgen, loader);
			mundo[i].push_back(chunk);
		}
	}
}

Mundo::~Mundo()
{
	for (auto zona : mundo) {
		for (auto chunk : zona) {
			delete chunk;
		}
		zona.clear();
	}
	mundo.clear();
}

void Mundo::drawWorld()
{
	for (int i = 0; i < mundo.size(); i++) {
		for (int j = 0; j < mundo[i].size(); j++) {
			mundo[i][j]->drawChunk();
		}
	}
}

Chunk* Mundo::getChunk(int x, int z)
{
	if (x > xMax || x<xMin || z>zMax || z < zMin) return nullptr;
	int zc = (z - zMin) / tamCasillaZ;
	int xc = (x - xMin) / tamCasillaX;
	if (zc > mundo.size() - 1) zc = mundo.size() - 1;
	if (xc > mundo[zc].size() - 1) xc = mundo[zc].size() - 1;
	return mundo[zc][xc];
}
