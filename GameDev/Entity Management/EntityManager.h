/************************************************************
Class: EntityManger
File Type: h
Author: George Tranter
Description: Class to act as a container for all entities
************************************************************/

#pragma once

#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Projectile.h"
#include "FileInput.h"

using namespace sf;

enum EntityType{ PlayerType = 0, PlatformType, EnemyType};

class EntityManager{
	private:
		Player* player;

		//Enemies
		const static int MAX_ENEMIES = 50;
		Enemy* enemies[MAX_ENEMIES];
		int numEnemies;
		bool isSpawned = false;
		bool physicsSet = false;

		//Platforms
		const static int MAX_PLATFORMS = 50;
		Platform* platforms[MAX_PLATFORMS];
		int numPlatforms;

	public:
		EntityManager();
		~EntityManager();

		//Getters and setter
		inline Player* getPlayer() { return player; }
		inline int getNumPlatforms() { return numPlatforms; }
		inline Platform* getPlatform(int pos) { return platforms[pos]; }
		inline int getNumEnemies() { return numEnemies; }
		inline Enemy* getEnemy(int pos) { return enemies[pos]; }
		inline void setPlayer(Player* newPlay) { player = newPlay; }

		inline bool isPhysicsSet() { return physicsSet; }
		inline void setPhysics(bool isSet) { physicsSet = isSet; }

		inline bool getSpawned() { return isSpawned; }

		//ini for InGame state
		void inGameIni(std::string, std::string, std::string);

		//Spawning and despawing of enemies
		void enemySpawn();
		void enemyDespawn();
		
		//Update entites for InGame state
		void inGameUpdate();
};