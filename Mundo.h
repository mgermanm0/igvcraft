#pragma once
#include <vector>
#include "Chunk.h"
#include "TextureLoader.h"
class Mundo
{
private:
	std::vector<std::vector<Chunk*>> mundo;
	TextureLoader loader;
	int xMin, zMin, xMax, zMax;
	float tamCasillaX, tamCasillaZ;
public:
	Mundo();
	Mundo(int xMin, int xMax, int zMin, int zMax, int tamaChunkX, int tamaChunkY, int tamaChunkZ);
	~Mundo();
	void drawWorld();
	Chunk* getChunk(int x, int y);
};

