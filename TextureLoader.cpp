#include "TextureLoader.h"
#include <iostream>
TextureLoader::TextureLoader()
{
	std::string path(".\\textures\\dirt.png");
	texturas.push_back(new igvTextura(&path[0]));
}

TextureLoader::~TextureLoader()
{
	for (auto textura : texturas) {
		delete textura;
	}
}

igvTextura* TextureLoader::getTextura(tipoCubo tipo)
{
	if (tipo == TIERRA) {
		return texturas[0];
	}
}
