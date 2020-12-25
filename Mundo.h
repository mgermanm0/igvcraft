#pragma once
#include <vector>
#include <map>
#include "Chunk.h"
#include "igvColor.h"
#include "TextureLoader.h"

struct CompareColor
{
	bool operator() (const igvColor& lhs, const igvColor& rhs) const
	{
		return igvColor::less(lhs, rhs);
	}
};

class Mundo
{
private:
	std::vector<std::vector<Chunk*>> mundo;
	std::map<igvColor, Chunk*, CompareColor> mundoSeleccion;
	TextureLoader loader;
	int xMin, zMin, xMax, zMax;
	float tamCasillaX, tamCasillaZ;
public:
	Mundo();
	Mundo(int xMin, int xMax, int zMin, int zMax, int tamaChunkX, int tamaChunkY, int tamaChunkZ);
	~Mundo();
	void drawWorld();
	void drawWorldCubes();
	void drawWorldChunksVB();
	Chunk* getChunkSeleccion(igvColor& color);
	Chunk** getChunkSeleccionFrontera(igvColor& color);
	Chunk* getChunk(int x, int y);
};

