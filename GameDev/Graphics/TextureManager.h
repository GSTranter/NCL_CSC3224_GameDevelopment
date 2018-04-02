/***********************************************************************
Class: TextureManager
File Type: h
Author: George Tranter
Description: Class to be used to load and handle state textures
***********************************************************************/

#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include <exception>
#include <fstream>
#include <sstream>

#include "FileInput.h"

	//Location of the default texture
#define D_TEX_FILE "../Resources/Other/kistoR.jpg"

using namespace std;

class TextureManager {
	private:
		map<string, sf::Texture> textures;
		sf::Texture defaultTex;

	public:
		TextureManager(){}
		~TextureManager(){}

		void loadStateTextures(string);
		sf::Texture& getTexRef(string);
		sf::Texture* getTexPoint(string);
};