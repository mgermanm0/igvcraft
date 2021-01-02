#include "Chunk.h"
#include "TipoBloque.h"
#include "tipoCubo.h"
#include "TextureLoader.h"
#include "orientacion.h"
#include "caraCubo.h"
#include <map>
Chunk::Chunk()
{
}

Chunk::Chunk(int xMin, int zMin ,int tamaX, int tamaY, int tamaZ, igvColor& colorgen): tamaX(tamaX), tamaY(tamaY), tamaZ(tamaZ), color(colorgen)
{
	esquina.set(xMin, 0, zMin);
	float lado = 1;
	int r = 0;
	int g = 0;
	int b = 0;

	chunk.resize(tamaX);
	for (int x = 0; x < tamaX; x++)
	{
		for (int y = 0; y < tamaY; y++)
		{
			chunk[x].resize(tamaY);
			for (int z = 0; z < tamaZ; z++) {
				chunk[x][y].resize(tamaZ);
			}
		}
	}
	
	for (int y = 0; y < tamaY; y++)
	{
		for (int x = 0; x < tamaX; x++)
		{
			for(int z = 0; z < tamaZ; z++){
				igvColor* colorCubo = new igvColor(r, g, b);
				
				igvPunto3D coords(xMin + x*lado, y*lado, zMin + z*lado);
				Cubo* cubo;
				if(y==0) cubo = new Cubo(lado, coords, *colorCubo, PIEDRAMADRE, false);
				else if(y == (tamaY/4)) cubo = new Cubo(lado, coords, *colorCubo, CESPED, true);
				else if (y > (tamaY/4)){
					cubo = new Cubo(lado, coords, *colorCubo, VACIO, true);
				}
				else {
					cubo = new Cubo(lado, coords, *colorCubo, PIEDRA, true);
				}
				this->chunk[x][y][z] = cubo;

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
			}
		}
	}
}

Chunk::~Chunk()
{
	for (auto x : chunk) {
		for (auto y : x) {
			for (auto z : y) {
				delete z;
			}
			y.clear();
		}
		x.clear();
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
	for (int x = 0; x < chunk.size(); x++)
	{
		for (int y = 0; y < chunk[x].size(); y++)
		{
			for (int z = 0; z < chunk[x][y].size(); z++) {
				if (p == *(chunk[x][y][z]->getCoords())) {
					//std::cout << "Cubo seleccionado por coords: " << *(chunk[i]) << "\n";
					return chunk[x][y][z];
				}
			}
		}
	}

    return nullptr;
}

Cubo* Chunk::getCubo(igvColor& p)
{
	for (int x = 0; x < chunk.size(); x++)
	{
		for (int y = 0; y < chunk[x].size(); y++)
		{
			for (int z = 0; z < chunk[x][y].size(); z++) {
				if (p == *(chunk[x][y][z]->getColor())) {
					//std::cout << "Cubo seleccionado por coords: " << *(chunk[i]) << "\n";
					return chunk[x][y][z];
				}
			}
		}
	}
	return nullptr;
}


void Chunk::drawColorBox()
{
	float cx = color[R] / 255.0f;
	float cz = color[B] / 255.0f;
	
	float* color = new float[3]{ cx,0,cz };
	glPushMatrix();
	for (int x = 0; x < chunk.size(); x++)
	{
		for (int y = 0; y < chunk[x].size(); y++)
		{
			for (int z = 0; z < chunk[x][y].size(); z++) {
					//std::cout << "Cubo seleccionado por coords: " << *(chunk[i]) << "\n";
				if (chunk[x][y][z]->getTipo() != VACIO) chunk[x][y][z]->visualizaCuboChunkColor(color);
			}
		}
	}
	glPopMatrix();
}


void Chunk::drawChunk(TextureLoader* tl)
{
	glPushMatrix();
	for (int x = 0; x < chunk.size(); x++)
	{
		for (int y = 0; y < chunk[x].size(); y++)
		{
			for (int z = 0; z < chunk[x][y].size(); z++) {
				//std::cout << "Cubo seleccionado por coords: " << *(chunk[i]) << "\n";
				if (chunk[x][y][z]->getTipo() != VACIO) chunk[x][y][z]->visualizarCubo(tl);
			}
		}
	}
	glPopMatrix();

}

void Chunk::drawChunkSeleccionCubo()
{
	glPushMatrix();
	for (int x = 0; x < chunk.size(); x++)
	{
		for (int y = 0; y < chunk[x].size(); y++)
		{
			for (int z = 0; z < chunk[x][y].size(); z++) {
				//std::cout << "Cubo seleccionado por coords: " << *(chunk[i]) << "\n";
				if (chunk[x][y][z]->getTipo() != VACIO) chunk[x][y][z]->visualizaCuboSeleccion();
			}
		}
	}
	glPopMatrix();

}



void Chunk::drawChunkSeleccionCaras() {
	glPushMatrix();
	for (int x = 0; x < chunk.size(); x++)
	{
		for (int y = 0; y < chunk[x].size(); y++)
		{
			for (int z = 0; z < chunk[x][y].size(); z++) {
				//std::cout << "Cubo seleccionado por coords: " << *(chunk[i]) << "\n";
				if (chunk[x][y][z]->getTipo() != VACIO) chunk[x][y][z]->visualizaCarasCuboSeleccion();
			}
		}
	}
	glPopMatrix();
}

void Chunk::colocarCubo(igvColor& colorCara, Chunk** frontera, Cubo* seleccionado, tipoCubo selPl)
{
	caraCubo cara = seleccionado->caraSeleccionada(colorCara);
	int indexX = seleccionado->getCoordX() - esquina[X];
	int indexY = seleccionado->getCoordY();
	int indexZ = seleccionado->getCoordZ() - esquina[Z];
	switch (cara)
	{
	case DELANTERA:
		if (indexZ + 1 < chunk[indexX][indexY].size()) {
			if(chunk[indexX][indexY][indexZ + 1]->getTipo() == VACIO) chunk[indexX][indexY][indexZ + 1]->setTipo(selPl);
		}
		else {
			if (frontera[ABAJO] != nullptr && frontera[ABAJO]->chunk[indexX][indexY][0]->getTipo() == VACIO) {
				frontera[ABAJO]->chunk[indexX][indexY][0]->setTipo(selPl);
			}
		}
		break;
	case IZQ:
		if (indexX - 1 >= 0) {
			if (chunk[indexX - 1][indexY][indexZ]->getTipo() == VACIO) chunk[indexX - 1][indexY][indexZ]->setTipo(selPl);
		}
		else {
			if (frontera[CENTRO_IZQ] != nullptr && frontera[CENTRO_IZQ]->chunk[tamaX-1][indexY][indexZ]->getTipo() == VACIO) {
				frontera[CENTRO_IZQ]->chunk[tamaX - 1][indexY][indexZ]->setTipo(selPl);
			}
		}
		break;
	case TRASERA:
		if (indexZ - 1 >= 0) {
			if (chunk[indexX][indexY][indexZ - 1]->getTipo() == VACIO) chunk[indexX][indexY][indexZ - 1]->setTipo(selPl);
		}
		else {
			if (frontera[ARRIBA] != nullptr && frontera[ARRIBA]->chunk[indexX][indexY][tamaZ - 1]->getTipo() == VACIO) {
				frontera[ARRIBA]->chunk[indexX][indexY][tamaZ-1]->setTipo(selPl);
			}
		}
		break;
	case DER:
		if (indexX + 1 < chunk.size()) {
			if (chunk[indexX + 1][indexY][indexZ]->getTipo() == VACIO) chunk[indexX + 1][indexY][indexZ]->setTipo(selPl);
		}else {
			if (frontera[CENTRO_DER] != nullptr && frontera[CENTRO_DER]->chunk[0][indexY][indexZ]->getTipo() == VACIO) {
				frontera[CENTRO_DER]->chunk[0][indexY][indexZ]->setTipo(selPl);
			}
		}
		break;
	case BASE:
		if (indexY - 1 >= 0) {
			if (chunk[indexX][indexY - 1][indexZ]->getTipo() == VACIO) chunk[indexX][indexY - 1][indexZ]->setTipo(selPl);
		}
		break;
	case TAPA:
		if (indexY + 1 < chunk[indexX].size()) {
			if(chunk[indexX][indexY + 1][indexZ]->getTipo() == VACIO) chunk[indexX][indexY + 1][indexZ]->setTipo(selPl);
		}
		break;
	}

}

void Chunk::quitarCubo(Cubo* seleccionado)
{
	if(seleccionado->puedoRomper()) seleccionado->setTipo(VACIO);
}