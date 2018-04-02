/************************************************************
Class: Renderer
File Type: cpp
Author: George Tranter
Description: Class to be used as a render sub-system
************************************************************/

#include "Renderer.h"
#include <iostream>
using namespace sf;

namespace rend {

	//^~^CONSTRUCTOR^~^//
	Renderer::Renderer() {};
	Renderer::~Renderer() {};

	//^~^FUNCTIONS^~^//
		
		//Load textures for a state and bind them to the entities
	void Renderer::bindLevelTextures(string fileName) {
		stateTextures = new TextureManager();
		stateTextures->loadStateTextures(fileName);

		//Bind non-entity textures
		background = new Sprite();
		background->setTexture(stateTextures->getTexRef("background"));
		pauseOverlay = new Sprite();
		pauseOverlay->setTexture(stateTextures->getTexRef("pause"));
		gameOverOverlay = new Sprite();
		gameOverOverlay->setTexture(stateTextures->getTexRef("gameover"));
		victory = new Sprite();
		victory->setTexture(stateTextures->getTexRef("victory"));

		//Bind player textures
		gameEntities->getPlayer()->setRightTexture(stateTextures->getTexPoint("playerRight"));
		gameEntities->getPlayer()->setLeftTexture(stateTextures->getTexPoint("playerLeft"));
		gameEntities->getPlayer()->setJumpRightTexture(stateTextures->getTexPoint("playerJumpRight"));
		gameEntities->getPlayer()->setJumpLeftTexture(stateTextures->getTexPoint("playerJumpLeft"));
		gameEntities->getPlayer()->setTexture(*(gameEntities->getPlayer()->getStartingTexture()));
		
		//Bind platform texture
		for (int i = 0; i < gameEntities->getNumPlatforms(); i++) {
			gameEntities->getPlatform(i)->setTexture(stateTextures->getTexPoint("platform"));
		}
		
		//Bind enemy texture
		for (int i = 0; i < gameEntities->getNumEnemies(); i++) {
			gameEntities->getEnemy(i)->setTexture(stateTextures->getTexRef("enemy"));
		}
	}
		
		//Load textures for the main menu
	void Renderer::bindMenuTextures(string fileName) {
		stateTextures = new TextureManager();
		stateTextures->loadStateTextures(fileName);

		background = new Sprite();
		background->setTexture(stateTextures->getTexRef("background"));

		loading = new Sprite();
		loading->setTexture(stateTextures->getTexRef("loading"));
	}

		//Draw InGame objects//
	void Renderer::inGameRender(sf::Text* winText) {
		gameWindow->clear();

		//Draw scene
		gameWindow->draw(*background);
		
		for (int i = 0; i < gameEntities->getNumPlatforms(); i++) {
			gameWindow->draw(*(gameEntities->getPlatform(i)));
		}
		
		//Drar player and enemies
		gameWindow->draw(*(gameEntities->getPlayer()));

		if (gameEntities->getSpawned() == true) {
			for (int i = 0; i < gameEntities->getNumEnemies(); i++) {
				gameWindow->draw(*(gameEntities->getEnemy(i)));
			}
		}

		if (winText != NULL) {
			gameWindow->draw(*winText);
		}
		
		gameWindow->display();
	}

	//Draw pause screen objects
	void Renderer::pauseGameRender() {
		gameWindow->draw(*pauseOverlay);
		gameWindow->display();
	}

	//Draw game over screen objects
	void Renderer::gameOverRender() {
		gameWindow->draw(*gameOverOverlay);
		gameWindow->display();
	}

	//Draw menu elements
	void Renderer::menuRender() {
		gameWindow->clear();
		
		//Draw scene
		gameWindow->draw(*background);

		gameWindow->display();
	}

	//Draw loading screen
	void Renderer::loadingRender() {
		gameWindow->clear();
		gameWindow->draw(*loading);
		gameWindow->display();
	}

	void Renderer::victoryRender() {
		gameWindow->clear();
		gameWindow->draw(*victory);
		gameWindow->display();
	}

}