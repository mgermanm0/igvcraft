#pragma once
#include <vector>
#include "igvTextura.h"
#include "tipoCubo.h"
class TextureLoader
{
private:
	std::vector<igvTextura*> texturas;
public:
	TextureLoader();
	~TextureLoader();

	igvTextura* getTextura(tipoCubo tipo);
};

