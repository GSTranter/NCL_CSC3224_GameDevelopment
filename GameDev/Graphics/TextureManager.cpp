/***********************************************************************
Class: TextureManager
File Type: cpp
Author: George Tranter
Description: Class to be used to load and handle state textures
***********************************************************************/

#include "TextureManager.h"

//Loads all textures associated with a state
void TextureManager::loadStateTextures(string fileName) {
	defaultTex.loadFromFile(D_TEX_FILE);

	ifstream inputFile(fileName);

	string name;
	string texFile;
	sf::Texture tex;
	
	for (string line; getline(inputFile, line);) {
		istringstream inLine(line);

		inLine >> name >> texFile;

		tex.loadFromFile(texFile);
		textures[name] = tex;
	}
}

//Get reference to texture
sf::Texture& TextureManager::getTexRef(std::string texName) {
	try {
		return textures.at(texName);
	}
	catch (std::out_of_range e) {
		return defaultTex;
	}
}

//Get pointer to texture
sf::Texture* TextureManager::getTexPoint(std::string texName) {
	sf::Texture* tex = new sf::Texture;

	try {
		tex = new sf::Texture(textures.at(texName));
	}
	catch (std::out_of_range e) {
		printf("TEXTURE NOT FOUND: USING DEFAULT TEXTURE");
		*tex = defaultTex;
	}

	return tex;
}