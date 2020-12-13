#include "Mundo.h"

Mundo::Mundo()
{
}

Mundo::Mundo(int xMin, int xMax, int zMin, int zMax, int tamaChunkX, int tamaChunkY, int tamaChunkZ)
{
	int bloquesX = xMax - xMin;
	int bloquesZ = zMax - zMin;
	int numDivX = ceil(bloquesX / (float)tamaChunkX);
	int numDivZ = ceil(bloquesZ / (float)tamaChunkY);

	int rectificarXmax = xMax + (numDivX * tamaChunkX - bloquesX);
	int rectificarZmax = zMax + (numDivZ * tamaChunkX - bloquesZ);

	this->xMax = rectificarXmax;
	this->xMin = xMin;
	this->zMax = rectificarZmax;
	this->zMin = zMin;
	this->tamCasillaX = tamaChunkX;
	this->tamCasillaZ = tamaChunkZ;

	mundo.resize(numDivZ);
	for (int i = 0; i < numDivZ; i++)
	{
		for (int j = 0; j < numDivX; j++) {
			Chunk* chunk = new Chunk(j*tamaChunkX + xMin,i*tamaChunkZ + zMin,tamaChunkX,tamaChunkY,tamaChunkZ);
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
	return mundo[zc][xc];
}
