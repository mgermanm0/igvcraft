#include "TextureLoader.h"
#include <iostream>
TextureLoader::TextureLoader()
{
	texturas.push_back(new igvTextura(".\\textures\\dirt.png"));
	texturas.push_back(new igvTextura(".\\textures\\stone.png"));
	texturas.push_back(new igvTextura(".\\textures\\grass_side.png"));
	texturas.push_back(new igvTextura(".\\textures\\grass_block_top.png"));	
	texturas.push_back(new igvTextura(".\\textures\\oak_planks.png"));
	texturas.push_back(new igvTextura(".\\textures\\bedrock.png"));
}

TextureLoader::~TextureLoader()
{
	for (auto textura : texturas) {
		delete textura;
	}

}

igvTextura* TextureLoader::getTextura(tipoCubo tipo)
{
	if (tipo == VACIO) return nullptr;
	return texturas[tipo];

}

