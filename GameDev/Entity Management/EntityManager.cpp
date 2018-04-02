/************************************************************
Class: EntityManger
File Type: cpp
Author: George Tranter
Description: Class to act as a container for all entities
************************************************************/

#include "EntityManager.h"
#include <iostream>
//^~^CONSTRUCTORS^~^//
EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
	delete player;
	
	for (int i = 0; i < MAX_ENEMIES; i++) {
		delete enemies[i];
	}

	for (int i = 0; i < MAX_PLATFORMS; i++) {
		delete platforms[i];
	}
}

//^~^FUNCTIONS^~^//
//Ini for InGame state
void EntityManager::inGameIni(std::string playerFile, std::string platformFile, std::string enemyFile) {
	numPlatforms = 0;
	numEnemies = 0;

	//Load in the player file and set stats
	player = new Player();
	input_player playerInput = FileInput::loadStatePlayer(playerFile);
	player->iniPosition(playerInput.xPos, playerInput.yPos);
	player->setStats(playerInput.health, playerInput.speed, playerInput.jumpStrength, playerInput.damage, playerInput.attackSpeed);

	//Load in the platform file and set stats
	vector<input_platform> platformInput = FileInput::loadStatePlatforms(platformFile);
	for (int i = 0; i < platformInput.size(); i++) {
		platforms[numPlatforms] = new Platform();
		platforms[numPlatforms]->setPosition(sf::Vector2f(platformInput[numPlatforms].xPos, platformInput[numPlatforms].yPos));
		platforms[numPlatforms]->setSize(sf::Vector2f(platformInput[numPlatforms].width, platformInput[numPlatforms].height));
		numPlatforms++;
	}

	//Load in the enemies file and set stats
	vector<input_enemy> enemyInput = FileInput::loadStateEnemies(enemyFile);
	for (int i = 0; i < enemyInput.size(); i++) {
		enemies[numEnemies] = new Enemy();
		enemies[numEnemies]->setOriginalPos(enemyInput[numEnemies].xPos, enemyInput[numEnemies].yPos);
		enemies[numEnemies]->setPosition(enemies[numEnemies]->getOriginalPos());
		enemies[numEnemies]->setStats(enemyInput[numEnemies].health, enemyInput[numEnemies].speed, enemyInput[numEnemies].damage);
		if (numEnemies > 0) {
			int id = enemies[numEnemies - 1]->getId();
			id++;
			enemies[numEnemies]->setId(id);
		}
		
		numEnemies++;
	}
}

void EntityManager::enemySpawn() {
	isSpawned = true;
}

void EntityManager::enemyDespawn() {
	//Set enemies to original position
	for (int i = 0; i < numEnemies; i++) {
		enemies[i]->setPosition(enemies[i]->getOriginalPos());
	}

	isSpawned = false;
}

void EntityManager::inGameUpdate() {
	
	//Update player
	player->playerUpdate();

	//Update enemies
	if (isSpawned == true && physicsSet == true) {
		for (int i = 0; i < numEnemies; i++) {
			enemies[i]->enemyUpdate(player);
		}
	}
}
