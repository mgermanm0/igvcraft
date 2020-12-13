#pragma once
#include "Cubo.h"
#include <vector>
#include "igvPunto3D.h"
struct comparatorPunto3D {

	bool operator() (const igvPunto3D& p1, const igvPunto3D& p2) {
		float d1 = sqrt(pow(p1[X], 2) + pow(p1[Y], 2) + pow(p1[Z], 2));
		float d2 = sqrt(pow(p2[X], 2) + pow(p2[Y], 2) + pow(p2[Z], 2));
		return d1 < d2;
	}

};
class Chunk
{
private:
	std::vector<Cubo*> chunk;
	int tamaX = 4;
	int tamaY = 4;
	int tamaZ = 4;
public:
	Chunk();
	Chunk(int xMin, int zMin, int tamaX, int tamaY, int tamaZ);
	~Chunk();
	int getTam();
	Cubo* getCubo(igvPunto3D p);
	void drawChunk();
	void drawChunkSinColor();


};

