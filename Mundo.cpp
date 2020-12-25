#include "Mundo.h"
#include "orientacion.h"
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
	int cx = 100;
	int cz = 60;
	for (int i = 0; i < numDivZ; i++)
	{
		for (int j = 0; j < numDivX; j++) {
			int rc = j * tamaChunkX + xMin + cx;
			int bc = i * tamaChunkZ + zMin + cz;
			igvColor chunkColor(rc, 0, bc);
			Chunk* chunk = new Chunk(j*tamaChunkX + xMin,i*tamaChunkZ + zMin,tamaChunkX,tamaChunkY,tamaChunkZ, chunkColor, loader);
			mundo[i].push_back(chunk);
			//mundoSeleccion.insert(std::pair<igvColor, Chunk*>(chunkColor, chunk));
			cz += 1;
			std::cout << "Color generado: " << rc << " " << bc << "\n";
		}
		cx += 2;
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

void Mundo::drawWorldCubes()
{
	for (int i = 0; i < mundo.size(); i++) {
		for (int j = 0; j < mundo[i].size(); j++) {
			mundo[i][j]->drawChunkSeleccionCubo();
		}
	}
}

void Mundo::drawWorldChunksVB()
{
	for (int i = 0; i < mundo.size(); i++) {
		for (int j = 0; j < mundo[i].size(); j++) {
			mundo[i][j]->drawColorBox();
		}
	}
}

Chunk* Mundo::getChunkSeleccion(igvColor& color) {
	for (int i = 0; i < mundo.size(); i++) {
		for (int j = 0; j < mundo[i].size(); j++) {
			if (color == *(mundo[i][j]->getColor())) {
				return mundo[i][j];
			}
		}
	}
	return nullptr;
}

Chunk** Mundo::getChunkSeleccionFrontera(igvColor& color) {
	Chunk* sel = nullptr;
	int z, x;
	for (int i = 0; i < mundo.size(); i++) {
		for (int j = 0; j < mundo[i].size(); j++) {
			if (color == *(mundo[i][j]->getColor())) {
				sel = mundo[i][j];
				z = i;
				x = j;
			}
		}
	}
	if(!sel) return nullptr;
	Chunk** frontera = new Chunk*[9];
	for (int i = 0; i < 9; i++)
	{
		frontera[i] = nullptr;
	}
	frontera[CENTRO] = sel;

	if ((x - 1) >= 0) {
		frontera[IZQ] = mundo[z][x - 1];
	}
	if ((x + 1) < mundo[z].size()) {
		frontera[DER] = mundo[z][x + 1];
	}

	if ((z - 1) >= 0) {
		frontera[ARRIBA] = mundo[z - 1][x];
		if ((x - 1) >= 0) {
			frontera[ARRIBA_IZQ] = mundo[z - 1][x - 1];
		}
		if((x + 1) < mundo[z-1].size()) {
			frontera[ARRIBA_DER] = mundo[z - 1][x + 1];
		}
	}
	if ((z + 1) < mundo.size()) {
		frontera[ABAJO] = mundo[z + 1][x];
		if ((x - 1) >= 0) {
			frontera[ABAJO_IZQ] = mundo[z + 1][x - 1];
		}
		if ((x + 1) < mundo[z + 1].size()) {
			frontera[ABAJO_DER] = mundo[z + 1][x + 1];
		}
	}

	return frontera;
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
