#pragma once
#include "Cubo.h"
#include <vector>
#include "igvPunto3D.h"
#include "TextureLoader.h"
#include "igvColor.h"
class Chunk
{
private:
	std::vector<std::vector<std::vector<Cubo*>>> chunk;
	igvColor color;
	igvPunto3D esquina;
	int tamaX = 4;
	int tamaY = 4;
	int tamaZ = 4;
public:
	Chunk();
	Chunk(int xMin, int zMin, int tamaX, int tamaY, int tamaZ, igvColor& colorgen);
	~Chunk();
	int getTam();
	igvColor* getColor();
	Cubo* getCubo(igvPunto3D p);
	Cubo* getCubo(igvColor& p);
	void drawColorBox();
	void drawChunk(TextureLoader* tl);
	void drawChunkSeleccionCubo();
	void drawChunkSeleccionCaras();
	void colocarCubo(igvColor& colorCara, Chunk** frontera, Cubo* seleccionado, tipoCubo selPl);
	void quitarCubo(Cubo* seleccionado);
};

